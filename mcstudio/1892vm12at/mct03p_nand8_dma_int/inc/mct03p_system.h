// Copyright 2023-2025 RnD Center "ELVEES", JSC
// SPDX-License-Identifier: MIT

//*******************************************************************************
//  Пример использования смотри в < mct03p_dma_mem_ch_regs.h >
//
//******************************************************************************/
#ifndef MCT03P_SYSTEM_REGS_H_
#define MCT03P_SYSTEM_REGS_H_

#include "mct03p_mem_map.h"

//==============================================================================
// CR_PLL
//==================================================
struct __attribute__((packed,
                      aligned(4))) SYSTEM_CR_PLL_BITS {  // bits  description
  unsigned short SEL_PLL_CORE : 7;   // Коэффициент умножения/деления входной
                                     // частоты PLL_CORE
  unsigned short PLL_CORE_EN : 1;    // Режим работы PLL_CORE
  unsigned short SEL_PLL_MPORT : 7;  // Коэффициент умножения/деления входной
                                     // частоты PLL_MPORT
  unsigned short PLL_MPORT_EN : 1;   // Режим работы PLL_MPORT
  unsigned short rsrv_1 : 16;        // Резерв
};

union SYSTEM_CR_PLL_REG {
  unsigned int data;
  struct SYSTEM_CR_PLL_BITS bits;
};

//==================================================
// CLK_EN
//==================================================
struct __attribute__((packed,
                      aligned(4))) SYSTEM_CLK_EN_BITS {  // bits  description
  unsigned short CLKEN_CORE : 1;   // Управление включением тактовой частоты
  unsigned short rsrv_1 : 7;       // Резерв
  unsigned short CLKEN_MFBSP : 2;  // Управление включением тактовой частоты
                                   // MFBSP, поступающей от PLL_CORE
  unsigned short rsrv_2 : 2;       // Резерв
  unsigned short CLKEN_DMA : 2;    // Управление включением тактовой частоты
                                   // каналов DMA MEM_CH
  unsigned short rsrv_3 : 10;      // Резерв
  unsigned short CLKEN_SWIC : 2;   // Управление включением тактовой частоты
                                   // SWIC1,0 поступающей от PLL_CORE
  unsigned short CLKEN_GSWIC : 2;  // Управление включением тактовой частоты
                                   // GSWIC1,0 поступающей от PLL_CORE
  unsigned short rsrv_4 : 4;       // Резерв
};

union SYSTEM_CLK_EN_REG {
  unsigned int data;
  struct SYSTEM_CLK_EN_BITS bits;
};

//==================================================
// CSR
//==================================================
struct __attribute__((packed,
                      aligned(4))) SYSTEM_SCSR_BITS {  // bits  description
  unsigned short FM : 1;       // Режим преобразования виртуальных адресов CPU в
                               // физические адреса
  unsigned short TR_CRAM : 1;  // Режим размещения векторов прерываний при BEV =
                               // 0 (регистр Status CPU)
  unsigned short rsrv_1 : 9;   // Резерв
  unsigned short TST_CACHE : 1;  // Режим работы кэш программ и кэш данных
  unsigned short FLUSH_I : 1;    // При записи 1 в данный разряд кэш команд CPU
                               // останавливается в исходное состояние, то есть
                               // ее содержимое девалидируется
  unsigned short FLUSH_D : 1;  // При записи 1 в данный разряд кэш данных CPU
                               // останавливается в исходное состояние, то есть
                               // ее содержимое девалидируется
  unsigned int rsrv_2 : 17;    // Резерв
};

union SYSTEM_SCSR_REG {
  unsigned int data;
  struct SYSTEM_SCSR_BITS bits;
};

//==================================================
// QSTR0
//==================================================
struct __attribute__((packed,
                      aligned(4))) SYSTEM_QSTR0_BITS {  // bits  description
  unsigned short IRQ0 : 1;     // Внешние прерывание nIRQ0
  unsigned short IRQ1 : 1;     // Внешние прерывание nIRQ1
  unsigned short IRQ2 : 1;     // Внешние прерывание nIRQ2
  unsigned short IRQ3 : 1;     // Внешние прерывание nIRQ3
  unsigned short UART0 : 1;    // Прерывание от UART0
  unsigned short UART1 : 1;    // Прерывание от UART1
  unsigned short rsrv_1 : 14;  // Резерв
  unsigned short WDT : 1;      // Прерывание от таймера WDT
  unsigned short IT0 : 1;      // Прерывание от таймера IT0
  unsigned short IT1 : 1;      // Прерывание от таймера IT1
  unsigned short rsrv_2 : 9;   // Резерв
};

union SYSTEM_QSTR0_REG {
  unsigned int data;
  struct SYSTEM_QSTR0_BITS bits;
};

//==================================================
// QSTR1
//==================================================
struct __attribute__((packed,
                      aligned(4))) SYSTEM_QSTR1_BITS {  // bits  description
  unsigned short MEM_CH00 : 1;  // Прерывание от каналов DMA MEM_CH00
  unsigned short MEM_CH01 : 1;  // Прерывание от каналов DMA MEM_CH01
  unsigned short MEM_CH02 : 1;  // Прерывание от каналов DMA MEM_CH02
  unsigned short MEM_CH03 : 1;  // Прерывание от каналов DMA MEM_CH03
  unsigned short rsrv_1 : 4;    // Резерв
  unsigned short MEM_CH10 : 1;  // Прерывание от каналов DMA MEM_CH10
  unsigned short MEM_CH11 : 1;  // Прерывание от каналов DMA MEM_CH11
  unsigned short MEM_CH12 : 1;  // Прерывание от каналов DMA MEM_CH12
  unsigned short MEM_CH13 : 1;  // Прерывание от каналов DMA MEM_CH13
  unsigned int rsrv_2 : 20;     // Резерв
};

union SYSTEM_QSTR1_REG {
  unsigned int data;
  struct SYSTEM_QSTR1_BITS bits;
};

//==================================================
// QSTR2
//==================================================
struct __attribute__((packed,
                      aligned(4))) SYSTEM_QSTR2_BITS {  // bits  description
  unsigned short SW_LINK0 : 1;  // 0  Прерывание SWIC0 – установлено соединение
  unsigned short SW_ERR0 : 1;   // 1  Прерывание SWIC0 – ошибка в канале
  unsigned short SW_TIME0 : 1;  // 2  Прерывание SWIC0 – получен маркер
                                // времени/распределенное прерывание
  unsigned short rsrv_1 : 1;    // 3  Резерв
  unsigned short SW_RX_DES_CH0 : 1;  // 4  Прерывание от канала DMA
                                     // SW_RX_DES_CH0
  unsigned short SW_RX_DAT_CH0 : 1;  // 5  Прерывание от канала DMA
                                     // SW_RX_DAT_CH0
  unsigned short SW_TX_DES_CH0 : 1;  // 6  Прерывание от канала DMA
                                     // SW_TX_DES_CH0
  unsigned short SW_TX_DAT_CH0 : 1;  // 7  Прерывание от канала DMA
                                     // SW_TX_DAT_CH0
  unsigned short SW_LINK1 : 1;  // 8  Прерывание SWIC1 – установлено соединение
  unsigned short SW_ERR1 : 1;   // 9  Прерывание SWIC1 – ошибка в канале
  unsigned short SW_TIME1 : 1;  // 10 Прерывание SWIC1 – получен маркер
                                // времени/распределенное прерывание
  unsigned short rsrv_3 : 1;    // 11 Резерв
  unsigned short SW_RX_DES_CH1 : 1;  // 12 Прерывание от канала DMA
                                     // SW_RX_DES_CH1
  unsigned short SW_RX_DAT_CH1 : 1;  // 13 Прерывание от канала DMA
                                     // SW_RX_DAT_CH1
  unsigned short SW_TX_DES_CH1 : 1;  // 14 Прерывание от канала DMA
                                     // SW_TX_DES_CH1
  unsigned short SW_TX_DAT_CH1 : 1;  // 15 Прерывание от канала DMA
                                     // SW_TX_DAT_CH1
  unsigned short GSW_LINK0 : 1;      // 16 Прерывание GSWIC0 – установлено
                                     // соединение
  unsigned short GSW_ERR0 : 1;       // 17 Прерывание GSWIC0 – ошибка в канале
  unsigned short GSW_TIME0 : 1;      // 18 Прерывание GSWIC0 – получен маркер
                                     // времени/распределенное прерывание
  unsigned short rsrv_4 : 1;         // 19 Резерв
  unsigned short
      GSW_RX_DES_CH0 : 1;  // 20 Прерывание от канала DMA GSW_RX_DES_CH0
  unsigned short
      GSW_RX_DAT_CH0 : 1;  // 21 Прерывание от канала DMA GSW_RX_DAT_CH0
  unsigned short
      GSW_TX_DES_CH0 : 1;  // 22 Прерывание от канала DMA GSW_TX_DES_CH0
  unsigned short
      GSW_TX_DAT_CH0 : 1;        // 23 Прерывание от канала DMA GSW_TX_DAT_CH0
  unsigned short GSW_LINK1 : 1;  // 24 Прерывание GSWIC1 – установлено
                                 // соединение
  unsigned short GSW_ERR1 : 1;   // 25 Прерывание GSWIC1 – ошибка в канале
  unsigned short GSW_TIME1 : 1;  // 26 Прерывание GSWIC1 – получен маркер
                                 // времени/распределенное прерывание
  unsigned short rsrv_5 : 1;     // 27 Резерв
  unsigned short
      GSW_RX_DES_CH1 : 1;  // 28 Прерывание от канала DMA GSW_RX_DES_CH1
  unsigned short
      GSW_RX_DAT_CH1 : 1;  // 29 Прерывание от канала DMA GSW_RX_DAT_CH1
  unsigned short
      GSW_TX_DES_CH1 : 1;  // 30 Прерывание от канала DMA GSW_TX_DES_CH1
  unsigned short
      GSW_TX_DAT_CH1 : 1;  // 31 Прерывание от канала DMA GSW_TX_DAT_CH1
};

union SYSTEM_QSTR2_REG {
  unsigned int data;
  struct SYSTEM_QSTR2_BITS bits;
};

//==================================================
// QSTR3
//==================================================
struct __attribute__((packed,
                      aligned(4))) SYSTEM_QSTR3_BITS {  // bits  description
  unsigned short
      INT_HMCRAM : 4;  // Прерывания по контролю кода Хемминга CRAM[3:0]
  unsigned short
      INT_HMICACHE : 1;  // Прерывание по контролю кода Хемминга от ICACHE
  unsigned short
      INT_HMDCACHE : 1;       // Прерывание по контролю кода Хемминга DCACHE
  unsigned short rsrv_1 : 1;  // Резерв
  unsigned short
      INT_HMMPORT : 1;  // Прерывание по контролю кода Хемминга внешней памяти
  unsigned int rsrv_2 : 24;  // Резерв
};

union SYSTEM_QSTR3_REG {
  unsigned int data;
  struct SYSTEM_QSTR3_BITS bits;
};

//==================================================
// QSTR4
//==================================================
struct __attribute__((packed,
                      aligned(4))) SYSTEM_QSTR4_BITS {  // bits  description
  unsigned short SRQ0 : 1;          // 0  Запрос обслуживания от порта MFBSP0
  unsigned short MFBSP_RXBUF0 : 1;  // 1  Формируется, если порт MFBSP0 включен
                                    // на прием данных
  unsigned short MFBSP_TXBUF0 : 1;  // 2  Формируется, если порт MFBSP0 включен
                                    // на передачу данных
  unsigned short rsrv_1 : 1;        // 3  Резерв
  unsigned short MFBSP_TX_CH0 : 1;  // 4  Прерывание от канала DMA порта MFBSP0
                                    // при передаче данных
  unsigned short MFBSP_RX_CH0 : 1;  // 5  Прерывание от канала DMA порта MFBSP0
                                    // при приеме данных
  unsigned short rsrv_2 : 2;        // 7:6 Резерв
  unsigned short SRQ1 : 1;          // 8  Запрос обслуживания от порта MFBSP1
  unsigned short MFBSP_RXBUF1 : 1;  // 9  Формируется, если порт MFBSP1 включен
                                    // на прием данных
  unsigned short MFBSP_TXBUF1 : 1;  // 10 Формируется, если порт MFBSP1 включен
                                    // на передачу данных
  unsigned short rsrv_3 : 1;        // 11 Резерв
  unsigned short MFBSP_TX_CH1 : 1;  // 12 Прерывание от канала DMA порта MFBSP1
                                    // при передаче данных
  unsigned short MFBSP_RX_CH1 : 1;  // 13 Прерывание от канала DMA порта MFBSP1
                                    // при приеме данных
  unsigned int rsrv_4 : 18;         // 31:14 Резерв
};

union SYSTEM_QSTR4_REG {
  unsigned int data;
  struct SYSTEM_QSTR4_BITS bits;
};

//==================================================
// IRQM
//==================================================
struct __attribute__((packed,
                      aligned(4))) SYSTEM_IRQM_BITS {  // bits  description
  unsigned short
      IRQ_NULL : 4;  // Обнуление запомненных прерываний при IRQ_MODE = 1
  unsigned short rsrv_1 : 4;    // Резерв
  unsigned short IRQ_MODE : 4;  // Режим приема внешних прерываний  nIRQ[3:0]
  unsigned int rsrv_2 : 20;     // Резерв
};

union SYSTEM_IRQM_REG {
  unsigned int data;
  struct SYSTEM_IRQM_BITS bits;
};

//==============================================================================
// SYSTEM структура
//==============================================================================
typedef volatile struct {
  union SYSTEM_CR_PLL_REG CrPll;  // 00 Регистр управления PLL
  union SYSTEM_CLK_EN_REG
      ClkEn;  // 04 Регистр управления отключением частоты от устройств
  union SYSTEM_SCSR_REG Csr;              // 08 Регистр управления и состояния
  union DATA_REG_COMMON_UNION Reserve0C;  // 0C
  union SYSTEM_QSTR0_REG
      Maskr0;  // 10 Регистр маски прерываний из регистра QSTR0
  union SYSTEM_QSTR0_REG Qstr0;  // 14 Регистр запросов прерываний от IT0, IT1,
                                 // WDT, UART0, UART1, nIRQ[3:0]
  union SYSTEM_QSTR1_REG
      Maskr1;  // 18 Регистр маски прерываний из регистра QSTR1
  union SYSTEM_QSTR1_REG
      Qstr1;  // 1C Регистр запросов прерываний от каналов DMA MEM_CH0, MEM_CH1
  union SYSTEM_QSTR2_REG
      Maskr2;  // 20 Регистр маски прерываний из регистра QSTR2
  union SYSTEM_QSTR2_REG
      Qstr2;  // 24 Регистр запросов прерываний от GSWIC0, GSWIC1, SWIC0, SWIC1
  union SYSTEM_QSTR3_REG
      Maskr3;  // 28 Регистр маски прерываний из регистра QSTR3
  union SYSTEM_QSTR3_REG
      Qstr3;  // 2C Регистр запросов прерываний от контроля кодом Хэмминга
  union SYSTEM_IRQM_REG IRQM;  // 30 Регистр управления режимом приема внешних
                               // прерываний nIRQ[3:0]
  union DATA_REG_COMMON_UNION reserve_34;  // 34
  union SYSTEM_QSTR4_REG
      Maskr4;  // 38 Регистр маски прерываний из регистра QSTR4
  union SYSTEM_QSTR4_REG
      Qstr4;  // 3C Регистр запросов прерываний от MFBSP0, MFBSP1
} SYSTEM_REGS_TYPE;

//==================================================
//	Макрос
//==================================================
#define SYS_REG (*((SYSTEM_REGS_TYPE*)SYS_REG_ADDR))
//==============================================================================

#endif /* MCT03P_SYSTEM_REGS_H_ */
