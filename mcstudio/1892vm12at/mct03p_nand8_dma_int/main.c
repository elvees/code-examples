// Copyright 2023-2025 RnD Center "ELVEES", JSC
// SPDX-License-Identifier: MIT

#include "mct03p.h"
#include "mct03p_dma_regs.h"
#include "mt29f8g.h"
#include "risc_interrupt.h"

#define ERASED_BLOCK_ADDR 0x0  // адрес очищаемого блока,
// при выполнении операции Erase Block учитывается только 3-байтовый адрес ряда,
// адрес колонки дешифратором не учитывается

// Адрес страницы
#define PAGE_ADDR_WR 0x0  // адрес страницы для записи
#define PAGE_ADDR_R 0x0   // адрес страницы для чтения

unsigned int OutputArray[MT29F8G_PAGE_SIZE] __attribute__((aligned(8)));
unsigned int InputArray[MT29F8G_PAGE_SIZE] __attribute__((aligned(8)));

unsigned int Verify_Flag = 0;  // флаг корректности полученных данных
unsigned int ExitStatus = 1;

// функция заполнения массива числами от 0 до len
void FillArray(unsigned int *array, unsigned int len) {
  unsigned int i;

  for (i = 0; i < len * 4; i += 1) {
    ((unsigned char *)array)[i] = i;
  }
}

// функция сравнивает значения элементов массива
// при корректных значениях элементов возвращает единицу
unsigned int VerifyArray(unsigned int *array1, unsigned int *array2,
                         unsigned int len) {
  unsigned int i;

  for (i = 0; i < len; i++) {
    if (array1[i] != array2[i]) {
      return 0;
    }
  }

  return 1;
}

// функция заполняет массив нулями
void ZeroArray(unsigned int *array, unsigned int len) {
  unsigned int i;

  for (i = 0; i < len; i++) {
    array[i] = 0;
  }
}

void int_handler(int a) {
  int csr =
      DMA_MEM_CH00.CSR.data;  // Читаем регистр CSR, чтобы сбросить прерывание

  asm("nop");
}

int main() {
  risc_enable_interrupts();
  risc_set_interrupts_vector(INTH_B8000180);
  risc_enable_interrupt(RISC_INT_MEMCH0, 0);
  risc_register_interrupt(int_handler, RISC_INT_MEMCH0);

  // инициализируем регистр управления PLL и регистр управления отключением
  // частоты устройств
  Set_Sys_reg();

  ZeroArray(InputArray, MT29F8G_PAGE_SIZE);
  FillArray(OutputArray, MT29F8G_PAGE_SIZE);

  // инициализируем регистры параметров и управления NAND-flash
  NDF_init();

  while (1) {
    // выполнение команды RESET
    Reset();

    // отключаем защиту от записи
    NWPR_OFF();

    // очищаем память
    Erase(ERASED_BLOCK_ADDR);

    // записываем массив в память
    Program_Page(PAGE_ADDR_WR, OutputArray);

    // включаем прерывание повторно
    risc_enable_interrupt(RISC_INT_MEMCH0, 0);

    // читаем записанные данные
    Read_Page(PAGE_ADDR_R, InputArray);

    // проверка содержимого входного массива
    Verify_Flag = VerifyArray(InputArray, OutputArray, MT29F8G_PAGE_SIZE);
    if (Verify_Flag == 1) {
      ExitStatus = 0;
      /* Place breakpoint here */
      asm("nop");
    } else {
      ExitStatus = 1;
    }
  }
  return ExitStatus;
}
