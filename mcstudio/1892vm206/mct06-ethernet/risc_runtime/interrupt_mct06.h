// Copyright 2023-2025 RnD Center "ELVEES", JSC
// SPDX-License-Identifier: MIT

#ifndef _INTERRUPT_MCT06_H_
#define _INTERRUPT_MCT06_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
  // QSTR0
  RISC_INT_NIRQ0 = 0,
  RISC_INT_NIRQ1 = 1,
  RISC_INT_NIRQ2 = 2,
  RISC_INT_NIRQ3 = 3,
  RISC_INT_UART = 4,
  RISC_INT_WDT = 20,
  RISC_INT_IT0 = 22,
  RISC_INT_IT1 = 21,

  // QSTR1
  RISC_INT_IT15 = (0x100 | (31)),
  RISC_INT_IT14 = (0x100 | (30)),
  RISC_INT_IT13 = (0x100 | (29)),
  RISC_INT_IT12 = (0x100 | (28)),
  RISC_INT_IT11 = (0x100 | (27)),
  RISC_INT_IT10 = (0x100 | (26)),
  RISC_INT_IT9 = (0x100 | (25)),
  RISC_INT_IT8 = (0x100 | (24)),
  RISC_INT_IT7 = (0x100 | (23)),
  RISC_INT_IT6 = (0x100 | (22)),
  RISC_INT_IT5 = (0x100 | (21)),
  RISC_INT_IT4 = (0x100 | (20)),
  RISC_INT_IT3 = (0x100 | (19)),
  RISC_INT_IT2 = (0x100 | (18)),
  RISC_INT_IT1_CPY = (0x100 | (17)),
  RISC_INT_IT0_CPY = (0x100 | (16)),

  RISC_INT_MEMCH17 = (0x100 | (15)),
  RISC_INT_MEMCH16 = (0x100 | (14)),
  RISC_INT_MEMCH15 = (0x100 | (13)),
  RISC_INT_MEMCH14 = (0x100 | (12)),
  RISC_INT_MEMCH13 = (0x100 | (11)),
  RISC_INT_MEMCH12 = (0x100 | (10)),
  RISC_INT_MEMCH11 = (0x100 | (9)),
  RISC_INT_MEMCH10 = (0x100 | (8)),
  RISC_INT_MEMCH7 = (0x100 | (7)),
  RISC_INT_MEMCH6 = (0x100 | (6)),
  RISC_INT_MEMCH5 = (0x100 | (5)),
  RISC_INT_MEMCH4 = (0x100 | (4)),
  RISC_INT_MEMCH3 = (0x100 | (3)),
  RISC_INT_MEMCH2 = (0x100 | (2)),
  RISC_INT_MEMCH1 = (0x100 | (1)),
  RISC_INT_MEMCH0 = (0x100 | (0)),
  RISC_INT_MEMCH,
  RISC_INT_MEMCH_MAX = RISC_INT_MEMCH17,

  // QSTR2
  RISC_INT_SW_SPFMIC0_LINK = (0x200 | (0)),
  RISC_INT_SW_SPFMIC0_ERR = (0x200 | (1)),
  RISC_INT_SW_SPFMIC0_TIME = (0x200 | (2)),
  RISC_INT_SW_SPFMIC0_RX_DES_CH0 = (0x200 | (3)),
  RISC_INT_SW_SPFMIC0_RX_DAT_CH0 = (0x200 | (4)),
  RISC_INT_SW_SPFMIC0_TX_DES_CH0 = (0x200 | (5)),
  RISC_INT_SW_SPFMIC0_TX_DAT_CH0 = (0x200 | (6)),
  RISC_INT_SW_SPFMIC1_LINK = (0x200 | (7)),
  RISC_INT_SW_SPFMIC1_ERR = (0x200 | (8)),
  RISC_INT_SW_SPFMIC1_TIME = (0x200 | (9)),
  RISC_INT_SW_SPFMIC1_RX_DES_CH0 = (0x200 | (10)),
  RISC_INT_SW_SPFMIC1_RX_DAT_CH0 = (0x200 | (11)),
  RISC_INT_SW_SPFMIC1_TX_DES_CH0 = (0x200 | (12)),
  RISC_INT_SW_SPFMIC1_TX_DAT_CH0 = (0x200 | (13)),
  RISC_INT_MD_MAC0 = (0x200 | (14)),
  RISC_INT_MAC0_RX_ERROR_IN = (0x200 | (15)),
  RISC_INT_MAC0_RX_INT = (0x200 | (16)),
  RISC_INT_MAC0_TX_ERROR = (0x200 | (17)),
  RISC_INT_MAC0_TX_INT = (0x200 | (18)),
  RISC_INT_DMA_MAC0_RX_DES = (0x200 | (19)),
  RISC_INT_DMA_MAC0_RX_DAT = (0x200 | (20)),
  RISC_INT_DMA_MAC0_TX_DES = (0x200 | (21)),
  RISC_INT_DMA_MAC0_TX_DAT = (0x200 | (22)),
  RISC_INT_MD_MAC1 = (0x200 | (23)),
  RISC_INT_MAC1_RX_ERROR_IN = (0x200 | (24)),
  RISC_INT_MAC1_RX_INT = (0x200 | (25)),
  RISC_INT_MAC1_TX_ERROR = (0x200 | (26)),
  RISC_INT_MAC1_TX_INT = (0x200 | (27)),
  RISC_INT_DMA_MAC1_RX_DES = (0x200 | (28)),
  RISC_INT_DMA_MAC1_RX_DAT = (0x200 | (29)),
  RISC_INT_DMA_MAC1_TX_DES = (0x200 | (30)),
  RISC_INT_DMA_MAC1_TX_DAT = (0x200 | (31)),

  // QSTR3
  // QSTR3
  RISC_INT_HMCRAM0 = (0x300 | (0)),
  RISC_INT_HMCRAM1 = (0x300 | (1)),
  RISC_INT_HMCRAM2 = (0x300 | (2)),
  RISC_INT_HMCRAM3 = (0x300 | (3)),
  RISC_INT_HMICACHE = (0x300 | (4)),
  RISC_INT_HMDCACHE = (0x300 | (5)),
  RISC_INT_HMMPORT = (0x300 | (7)),
  RISC_INT_HMMEM0 = (0x300 | (8)),
  RISC_INT_HMMEM1 = (0x300 | (9)),

  RISC_INT_HmMPORT = (0x300 | (7)),
  RISC_INT_HmDSP0 = (0x300 | (8)),
  RISC_INT_HmDSP1 = (0x300 | (9)),

  RISC_INT_MIL_1_IRQ = (0x300 | (15)),
  RISC_INT_MILL_1_DMA_HI = (0x300 | (14)),
  RISC_INT_MILL_1_DMA_LO = (0x300 | (13)),

  RISC_INT_MIL_0_IRQ = (0x300 | (12)),
  RISC_INT_MILL_0_DMA_HI = (0x300 | (11)),
  RISC_INT_MILL_0_DMA_LO = (0x300 | (10)),

  RISC_INT_IRQ_DMA_MFBSP1 = (0x300 | (29)),
  RISC_INT_ARINC_IRQ = (0x300 | (30)),
  RISC_INT_ARINC_DMA = (0x300 | (31)),

  // QSTR4
  RISC_INT_SW_LINK0 = (0x400 | (0)),
  RISC_INT_SW_ERR0 = (0x400 | (1)),
  RISC_INT_SW_TIME0 = (0x400 | (2)),
  RISC_INT_SW_RX_DES_CH0 = (0x400 | (4)),
  RISC_INT_SW_RX_DAT_CH0 = (0x400 | (5)),
  RISC_INT_SW_TX_DES_CH0 = (0x400 | (6)),
  RISC_INT_SW_TX_DAT_CH0 = (0x400 | (7)),
  RISC_INT_SW_LINK1 = (0x400 | (8)),
  RISC_INT_SW_ERR1 = (0x400 | (9)),
  RISC_INT_SW_TIME1 = (0x400 | (10)),
  RISC_INT_SW_RX_DES_CH1 = (0x400 | (12)),
  RISC_INT_SW_RX_DAT_CH1 = (0x400 | (13)),
  RISC_INT_SW_TX_DES_CH1 = (0x400 | (14)),
  RISC_INT_SW_TX_DAT_CH1 = (0x400 | (15)),
  RISC_INT_SW_LINK2 = (0x400 | (16)),
  RISC_INT_SW_ERR2 = (0x400 | (17)),
  RISC_INT_SW_TIME2 = (0x400 | (18)),
  RISC_INT_SW_RX_DES_CH2 = (0x400 | (20)),
  RISC_INT_SW_RX_DAT_CH2 = (0x400 | (21)),
  RISC_INT_SW_TX_DES_CH2 = (0x400 | (22)),
  RISC_INT_SW_TX_DAT_CH2 = (0x400 | (23)),
  RISC_INT_SW_LINK3 = (0x400 | (24)),
  RISC_INT_SW_ERR3 = (0x400 | (25)),
  RISC_INT_SW_TIME3 = (0x400 | (26)),
  RISC_INT_SW_RX_DES_CH3 = (0x400 | (28)),
  RISC_INT_SW_RX_DAT_CH3 = (0x400 | (29)),
  RISC_INT_SW_TX_DES_CH3 = (0x400 | (30)),
  RISC_INT_SW_TX_DAT_CH3 = (0x400 | (31)),

  RICS_EXC_MOD = 0x801,
  RICS_EXC_TLBL,
  RICS_EXC_TLBS,
  RICS_EXC_ADEL,
  RICS_EXC_ADES,
  RICS_EXC_SYS,
  RICS_EXC_BP,
  RICS_EXC_RI,
  RICS_EXC_CPU,
  RICS_EXC_OV,
  RICS_EXC_TRAP,
  RICS_EXC_FPE,
  RICS_EXC_MCHECK,
  RISC_COMPARE = 0x8001
} RISC_INTERRUPT_TYPE;

#ifdef __cplusplus
}
#endif

#endif  // _INTERRUPT_MCT06_H_
