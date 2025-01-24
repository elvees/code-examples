// Copyright 2023-2025 RnD Center "ELVEES", JSC
// SPDX-License-Identifier: MIT

/*************************

 Библиотека  функций
 для работы с NAND-flash.

 ************************/
#include "mt29f8g.h"

#include "mct03p.h"
#include "mct03p_dma_regs.h"
#include "mct03p_mport_regs.h"

#define MFBSP1_GPIO *((volatile int *)0xb82F900C)

unsigned int tmp;

// функция настройки системных регистров
void Set_Sys_reg() {
  // Управление включением тактовой частоты
  SYS_REG.ClkEn.bits.CLKEN_CORE = 1;

  // MPORT 40 MHz, RISC 100 MHz
  SYS_REG.CrPll.bits.SEL_PLL_CORE = 0x14;
  SYS_REG.CrPll.bits.PLL_CORE_EN = 1;
  SYS_REG.CrPll.bits.SEL_PLL_MPORT = 8;
  SYS_REG.CrPll.bits.PLL_MPORT_EN = 1;
}

// функции, реализующие операции работы с памятью

// функция компоновки команды NAND-flash
void SetCommand(unsigned int CMD, unsigned int BN, unsigned int command) {
  unsigned int addr;

  addr = MT29F8G_NAND_BASE_ADDR | (CMD << 20) | (BN << 16);
  *((unsigned int *)addr) = command;
}

// функция выполнения команды READ STATUS и анализ прочитанного статуса
unsigned int Read_Status() {
  unsigned int status = 0;

  // ждем, пока в регистре Status NAND-flash не установится флаг READY
  status = 0;
  SetCommand(1, 0, MT29F8G_STATUS);  // chanched
  // чтение ячейки 0
  status = MT29F8G_NAND_BASE_READ_STATUS;
  return status;
}

// функция анализа статуса на бит READY
void Ready_Check() {
  unsigned int status = 0;
  while ((status & MT29F8G_READY) == 0) {
    status = Read_Status();
  }
  status = 0;
}

// функция инициализации регистров параметров и управления NAND-flash
void NDF_init() {
  //	MPORT.Cscon0.data = 0x1011FC;
  MPORT.Cscon0.bits.CSBA = 0x11;

  MPORT.Cscon2.bits.CSMASK =
      0xFF;  // Разряды маски 31:24 при определении базового адреса блока памяти
  MPORT.Cscon2.bits.WS =
      0x2;  // Число тактов ожидания при обращении к блоку памяти
  MPORT.Cscon2.bits.E = 1;  // Разрешение формирования сигнала nCS - – разрешено
  MPORT.Cscon2.bits.T = 1;  // Тип памяти блока памяти - асинхронная NAND FLASH

  MPORT.Ndfpsr.data = 0x20000550;
  MPORT.Ndftmw.data = 0x05030100;
  MPORT.Ndftmr.data = 0x03312100;
}

//
// функция записи в память PROGRAM_PAGE:
// -<_80h_>-<addr_col>-<addr_col>-<addr_col>-<addr_row>-<addr_row>-<addr_row>-<DIN>-...-<DIN>-<_10h_>
void Program_Page(unsigned int page_addr, unsigned int *array) {
  // разрешаем програмирование
  // для формирования команды PROGRAM PAGE необходимо 5 байтов адреса

  SetCommand(
      1, 3,
      (MT29F8G_PROGRAM_BEGIN |
       page_addr << 24));  // Выполняется цикл записи команды и три цикла записи
                           // адреса. По шине D[7:0] последовательно передаются
                           // байты данных с номерами 0, 1, 2, 3
  SetCommand(
      2, 1,
      MT29F8G_NAND_BASE_ADDR);  // Выполняется два цикла записи адреса.
                                // По шине D[7:0] последовательно передаются
                                // нулевой и первый байты данных

  // обмен по DMA
  // Настраиваем DMA  на прием
  DMA_MEM_CH00.IR0.data =
      MT29F8G_NAND_BASE_ADDR -
      0x80000000;  // физический адрес первого элемента массива-приемника
  DMA_MEM_CH00.IR1.data =
      ((unsigned int)&array[0]) -
      0xA0000000;  // физический адрес первого элемента массива-источника
  DMA_MEM_CH00.OR.data =
      0x00010000;  // Старшая часть регистра задает смещение регистра IR1, а
                   // младшая часть - смещение регистра IR0 после передачи
                   // каждого слова

  DMA_MEM_CH00.CSR.data = ((MT29F8G_PAGE_SIZE - 1) << 16) |  // WCX
                          (1 << 1) |                         // DIR =1
                          1;                                 // RUN = 1

  for (int i = 0; i < 0x100000; i++)  // Добавляем задержку, чтобы не подать
    asm("nop");                       // команду PROGRAM_END слишком рано

  // обнуляем регистры
  DMA_MEM_CH00.CSR.data = 0;
  DMA_MEM_CH00.IR0.data = 0;
  DMA_MEM_CH00.IR1.data = 0;

  // завершаем программирование командой 10h
  SetCommand(3, 0, MT29F8G_PROGRAM_END);

  // контролируем процесс записи выполнением команды READ STATUS:
  // ждем, пока в регистре Status NAND-flash не установится флаг READY
  // анализ статуса на бит READY
  Ready_Check();
}

// функция сброса RESET
void Reset() {
  SetCommand(1, 0, MT29F8G_RESET);
  // ожидаем выполнения операции
  // выполнение команды READ STATUS:
  // анализ статуса на бит READY
  Ready_Check();
}

// функция очищения памяти ERASE - ERASE_BLOCK Operation (60h-D0h)
void Erase(unsigned int erased_bl_addr) {
  // первые 3 цикла очищения
  SetCommand(1, 3, MT29F8G_ERASE_BLOCK_BEGIN);  //((erased_bl_addr<<8) |
  // завершающий цикл очищения
  SetCommand(1, 0, MT29F8G_ERASE_BLOCK_END);

  // контролируем процесс записи выполнением команды READ STATUS:
  // ждем, пока в регистре Status NAND-flash не установится флаг READY
  // анализ статуса на бит READY
  Ready_Check();
}

// функция чтения READ_PAGE
// -<_0h_>-<addr_col>-<addr_col>-<addr_row>-<addr_row>-<addr_row>-<addr_row>-<_30h_>
void Read_Page(unsigned int page_addr, unsigned int *array) {
  // задаем режим READ_PAGE (0-30h)
  SetCommand(1, 3,
             (MT29F8G_READ_PAGE_BEGIN |
              page_addr << 24));  // Выполняется цикл записи команды и три цикла
                                  // записи адреса.  //(page_addr&0xFFFF<<8) |
                                  // По шине D[7:0] последовательно передаются
                                  // байты данных с номерами 0, 1, 2, 3
  SetCommand(3, 2,
             MT29F8G_READ_PAGE_END);  // Выполняется два цикла записи адреса и
                                      // цикл записи команды. По шине D[7:0]
                                      // последовательно передаются нулевой,
                                      // первый и второй байты данных

  // обмен по DMA
  // Настраиваем DMA  на прием
  DMA_MEM_CH00.IR0.data =
      ((unsigned int)&array[0]) -
      0xA0000000;  // физический адрес первого элемента массива-приемника
  DMA_MEM_CH00.IR1.data =
      MT29F8G_NAND_BASE_ADDR -
      0x80000000;  // физический адрес первого элемента массива-источника
  DMA_MEM_CH00.OR.data =
      0x00000001;  // Старшая часть регистра задает смещение регистра IR1, а
                   // младшая часть - смещение регистра IR0 после передачи
                   // каждого слова

  DMA_MEM_CH00.CSR.data = ((MT29F8G_PAGE_SIZE - 1) << 16) |  // WCX
                          (1 << 1) |                         // DIR =1
                          1;                                 // RUN = 1

  for (int i = 0; i < 0x100000;
       i++)  // Добавляем задержку, чтобы не попасть в Ready_Check слишком рано
    asm("nop");

  // обнуляем регистры
  DMA_MEM_CH00.CSR.data = 0;
  DMA_MEM_CH00.IR0.data = 0;
  DMA_MEM_CH00.IR1.data = 0;

  // Проверка готовности памяти
  Ready_Check();
}

// функция отключения защиты от записи
void NWPR_OFF() { MPORT.Ndfwpr.data = 0; }
