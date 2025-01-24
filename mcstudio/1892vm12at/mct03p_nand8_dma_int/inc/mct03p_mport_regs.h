// Copyright 2023-2025 RnD Center "ELVEES", JSC
// SPDX-License-Identifier: MIT

//*******************************************************************************
// Пример использования смотри в < mct03p_dma_mem_ch_regs.h >
//
//******************************************************************************/

#ifndef MCT03P_MPORT_REGS_H_
#define MCT03P_MPORT_REGS_H_

//==============================================================================
// CSCON0 - CSCON2
//==================================================
struct __attribute__((packed,
                      aligned(4))) MPORT_CSCON_BITS {  // bits  description
  Uint16 CSMASK : 8;  // Разряды маски 31:24 при определении базового адреса
                      // блока памяти.
  Uint16 CSBA : 8;    // Разряды 31:24 базового адреса блока памяти.
  Uint16 WS : 4;      // Число тактов ожидания при обращении к блоку памяти.
  Uint16 E : 1;       // Разрешение формирования сигнала nCS[0].
  Uint16 T : 2;       // Тип памяти блока памяти.
  Uint16 FX16 : 1;    // Разрядность блока, если он сконфигурирован как память
                      // NAND FLASH
  Uint16 rsrv_1 : 8;  // Резерв
};

union MPORT_CSCON_REG {
  Uint32 data;
  struct MPORT_CSCON_BITS bits;
};

//==================================================
// CSCON3
//==================================================
struct __attribute__((packed,
                      aligned(4))) MPORT_CSCON3_BITS {  // bits  description
  Uint16 rsrv_1 : 16;                                   // Резерв
  Uint16 WS : 4;    // Число тактов ожидания при обращении к памяти блока
  Uint16 ADDR : 2;  // Используются при программной записи данных в 8-разрядную
                    // асинхронную память
  Uint16 rsrv_2 : 1;  // Резерв
  Uint16 FW : 1;    // Порт входного сигнала FW.Определяет разрядность блока при
                    // BOOT = 01
  Uint16 BOOT : 2;  // Cостояние сигналов на одноименных входах микропроцессора
  Uint16 rsrv_3 : 5;  // Резерв
  Uint16 OVER : 1;    // Признак того, что при обмене данными с любым блоком
                      // асинхронной памяти
};

union MPORT_CSCON3_REG {
  Uint32 data;
  struct MPORT_CSCON3_BITS bits;
};

//==================================================
// CSCON4
//==================================================
struct __attribute__((packed, aligned(4))) MPORT_CSCON4_BITS {
  Uint16 rsvd_1 : 16;  // Резерв
  Uint16 WS : 4;       // Число тактов ожидания при обращении к блоку памяти.
  Uint16 rsrv_2 : 12;  // Резерв
};

union MPORT_CSCON4_REG {
  Uint32 data;
  struct MPORT_CSCON4_BITS bits;
};

//==================================================
// SDRCON
//==================================================
struct __attribute__((packed,
                      aligned(4))) MPORT_SDRCON_BITS {  // bits  description
  Uint16 PS : 3;      // Размер страницы микросхем SDRAM, подключенных к MPORT
  Uint16 rsrv_1 : 1;  // Резерв
  Uint16 CL : 3;      // Задержка данных при чтении (CAS latency)
  Uint16 rsrv_2 : 9;  // Резерв
  Uint16 TRFR : 14;   // Период регенерации SDRAM в тактах частоты SCLK
  Uint16 rsrv_3 : 2;  // Резерв
};

union MPORT_SDRCON_REG {
  Uint32 data;
  struct MPORT_SDRCON_BITS bits;
};

//==================================================
// SDRTMR
//==================================================
struct __attribute__((packed,
                      aligned(4))) MPORT_SDRTMR_BITS {  // bits  description
  Uint16 TWR : 2;     // Минимальная задержка между записью данных и командой
                      // Precharge(Write recovery).
  Uint16 rsrv_1 : 2;  // Резерв
  Uint16 TRP : 2;     // Минимальный период команд Precharge
  Uint16 rsrv : 2;    // Резерв
  Uint16 TRCD : 2;  // Минимальная задержка между командами Active и  Read/Write
  Uint16 rsrv_2 : 6;  // Резерв
  Uint16 TRAS : 4;  // Минимальная задержка между командами Active и Precharge.
  Uint16 TRFC : 4;  // Минимальный интервал между командами Refresh
  Uint16 TRC : 4;   // Минимальный интервал между командами ACTIVE для одного и
                    // того же банка
  Uint16 rsrv_3 : 4;  // Резерв
};

union MPORT_SDRTMR_REG {
  Uint32 data;
  struct MPORT_SDRTMR_BITS bits;
};

//==================================================
// SDRCSR
//==================================================
struct __attribute__((packed,
                      aligned(4))) MPORT_SDRCSR_BITS {  // bits  description
  Uint16 INIT : 1;  // выполняет инициализацию SDRAM с параметрами
  Uint16 AREF : 1;  // режим авторегенерации SDRAM / признак окончания команды.
  Uint16 SREF : 1;  // режим саморегенерации / признак окончания команды.
  Uint16
      PWDN : 1;  // режим пониженного потребления / признак окончания команды.
  Uint16 EXIT : 1;     // вывод SDRAM из режимов саморегенерации и пониженного
                       // потребления / признак окончания команды.
  Uint32 rsvd_1 : 27;  // Резерв
};

union MPORT_SDRCSR_REG {
  Uint32 data;
  struct MPORT_SDRCSR_BITS bits;
};

//==================================================
// CSR_EXT
//==================================================
struct __attribute__((packed,
                      aligned(4))) MPORT_CSR_EXT_BITS {  // bits  description
  Uint16 MODE : 2;                                       // Режим работы памяти
  Uint16 NEMPTY : 1;  // Признак наличия данных в FIFO ошибочных адресов
  Uint16 RMW : 1;  // Разрешение операции чтение-модификация-запись в режиме без
                   // коррекции ошибок
  Uint16
      ROM : 1;  // Признак отключения контроля по Хеммингу для блока памяти 3:
  Uint16 rsrv_1 : 3;    // Резерв
  Uint16 CNT_DERR : 8;  // Счетчик двойных ошибок в данных
  Uint16 NUM_SERR : 8;  // Если cnt_Serr > num_Serr, то формируется запрос на
                        // прерывание
  Uint16 CNT_SERR : 8;  // Счетчик одиночных ошибок в данных
};

union MPORT_CSR_EXT_REG {
  Uint32 data;
  struct MPORT_CSR_EXT_BITS bits;
};

//==================================================
// AERROR_EXT
//==================================================
struct __attribute__((packed,
                      aligned(4))) MPORT_AERROR_EXT_BITS {  // bits  description
  Uint16 CODE_ERR : 2;                                      // Код ошибки
  Uint32 ADDR_ERR : 30;  // Разряды 31:2 физического адреса ячейки памяти, при
                         // чтении из которой обнаружена ошибка
};

union MPORT_AERROR_EXT_REG {
  Uint32 data;
  struct MPORT_AERROR_EXT_BITS bits;
};

//==================================================
// NDFPSR
//==================================================
struct __attribute__((packed,
                      aligned(4))) MPORT_NDFPSR_BITS {  // bits  description
  Uint16 TRB : 1;     // Признак переключения входного сигнала RB
  Uint16 TRB2 : 1;    // Признак переключения входного сигнала RB2
  Uint16 rsvd_1 : 2;  // Резерв
  Uint16 TWW : 4;  // Минимальная задержка между изменением режима защиты памяти
                   // и следующей операцией запись
  Uint16 TCCS : 8;    // Минимальная задержка между командой изменения
                      // адреса столбца и следующей операцией с NAND FLASH
  Uint16 RB : 1;      // Порт входного сигнала RB
  Uint16 RB2 : 1;     // Порт входного сигнала RB2
  Uint16 rsvd_2 : 5;  // Резерв
  Uint16 FW : 1;      // Порт входного сигнала FW
  Uint16 BOOT : 2;    // Порт одноименных входных сигналов
  Uint16 rsvd_3 : 2;  // Резерв
  Uint16 TRR : 4;     // Минимальная задержка между переключением сигнала
                   // готовности NAND FLASH из низкого уровня в высокий уровень
                   // и следующей операцией чтения
};

union MPORT_NDFPSR_REG {
  Uint32 data;
  struct MPORT_NDFPSR_BITS bits;
};

//==================================================
// NDFTMW
//==================================================
struct __attribute__((packed,
                      aligned(4))) MPORT_NDFTMW_BITS {  // bits  description
  Uint16 TWP : 4;   // Длительность низкого уровня сигнала nWEF
  Uint16 TWH : 4;   // Длительность удержания высокого уровня сигнала nWEF в
                    // цикле записи
  Uint16 TWC : 5;   // Длительность цикла сигнала nWEF
  Uint16 TCS : 3;   // Длительность предустановки nCS в цикле записи
  Uint16 TADL : 8;  // Минимальная задержка между последней фазой адреса и
                    // записью данных
  Uint16 TRHW : 8;  // Минимальная задержка между последним циклом чтения и
                    // началом цикла записи
};

union MPORT_NDFTMW_REG {
  Uint32 data;
  struct MPORT_NDFTMW_BITS bits;
};

//==================================================
// NDFTMR
//==================================================
struct __attribute__((packed,
                      aligned(4))) MPORT_NDFTMR_BITS {  // bits  description
  Uint16 TRPF : 4;  // Длительность низкого уровня сигнала nREF
  Uint16 TREH : 4;  // Длительность удержания высокого уровня сигнала nREF
  Uint16 TRCF : 5;  // Длительность цикла сигнала nREF
  Uint16 TCEA : 3;  // Готовность данных после установки низкого уровня сигнала
                    // nCS в цикле чтения
  Uint16 TREA : 4;  // Готовность данных после установки низкого уровня сигнала
                    // nREF в цикле чтения
  Uint16 TCHZ : 4;  // Максимальная задержка между установкойвысокого уровня
                    // сигнала nCS и переходом шины данных памяти в
                    // высокоимпедансное состояние после цикла чтения
  Uint16 TWHR : 8;  // Минимальная задержка между последним циклом записи и
                    // чтением данных
};

union MPORT_NDFTMR_REG {
  Uint32 data;
  struct MPORT_NDFTMR_BITS bits;
};

//==================================================
// NDFWPR
//==================================================
struct __attribute__((packed,
                      aligned(4))) MPORT_NDFWPR_BITS {  // bits  description
  Uint16 WP : 1;       // Порт выходного сигнала nWP
  Uint16 WP2 : 1;      // Порт выходного сигнала nWP2
  Uint32 rsvd_1 : 30;  // Резерв
};

union MPORT_NDFWPR_REG {
  Uint32 data;
  struct MPORT_NDFWPR_BITS bits;
};

//==================================================
// NRFTMR
//==================================================
struct __attribute__((packed,
                      aligned(4))) MPORT_NRFTMR_BITS {  // bits  description
  Uint16 FPS : 4;     // Размер страницы микросхем NOR FLASH
  Uint16 TAVAV : 4;   // Длительность низкого уровня сигнала nRD
  Uint16 TAVAV1 : 5;  // Минимальная задержка между изменением адреса и
                      // готовностью данных при чтении второго и последующих
                      // слов страницы
  Uint16 TGHQZ : 3;   // Максимальная задержка между установкойвысокого
                      // уровня сигнала nRD и переходом шины данных памяти
  Uint16 TWHWL : 4;   // Длительность высокого уровня сигнала nWE в цикле записи
  Uint16 TWLWH : 4;   // Длительность низкого уровня сигнала nWE в цикле записи
  Uint16 TWHQV : 8;   // Минимальная задержка между переключением сигнала nWE
};

union MPORT_NRFTMR_REG {
  Uint32 data;
  struct MPORT_NRFTMR_BITS bits;
};

//==============================================================================
// MPORT структура
//==============================================================================
typedef volatile struct {
  union MPORT_CSCON_REG Cscon0;  // 0 Регистр конфигурации блока внешней памяти,
                                 // подключаемого к выводу nCS[0]
  union MPORT_CSCON_REG Cscon1;  // 4 Регистр конфигурации блока внешней памяти,
                                 // подключаемого к выводу nCS[1]
  union MPORT_CSCON_REG Cscon2;  // 8 Регистр конфигурации блока внешней памяти,
                                 // подключаемого к выводу nCS[2]
  union MPORT_CSCON3_REG Cscon3;  // C Регистр конфигурации блока внешней
                                  // памяти, подключаемого к выводу nCS[3]
  union MPORT_CSCON4_REG
      Cscon4;  // 10 Регистр конфигурации внешней памяти, не вошедшей
               //    в блоки памяти, определяемые регистрами CSCON3 - CSCON0
  union MPORT_SDRCON_REG Sdrcon;  // 14 Регистр конфигурации SDRAM.
  union MPORT_SDRTMR_REG Sdrtmr;  // 18 Регистр параметров SDRAM
  union MPORT_SDRCSR_REG Sdrcsr;  // 1C Регистр управления и состояния SDRAM
  union DATA_REG_COMMON_UNION reserve_20;  // 20

  union MPORT_CSR_EXT_REG
      CsrExt;  // 24 Регистр управления режимами контроля внешней памяти
  union MPORT_AERROR_EXT_REG AerrorExt;  // 28 Регистр ошибок внешней памяти
  union MPORT_NRFTMR_REG Nrftmr;         // 2C Регистр параметров NOR FLASH
  union MPORT_NDFPSR_REG
      Ndfpsr;  // 30 Регистр параметров и состояния памяти NAND FLASH
  union MPORT_NDFTMW_REG Ndftmw;  // 34 Регистр параметров записи NAND FLASH
  union MPORT_NDFTMR_REG Ndftmr;  // 38 Регистр параметров чтения NAND FLASH
  union MPORT_NDFWPR_REG Ndfwpr;  // 3C Регистр защиты памяти NAND FLASH
} MPORT_REGS_TYPE;

//==================================================
//	Макрос
//==================================================
#define MPORT (*((MPORT_REGS_TYPE*)MPORT_ADDR))
//==============================================================================

#endif /* MCT03P_MPORT_REGS_H_ */
