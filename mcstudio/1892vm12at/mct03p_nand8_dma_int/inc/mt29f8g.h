// Copyright 2023-2025 RnD Center "ELVEES", JSC
// SPDX-License-Identifier: MIT

#ifndef MT29F8G_H
#define MT29F8G_H

#ifdef __cplusplus
extern "C" {
#endif

// операции с памятью
#define MT29F8G_RESET 0xFF
#define MT29F8G_STATUS 0x70
#define MT29F8G_READ_STATUS_78 0x78
#define MT29F8G_ERASE_BLOCK_BEGIN 0x0000060
#define MT29F8G_ERASE_BLOCK_END 0xD0
#define MT29F8G_PROGRAM_BEGIN 0x80
#define MT29F8G_PROGRAM_END 0x10
#define MT29F8G_READ_PAGE_BEGIN 0x00
#define MT29F8G_READ_PAGE_END 0x300000

// Базовый адрес NAND-flash
#define MT29F8G_NAND_BASE_ADDR 0x80000000

// Данная операция используется для чтения байта состояния памяти NAND FLASH при
// выполнении операции READ STATUS. Данная операция выполняется при любом уровне
// сигнала готовности NAND FLASH без контроля интервала tRR.
#define MT29F8G_NAND_BASE_READ_STATUS \
  (*((unsigned int *)(MT29F8G_NAND_BASE_ADDR | (4 << 20))))

// длина массива
#define MT29F8G_PAGE_SIZE 512

#define MT29F8G_READY (1 << 6)

// функция настройки системных регистров
void Set_Sys_reg();

// функции, реализующие операции работы с памятью:

// функция компоновки команды NAND-flash
void SetCommand(unsigned int CMD, unsigned int BN, unsigned int command);

// функция выполнения команды READ STATUS и анализ прочитанного статуса
unsigned int Read_Status();

// функция анализа статуса на бит READY
void Ready_Check();

// функция инициализации регистров параметров и управления NAND-flash
void NDF_init();

// функция записи в память PROGRAM_PAGE:
// -<_80h_>-<addr_col>-<addr_col>-<addr_col>-<addr_row>-<addr_row>-<addr_row>-<DIN>-...-<DIN>-<_10h_>
void Program_Page(unsigned int page_addr, unsigned int *array);

// функция сброса RESET
void Reset();

// функция очищения памяти ERASE - ERASE_BLOCK Operation (60h-D0h)
void Erase(unsigned int erased_bl_addr);

// функция чтения READ_PAGE
// -<_0h_>-<addr_col>-<addr_col>-<addr_row>-<addr_row>-<addr_row>-<addr_row>-<_30h_>
void Read_Page(unsigned int page_addr, unsigned int *array);

// функция отключения защиты от записи
void NWPR_OFF();

#ifdef __cplusplus
}
#endif

#endif
