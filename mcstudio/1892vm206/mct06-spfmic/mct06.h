// Copyright 2023-2025 RnD Center "ELVEES", JSC
// SPDX-License-Identifier: MIT

// ***************** mct06.h ***************************************
//                 Risc-Dsp runtime library
//
// This file implements address of mct-06 registers
//
//
// *******************************************************************
#ifndef ___MCL_MCT06_H___
#define ___MCL_MCT06_H___

#ifdef __cplusplus
extern "C" {
#endif

// DMA parameters defines
#define DMA_CONTROLLERS_NUM (2)
#define DMA_CHANNELS_IN_CONTROLLER (8)
#define DMAR_SIGNALS_NUM (4)

// MCT-06 registers

// DMA MemCh Registers

// MemChi Registers(only for 0-7 channels, 10-17 -- ?)
#define CSR_MemCh(i) *((volatile int *)(0xb82F0000 + 0x80 * i))
#define CP_MemCh(i) *((volatile int *)(0xb82F0004 + 0x80 * i))
#define IR0_MemCh(i) *((volatile int *)(0xb82F0008 + 0x80 * i))
#define IR1_MemCh(i) *((volatile int *)(0xb82F000C + 0x80 * i))
#define OR_MemCh(i) *((volatile int *)(0xb82F0010 + 0x80 * i))
#define Y_MemCh(i) *((volatile int *)(0xb82F0014 + 0x80 * i))
#define RUN_MemCh(i) *((volatile int *)(0xb82F0018 + 0x80 * i))

// MemCh0 Registers
#define CSR_MemCh0 *((volatile int *)0xb82F0000)
#define CP_MemCh0 *((volatile int *)0xb82F0004)
#define IR0_MemCh0 *((volatile int *)0xb82F0008)
#define IR1_MemCh0 *((volatile int *)0xb82F000C)
#define OR_MemCh0 *((volatile int *)0xb82F0010)
#define Y_MemCh0 *((volatile int *)0xb82F0014)
#define RUN_MemCh0 *((volatile int *)0xb82F0018)
// MemCh1 Registers
#define CSR_MemCh1 *((volatile int *)0xb82F0080)
#define CP_MemCh1 *((volatile int *)0xb82F0084)
#define IR0_MemCh1 *((volatile int *)0xb82F0088)
#define IR1_MemCh1 *((volatile int *)0xb82F008C)
#define OR_MemCh1 *((volatile int *)0xb82F0090)
#define Y_MemCh1 *((volatile int *)0xb82F0094)
#define RUN_MemCh1 *((volatile int *)0xb82F0098)
// MemCh2 Registers
#define CSR_MemCh2 *((volatile int *)0xb82F0100)
#define CP_MemCh2 *((volatile int *)0xb82F0104)
#define IR0_MemCh2 *((volatile int *)0xb82F0108)
#define IR1_MemCh2 *((volatile int *)0xb82F010C)
#define OR_MemCh2 *((volatile int *)0xb82F0110)
#define Y_MemCh2 *((volatile int *)0xb82F0114)
#define RUN_MemCh2 *((volatile int *)0xb82F0118)
// MemCh3 Registers
#define CSR_MemCh3 *((volatile int *)0xb82F0180)
#define CP_MemCh3 *((volatile int *)0xb82F0184)
#define IR0_MemCh3 *((volatile int *)0xb82F0188)
#define IR1_MemCh3 *((volatile int *)0xb82F018C)
#define OR_MemCh3 *((volatile int *)0xb82F0190)
#define Y_MemCh3 *((volatile int *)0xb82F0194)
#define RUN_MemCh3 *((volatile int *)0xb82F0198)
// MemCh4 Registers
#define CSR_MemCh4 *((volatile int *)0xb82F0200)
#define CP_MemCh4 *((volatile int *)0xb82F0204)
#define IR0_MemCh4 *((volatile int *)0xb82F0208)
#define IR1_MemCh4 *((volatile int *)0xb82F020C)
#define OR_MemCh4 *((volatile int *)0xb82F0210)
#define Y_MemCh4 *((volatile int *)0xb82F0214)
#define RUN_MemCh4 *((volatile int *)0xb82F0218)
// MemCh5 Registers
#define CSR_MemCh5 *((volatile int *)0xb82F0280)
#define CP_MemCh5 *((volatile int *)0xb82F0284)
#define IR0_MemCh5 *((volatile int *)0xb82F0288)
#define IR1_MemCh5 *((volatile int *)0xb82F028C)
#define OR_MemCh5 *((volatile int *)0xb82F0290)
#define Y_MemCh5 *((volatile int *)0xb82F0294)
#define RUN_MemCh5 *((volatile int *)0xb82F0298)
// MemCh6 Registers
#define CSR_MemCh6 *((volatile int *)0xb82F0300)
#define CP_MemCh6 *((volatile int *)0xb82F0304)
#define IR0_MemCh6 *((volatile int *)0xb82F0308)
#define IR1_MemCh6 *((volatile int *)0xb82F030C)
#define OR_MemCh6 *((volatile int *)0xb82F0310)
#define Y_MemCh6 *((volatile int *)0xb82F0314)
#define RUN_MemCh6 *((volatile int *)0xb82F0318)
// MemCh7 Registers
#define CSR_MemCh7 *((volatile int *)0xb82F0380)
#define CP_MemCh7 *((volatile int *)0xb82F0384)
#define IR0_MemCh7 *((volatile int *)0xb82F0388)
#define IR1_MemCh7 *((volatile int *)0xb82F038C)
#define OR_MemCh7 *((volatile int *)0xb82F0390)
#define Y_MemCh7 *((volatile int *)0xb82F0394)
#define RUN_MemCh7 *((volatile int *)0xb82F0398)

// ARINC429 Registers
#define ARINC_BASE (0xB8300000)
#define ARINC_REGS_ADDR (ARINC_BASE + 0xF00)
#define ARINC_CHANNEL_REGS_ADDR(i) (ARINC_BASE + 0x100 * i)
#define ARINC_DMA_ADDR(i) (ARINC_BASE + 0x1000 + 0x40 * i)

// SWIC Registers
#define SWIC0_BASE (0xB82F9000)
#define SWIC1_BASE (0xB82FA000)
#define SWIC2_BASE (0xB82FB000)
#define SWIC3_BASE (0xB82FC000)

#define SWIC0_DMA_RX_DES_BASE (0xB82FA800)
#define SWIC0_DMA_RX_DAT_BASE (0xB82FA840)
#define SWIC0_DMA_TX_DES_BASE (0xB82FA880)
#define SWIC0_DMA_TX_DAT_BASE (0xB82FA8C0)

#define SWIC1_DMA_RX_DES_BASE (0xB82FA900)
#define SWIC1_DMA_RX_DAT_BASE (0xB82FA940)
#define SWIC1_DMA_TX_DES_BASE (0xB82FA980)
#define SWIC1_DMA_TX_DAT_BASE (0xB82FA9C0)

#define SWIC2_DMA_RX_DES_BASE (0xB82FC800)
#define SWIC2_DMA_RX_DAT_BASE (0xB82FC840)
#define SWIC2_DMA_TX_DES_BASE (0xB82FC880)
#define SWIC2_DMA_TX_DAT_BASE (0xB82FC8C0)

#define SWIC3_DMA_RX_DES_BASE (0xB82FC900)
#define SWIC3_DMA_RX_DAT_BASE (0xB82FC940)
#define SWIC3_DMA_TX_DES_BASE (0xB82FC980)
#define SWIC3_DMA_TX_DAT_BASE (0xB82FC9C0)

// MFBSP Base Address
#define MFBSP_BASE (0xB8303800)
#define MFBSP0_BASE (0xB8303800)
#define MFBSP1_BASE (0xB8304000)

// DMA MFBSP Base Address
#define MFBSP0_DMA_BASE (0xB8304800)
#define MFBSP1_DMA_BASE (0xB8304880)

///////////////////////DMA MFBSP//////////////////////
#define _MFBSPdmaTXch0 ((mfbsp_dma_ch volatile *)0xB8304800)
#define _MFBSPdmaRXch0 ((mfbsp_dma_ch volatile *)0xB8304840)
#define _MFBSPdmaTXch1 ((mfbsp_dma_ch volatile *)0xB8304880)
#define _MFBSPdmaRXch1 ((mfbsp_dma_ch volatile *)0xB83048c0)

///////////////////////DMA MFBSP//////////////////////

///////////////////////MFBSP//////////////////////
// MFBSP Base Address

#define _MFBSPport0 ((mfbsp_port volatile *)0xB8303800)
#define _MFBSPport1 ((mfbsp_port volatile *)0xB8304000)

// MFBSP0 Registers
#define MFBSP0_TX *((volatile int *)0xb8303800)
#define MFBSP0_RX *((volatile int *)0xb8303800)
#define MFBSP0_CSR *((volatile int *)0xb8303804)
#define MFBSP0_DIR *((volatile int *)0xb8303808)
#define MFBSP0_GPIO *((volatile int *)0xb830380C)
#define MFBSP0_TCTR *((volatile int *)0xb8303810)
#define MFBSP0_RCTR *((volatile int *)0xb8303814)
#define MFBSP0_TSR *((volatile int *)0xb8303818)
#define MFBSP0_RSR *((volatile int *)0xb830381C)

// MFBSP1 Registers
#define MFBSP1_TX *((volatile int *)0xb8304000)
#define MFBSP1_RX *((volatile int *)0xb8304000)
#define MFBSP1_CSR *((volatile int *)0xb8304004)
#define MFBSP1_DIR *((volatile int *)0xb8304008)
#define MFBSP1_GPIO *((volatile int *)0xb830400C)
#define MFBSP1_TCTR *((volatile int *)0xb8304010)
#define MFBSP1_RCTR *((volatile int *)0xb8304014)
#define MFBSP1_TSR *((volatile int *)0xb8304018)
#define MFBSP1_RSR *((volatile int *)0xb830401C)

///////////////////////MFBSP//////////////////////

// CAN Base Address
#define CAN0_BASE (0xB8305000)
#define CAN1_BASE (0xB8306000)
#define CAN_STANDART_FILTER_OFFSET (0x200)
#define CAN_EXTENDED_FILTER_OFFSET (0x400)
#define CAN_RX_FIFO_OFFSET (0x600)
#define CAN_TX_BUFF_OFFSET (0xA00)
#define CAN_TX_FIFO_OFFSET (0xC00)
#define CAN_EVENT_OFFSET (0xD00)

// Dummy
#define MFBSP_DMA_RX_CH_BASE 0
#define MFBSP_DMA_TX_CH_BASE 0
#define MFBSP_DMA_CH_OFFSET 0

#define MC_RBR(id) *((volatile int *)(0xb82F3000) + (id) * 0x400)
#define MC_THR(id) *((volatile int *)(0xb82F3000) + (id) * 0x400)
#define MC_IER(id) *((volatile int *)(0xb82F3004) + (id) * 0x400)
#define MC_IIR(id) *((volatile int *)(0xb82F3008) + (id) * 0x400)
#define MC_FCR(id) *((volatile int *)(0xb82F3008) + (id) * 0x400)
#define MC_LCR(id) *((volatile int *)(0xb82F300C) + (id) * 0x400)
#define MC_MCR(id) *((volatile int *)(0xb82F3010) + (id) * 0x400)
#define MC_LSR(id) *((volatile int *)(0xb82F3014) + (id) * 0x400)
#define MC_MSR(id) *((volatile int *)(0xb82F3018) + (id) * 0x400)
#define MC_SPR(id) *((volatile int *)(0xb82F301C) + (id) * 0x400)
#define MC_DLL(id) *((volatile int *)(0xb82F3000) + (id) * 0x400)
#define MC_DLM(id) *((volatile int *)(0xb82F3004) + (id) * 0x400)
#define MC_SCLR(id) *((volatile int *)(0xb82F3014) + (id) * 0x400)

// UART0 Registers
#define UART_RBR *((volatile int *)0xb82F3000)
#define UART_THR *((volatile int *)0xb82F3000)
#define UART_IER *((volatile int *)0xb82F3004)
#define UART_IIR *((volatile int *)0xb82F3008)
#define UART_FCR *((volatile int *)0xb82F3008)
#define UART_LCR *((volatile int *)0xb82F300C)
#define UART_MCR *((volatile int *)0xb82F3010)
#define UART_LSR *((volatile int *)0xb82F3014)
#define UART_MSR *((volatile int *)0xb82F3018)
#define UART_SPR *((volatile int *)0xb82F301C)
#define UART_DLL *((volatile int *)0xb82F3000)
#define UART_DLM *((volatile int *)0xb82F3004)
#define UART_SCLR *((volatile int *)0xb82F3014)

// IT0 Registers
#define ITCSR0 *((volatile int *)0xb82F5000)
#define ITPERIOD0 *((volatile int *)0xb82F5004)
#define ITCOUNT0 *((volatile int *)0xb82F5008)
#define ITSCALE0 *((volatile int *)0xb82F500C)

// WDT Registers
#define WDTCSR *((volatile int *)0xb82F5010)
#define WDTPERIOD *((volatile int *)0xb82F5014)
#define WDTCOUNT *((volatile int *)0xb82F5018)
#define WDTSCALE *((volatile int *)0xb82F501C)

// IT1 Registers
#define ITCSR1 *((volatile int *)0xb82F5020)
#define ITPERIOD1 *((volatile int *)0xb82F5024)
#define ITCOUNT1 *((volatile int *)0xb82F5028)
#define ITSCALE1 *((volatile int *)0xb82F502C)

// IT2 Registers
#define ITCSR2 *((volatile int *)0xb82F5040)
#define ITPERIOD2 *((volatile int *)0xb82F5044)
#define ITCOUNT2 *((volatile int *)0xb82F5048)
#define ITSCALE2 *((volatile int *)0xb82F504C)

// IT3 Registers
#define ITCSR3 *((volatile int *)0xb82F5050)
#define ITPERIOD3 *((volatile int *)0xb82F5054)
#define ITCOUNT3 *((volatile int *)0xb82F5058)
#define ITSCALE3 *((volatile int *)0xb82F505C)

// IT4 Registers
#define ITCSR4 *((volatile int *)0xb82F5060)
#define ITPERIOD4 *((volatile int *)0xb82F5064)
#define ITCOUNT4 *((volatile int *)0xb82F5068)
#define ITSCALE4 *((volatile int *)0xb82F506C)

// IT5 Registers
#define ITCSR5 *((volatile int *)0xb82F5070)
#define ITPERIOD5 *((volatile int *)0xb82F5074)
#define ITCOUNT5 *((volatile int *)0xb82F5078)
#define ITSCALE5 *((volatile int *)0xb82F507C)

// IT6 Registers
#define ITCSR6 *((volatile int *)0xb82F5080)
#define ITPERIOD6 *((volatile int *)0xb82F5084)
#define ITCOUNT6 *((volatile int *)0xb82F5088)
#define ITSCALE6 *((volatile int *)0xb82F508C)

// IT7 Registers
#define ITCSR7 *((volatile int *)0xb82F5090)
#define ITPERIOD7 *((volatile int *)0xb82F5094)
#define ITCOUNT7 *((volatile int *)0xb82F5098)
#define ITSCALE7 *((volatile int *)0xb82F509C)

// IT8 Registers
#define ITCSR8 *((volatile int *)0xb82F50A0)
#define ITPERIOD8 *((volatile int *)0xb82F50A4)
#define ITCOUNT8 *((volatile int *)0xb82F50A8)
#define ITSCALE8 *((volatile int *)0xb82F50AC)

// IT9 Registers
#define ITCSR9 *((volatile int *)0xb82F50B0)
#define ITPERIOD9 *((volatile int *)0xb82F50B4)
#define ITCOUNT9 *((volatile int *)0xb82F50B8)
#define ITSCALE9 *((volatile int *)0xb82F50BC)

// IT10 Registers
#define ITCSR10 *((volatile int *)0xb82F50C0)
#define ITPERIOD10 *((volatile int *)0xb82F50C4)
#define ITCOUNT10 *((volatile int *)0xb82F50C8)
#define ITSCALE10 *((volatile int *)0xb82F50CC)

// IT11 Registers
#define ITCSR11 *((volatile int *)0xb82F50D0)
#define ITPERIOD11 *((volatile int *)0xb82F50D4)
#define ITCOUNT11 *((volatile int *)0xb82F50D8)
#define ITSCALE11 *((volatile int *)0xb82F50DC)

// IT12 Registers
#define ITCSR12 *((volatile int *)0xb82F50E0)
#define ITPERIOD12 *((volatile int *)0xb82F50E4)
#define ITCOUNT12 *((volatile int *)0xb82F50E8)
#define ITSCALE12 *((volatile int *)0xb82F50EC)

// IT13 Registers
#define ITCSR13 *((volatile int *)0xb82F50F0)
#define ITPERIOD13 *((volatile int *)0xb82F50F4)
#define ITCOUNT13 *((volatile int *)0xb82F50F8)
#define ITSCALE13 *((volatile int *)0xb82F50FC)

// IT14 Registers
#define ITCSR14 *((volatile int *)0xb82F5100)
#define ITPERIOD14 *((volatile int *)0xb82F5104)
#define ITCOUNT14 *((volatile int *)0xb82F5108)
#define ITSCALE14 *((volatile int *)0xb82F510C)

// IT15 Registers
#define ITCSR15 *((volatile int *)0xb82F5110)
#define ITPERIOD15 *((volatile int *)0xb82F5114)
#define ITCOUNT15 *((volatile int *)0xb82F5118)
#define ITSCALE15 *((volatile int *)0xb82F511C)

// WDT Registers
#define WTCSR *((volatile int *)0xb82F5010)
#define WTPERIOD *((volatile int *)0xb82F5014)
#define WTCOUNT *((volatile int *)0xb82F5018)
#define WTSCALE *((volatile int *)0xb82F501C)

// MPORT Registers
#define CSCON0 *((volatile int *)0xb82F1000)
#define CSCON1 *((volatile int *)0xb82F1004)
#define CSCON2 *((volatile int *)0xb82F1008)
#define CSCON3 *((volatile int *)0xb82F100C)
#define CSCON4 *((volatile int *)0xb82F1010)
#define SDRCON *((volatile int *)0xb82F1014)
#define SDRTMR *((volatile int *)0xb82F1018)
#define SDRCSR *((volatile int *)0xb82F101C)

// System Registers
#define CR_PLL *((volatile int *)0xb82F4000)
#define CLK_EN *((volatile int *)0xb82F4004)
#define CLK_EN_CORE (1 << 0)
#define CLKEN_DSP0 (1 << 4)
#define CLKEN_DSP1 (1 << 5)
#define CLK_EN_CAN0 (1 << 6)
#define CLK_EN_CAN1 (1 << 7)
#define CLK_EN_DMA0 (1 << 12)
#define CLK_EN_DMA1 (1 << 13)
#define CLK_EN_ARINC (1 << 16)
#define CLK_EN_SPI (1 << 17)
#define CLK_EN_SWIC0 (1 << 26)
#define CLK_EN_SWIC1 (1 << 27)
#define CLK_EN_SWIC2 (1 << 28)
#define CLK_EN_SWIC3 (1 << 29)

// Hamming
#define HM_CRAM_BASE *((volatile int *)0xb82F4400)
#define HM_ICACHE_BASE *((volatile int *)0xb82F4800)
#define HM_DCACHE_BASE *((volatile int *)0xb82F4C00)

// SPFMIC
#define SPFMIC_BASE(i) (0xb82F7000 + (i) * 0x1000)

#define SPFMIC_ID_VER(i) *(volatile int *)(SPFMIC_BASE(i) + 0x0)
#define SPFMIC_MODE_R(i) *(volatile int *)(SPFMIC_BASE(i) + 0x4)
#define SPFMIC_STATE_R(i) *(volatile int *)(SPFMIC_BASE(i) + 0x8)
#define SPFMIC_RISC_IRQ_MASK(i) *(volatile int *)(SPFMIC_BASE(i) + 0xC)
#define SPFMIC_CCODE_OUT(i) *(volatile int *)(SPFMIC_BASE(i) + 0x10)
#define SPFMIC_CUR_TIME(i) *(volatile int *)(SPFMIC_BASE(i) + 0x14)
#define SPFMIC_ISR_L(i) *(volatile int *)(SPFMIC_BASE(i) + 0x18)
#define SPFMIC_ISR_H(i) *(volatile int *)(SPFMIC_BASE(i) + 0x1C)
#define SPFMIC_INTR_IRQ_MASK_L(i) *(volatile int *)(SPFMIC_BASE(i) + 0x20)
#define SPFMIC_INTR_IRQ_MASK_H(i) *(volatile int *)(SPFMIC_BASE(i) + 0x24)
#define SPFMIC_INTA_IRQ_MASK_L(i) *(volatile int *)(SPFMIC_BASE(i) + 0x28)
#define SPFMIC_INTA_IRQ_MASK_H(i) *(volatile int *)(SPFMIC_BASE(i) + 0x2C)
#define SPFMIC_CCODES_MASK(i) *(volatile int *)(SPFMIC_BASE(i) + 0x30)
#define SPFMIC_DIST_INTS_TOUTS1(i) *(volatile int *)(SPFMIC_BASE(i) + 0x34)
#define SPFMIC_DIST_INTS_TOUTS2(i) *(volatile int *)(SPFMIC_BASE(i) + 0x38)
#define SPFMIC_ACK_NON_ACK_REGIME(i) *(volatile int *)(SPFMIC_BASE(i) + 0x3C)
#define SPFMIC_CCODES_SPEC_REGIME(i) *(volatile int *)(SPFMIC_BASE(i) + 0x40)
#define SPFMIC_SPEC_ISR_REGIME(i) *(volatile int *)(SPFMIC_BASE(i) + 0x44)
#define SPFMIC_INTER_HANDLER_TERM_FUNCT(i) \
  *(volatile int *)(SPFMIC_BASE(i) + 0x48)
#define SPFMIC_ISR_SOURCE_TERM_FUNCT(i) *(volatile int *)(SPFMIC_BASE(i) + 0x4C)
#define SPFMIC_ISR_TOUTS_FLS_L(i) *(volatile int *)(SPFMIC_BASE(i) + 0x50)
#define SPFMIC_ISR_TOUTS_FLS_H(i) *(volatile int *)(SPFMIC_BASE(i) + 0x54)
#define SPFMIC_ISR_1101(i) *(volatile int *)(SPFMIC_BASE(i) + 0x58)
#define SPFMIC_EXTERNAL_RESET_PARAMETERS(i) \
  *(volatile int *)(SPFMIC_BASE(i) + 0x5C)
#define SPFMIC_PORT_CCODES_MODE(i) *(volatile int *)(SPFMIC_BASE(i) + 0x60)
#define SPFMIC_CCODES_INTERVAL(i) *(volatile int *)(SPFMIC_BASE(i) + 0x64)
#define SPFMIC_BROADCAST_MODE(i) *(volatile int *)(SPFMIC_BASE(i) + 0x68)
#define SPFMIC_BROADCAST_NUMS(i) *(volatile int *)(SPFMIC_BASE(i) + 0x6C)
#define SPFMIC_BROADCAST_DATA_OUT_L(i) *(volatile int *)(SPFMIC_BASE(i) + 0x70)
#define SPFMIC_BROADCAST_DATA_OUT_H(i) *(volatile int *)(SPFMIC_BASE(i) + 0x74)
#define SPFMIC_BROADCAST_DATA_OUT_PARAMETRS(i) \
  *(volatile int *)(SPFMIC_BASE(i) + 0x78)
#define SPFMIC_BROADCAST_DATA_IN_L(i) *(volatile int *)(SPFMIC_BASE(i) + 0x7C)
#define SPFMIC_BROADCAST_DATA_IN_H(i) *(volatile int *)(SPFMIC_BASE(i) + 0x80)
#define SPFMIC_BROADCAST_DATA_IN_PARAMETRS(i) \
  *(volatile int *)(SPFMIC_BASE(i) + 0x84)
#define SPFMIC_BROADCAST_DATA_IN_STATUS1(i) \
  *(volatile int *)(SPFMIC_BASE(i) + 0x88)
#define SPFMIC_BROADCAST_DATA_IN_STATUS_ALL1(i) \
  *(volatile int *)(SPFMIC_BASE(i) + 0x8C)
#define SPFMIC_TIME_SLOTS_PARAMETERS(i) *(volatile int *)(SPFMIC_BASE(i) + 0x90)
#define SPFMIC_TIME_SLOTS_SETTINGS(i) *(volatile int *)(SPFMIC_BASE(i) + 0x94)
#define SPFMIC_PMA_STATUS(i) *(volatile int *)(SPFMIC_BASE(i) + 0x98)
#define SPFMIC_PMA_MODE(i) *(volatile int *)(SPFMIC_BASE(i) + 0x9C)
#define SPFMIC_GIGA_SPW_STATUS(i) *(volatile int *)(SPFMIC_BASE(i) + 0xA0)
#define SPFMIC_GIGA_SPW_MODE(i) *(volatile int *)(SPFMIC_BASE(i) + 0xA4)
#define SPFMIC_GIGA_SPW_TRANSMISSION_PARAMETERS(i) \
  *(volatile int *)(SPFMIC_BASE(i) + 0xA8)
#define SPFMIC_GIGA_SPW_CREDIT_PARAMETERS(i) \
  *(volatile int *)(SPFMIC_BASE(i) + 0xAC)
#define SPFMIC_GIGA_SPW_RX_SPEED(i) *(volatile int *)(SPFMIC_BASE(i) + 0xB0)
#define SPFMIC_SpF_PORT_MODE_VC_PARAMS(i) \
  *(volatile int *)(SPFMIC_BASE(i) + 0xB4)
#define SPFMIC_SpF_PORT_MODE_VC_TSLOTS_L(i) \
  *(volatile int *)(SPFMIC_BASE(i) + 0xC4)
#define SPFMIC_SpF_PORT_MODE_VC_TSLOTS_H(i) \
  *(volatile int *)(SPFMIC_BASE(i) + 0xD4)
#define SPFMIC_SpF_PORT_MODE_VC_FR_LL(i) \
  *(volatile int *)(SPFMIC_BASE(i) + 0xE4)
#define SPFMIC_SpF_PORT_MODE_LANE_CONSTANTS(i) \
  *(volatile int *)(SPFMIC_BASE(i) + 0xE8)
#define SPFMIC_SpF_PORT_STATUS_VC1(i) *(volatile int *)(SPFMIC_BASE(i) + 0xEC)
#define SPFMIC_SpF_PORT_STATUS_VC2(i) *(volatile int *)(SPFMIC_BASE(i) + 0xF0)
#define SPFMIC_SpF_PORT_CUR_CREDIT_VALUE(i) \
  *(volatile int *)(SPFMIC_BASE(i) + 0xF4)
#define SPFMIC_SpF_PORT_STATUS_LL_EL(i) *(volatile int *)(SPFMIC_BASE(i) + 0xF8)
#define SPFMIC_CONF_PORT_MODE_VC_PARAMS(i) \
  *(volatile int *)(SPFMIC_BASE(i) + 0xFC)
#define SPFMIC_CONF_PORT_CUR_CREDIT_VALUE(i) \
  *(volatile int *)(SPFMIC_BASE(i) + 0x10C)

#define SPFMIC0_RX_DES *(volatile int *)(0xb82F7800)
#define SPFMIC0_RX_DAT *(volatile int *)(0xb82F7840)
#define SPFMIC0_TX_DES *(volatile int *)(0xb82F7880)
#define SPFMIC0_TX_DAT *(volatile int *)(0xb82F78C0)

#define SPFMIC1_RX_DES *(volatile int *)(0xb82F8800)
#define SPFMIC1_RX_DAT *(volatile int *)(0xb82F8840)
#define SPFMIC1_TX_DES *(volatile int *)(0xb82F8880)
#define SPFMIC1_TX_DAT *(volatile int *)(0xb82F88C0)

// EMAC
#define EMAC0 *((volatile int *)(0xb82FD000))
#define EMAC1 *((volatile int *)(0xb82FE000))

#define EMAC0_RX_DES *((volatile int *)(0xb82FD800))
#define EMAC0_RX_DAT *((volatile int *)(0xb82FD840))
#define EMAC0_TX_DES *((volatile int *)(0xb82FD880))
#define EMAC0_TX_DAT *((volatile int *)(0xb82FD8C0))

#define EMAC1_RX_DES *((volatile int *)(0xb82FE800))
#define EMAC1_RX_DAT *((volatile int *)(0xb82FE840))
#define EMAC1_TX_DES *((volatile int *)(0xb82FE880))
#define EMAC1_TX_DAT *((volatile int *)(0xb82FE8C0))

// 1553BIC
#define _1553BIC0 *((volatile int *)(0xb8301800))
#define _1553BIC1 *((volatile int *)(0xb8302800))

#define SYS_CSR(i) *((volatile int *)(0xb82F4008 + 0x40 * i))
#define MASKR0(i) *((volatile int *)(0xb82F4010 + 0x40 * i))
#define QSTR0(i) *((volatile int *)(0xb82F4014 + 0x40 * i))
#define MASKR1(i) *((volatile int *)(0xb82F4018 + 0x40 * i))
#define QSTR1(i) *((volatile int *)(0xb82F401C + 0x40 * i))
#define MASKR2(i) *((volatile int *)(0xb82F4020 + 0x40 * i))
#define QSTR2(i) *((volatile int *)(0xb82F4024 + 0x40 * i))
#define MASKR3(i) *((volatile int *)(0xb82F4028 + 0x40 * i))
#define QSTR3(i) *((volatile int *)(0xb82F402c + 0x40 * i))
#define MASKR4(i) *((volatile int *)(0xb82F4034 + 0x40 * i))
#define QSTR4(i) *((volatile int *)(0xb82F4038 + 0x40 * i))
#define IRQM *((volatile int *)0xb82F4030)
#define RST_PROG *((volatile int *)0xb82F403C)
#define AXI_RND *((volatile int *)0xb82F404C)

// NOR-Flash Base Address
#define NOR_BASE 0xBC000000

// DSP Registers
// DSP Base Registers
#define MASKR_DSP *((volatile int *)0xb8481000)
#define QSTR_DSP *((volatile int *)0xb8481004)
#define CSR_DSP *((volatile int *)0xb8481008)
#define TOTAL_RUN_CNT *((volatile int *)0xb848100C)
#define TOTAL_CLK_CNT *((volatile int *)0xb8481010)
#define QSTR_HEM_DSP *((volatile int *)0xb8481014)

#define X(i) *((volatile long long *)0xb87FFF00 + i)
#define X_L(i) *((volatile int *)0xb87FFF00 + i * 2)
#define X_H(i) *((volatile int *)0xb87FFF04 + i * 2)

#define BASE(i) (0xB8480000 + (i) * 0x400000)
// DSP PCU (control) registers
#define DCSR(i) *((volatile int *)(BASE(i) + 0x0100))
#define SR(i) *((volatile int *)(BASE(i) + 0x0104))
#define IDR(i) *((volatile int *)(BASE(i) + 0x0108))
#define EFR(i) *((volatile int *)(BASE(i) + 0x010C))
#define DSTART(i) *((volatile int *)(BASE(i) + 0x010C))
#define IRQR(i) *((volatile int *)(BASE(i) + 0x0110))
#define IMASKR(i) *((volatile int *)(BASE(i) + 0x0114))
#define TMR(i) *((volatile int *)(BASE(i) + 0x0118))
#define ARBR(i) *((volatile int *)(BASE(i) + 0x011C))
#define PC(i) *((volatile int *)(BASE(i) + 0x0120))
#define SS(i) *((volatile int *)(BASE(i) + 0x0124))
#define LA(i) *((volatile int *)(BASE(i) + 0x0128))
#define CSL(i) *((volatile int *)(BASE(i) + 0x012C))
#define LC(i) *((volatile int *)(BASE(i) + 0x0130))
#define CSH(i) *((volatile int *)(BASE(i) + 0x0134))
#define SP(i) *((volatile int *)(BASE(i) + 0x0138))
#define SAR(i) *((volatile int *)(BASE(i) + 0x013C))
#define CNTR(i) *((volatile int *)(BASE(i) + 0x0140))
#define SAR1(i) *((volatile int *)(BASE(i) + 0x0144))
#define SAR2(i) *((volatile int *)(BASE(i) + 0x0148))
#define SAR3(i) *((volatile int *)(BASE(i) + 0x014C))
#define SAR4(i) *((volatile int *)(BASE(i) + 0x0150))
#define SAR5(i) *((volatile int *)(BASE(i) + 0x0154))
#define SAR6(i) *((volatile int *)(BASE(i) + 0x0158))
#define SAR7(i) *((volatile int *)(BASE(i) + 0x015C))

#define CCR(i) *((volatile int *)(BASE(i) + 0x0160))
#define PDNR(i) *((volatile int *)(BASE(i) + 0x0164))
#define SFR(i) *((volatile int *)(BASE(i) + 0x0168))
// DSP AGU (address) registers
#define A0(i) *((volatile int *)(BASE(i) + 0x0080))
#define A1(i) *((volatile int *)(BASE(i) + 0x0084))
#define A2(i) *((volatile int *)(BASE(i) + 0x0088))
#define A3(i) *((volatile int *)(BASE(i) + 0x008C))
#define A4(i) *((volatile int *)(BASE(i) + 0x0090))
#define A5(i) *((volatile int *)(BASE(i) + 0x0094))
#define A6(i) *((volatile int *)(BASE(i) + 0x0098))
#define A7(i) *((volatile int *)(BASE(i) + 0x009C))
#define I0(i) *((volatile int *)(BASE(i) + 0x00A0))
#define I1(i) *((volatile int *)(BASE(i) + 0x00A4))
#define I2(i) *((volatile int *)(BASE(i) + 0x00A8))
#define I3(i) *((volatile int *)(BASE(i) + 0x00AC))
#define I4(i) *((volatile int *)(BASE(i) + 0x00B0))
#define I5(i) *((volatile int *)(BASE(i) + 0x00B4))
#define I6(i) *((volatile int *)(BASE(i) + 0x00B8))
#define I7(i) *((volatile int *)(BASE(i) + 0x00BC))
#define M0(i) *((volatile int *)(BASE(i) + 0x00C0))
#define M1(i) *((volatile int *)(BASE(i) + 0x00C4))
#define M2(i) *((volatile int *)(BASE(i) + 0x00C8))
#define M3(i) *((volatile int *)(BASE(i) + 0x00CC))
#define M4(i) *((volatile int *)(BASE(i) + 0x00D0))
#define M5(i) *((volatile int *)(BASE(i) + 0x00D4))
#define M6(i) *((volatile int *)(BASE(i) + 0x00D8))
#define M7(i) *((volatile int *)(BASE(i) + 0x00DC))
#define AT(i) *((volatile int *)(BASE(i) + 0x00E0))
#define IT(i) *((volatile int *)(BASE(i) + 0x00E4))
#define MT(i) *((volatile int *)(BASE(i) + 0x00E8))
#define DT(i) *((volatile int *)(BASE(i) + 0x00EC))
#define IVAR(i) *((volatile int *)(BASE(i) + 0x00FC))
// DSP RF (data) registers
#define R0_L(i) *((volatile int *)(BASE(i) + 0x0000))
#define R2_L(i) *((volatile int *)(BASE(i) + 0x0004))
#define R4_L(i) *((volatile int *)(BASE(i) + 0x0008))
#define R6_L(i) *((volatile int *)(BASE(i) + 0x000C))
#define R8_L(i) *((volatile int *)(BASE(i) + 0x0010))
#define R10_L(i) *((volatile int *)(BASE(i) + 0x0014))
#define R12_L(i) *((volatile int *)(BASE(i) + 0x0018))
#define R14_L(i) *((volatile int *)(BASE(i) + 0x001C))
#define R16_L(i) *((volatile int *)(BASE(i) + 0x0020))
#define R18_L(i) *((volatile int *)(BASE(i) + 0x0024))
#define R20_L(i) *((volatile int *)(BASE(i) + 0x0028))
#define R22_L(i) *((volatile int *)(BASE(i) + 0x002C))
#define R24_L(i) *((volatile int *)(BASE(i) + 0x0030))
#define R26_L(i) *((volatile int *)(BASE(i) + 0x0034))
#define R28_L(i) *((volatile int *)(BASE(i) + 0x0038))
#define R30_L(i) *((volatile int *)(BASE(i) + 0x003C))
#define R1_L(i) *((volatile int *)(BASE(i) + 0x0040))
#define R3_L(i) *((volatile int *)(BASE(i) + 0x0044))
#define R5_L(i) *((volatile int *)(BASE(i) + 0x0048))
#define R7_L(i) *((volatile int *)(BASE(i) + 0x004C))
#define R9_L(i) *((volatile int *)(BASE(i) + 0x0050))
#define R11_L(i) *((volatile int *)(BASE(i) + 0x0054))
#define R13_L(i) *((volatile int *)(BASE(i) + 0x0058))
#define R15_L(i) *((volatile int *)(BASE(i) + 0x005C))
#define R17_L(i) *((volatile int *)(BASE(i) + 0x0060))
#define R19_L(i) *((volatile int *)(BASE(i) + 0x0064))
#define R21_L(i) *((volatile int *)(BASE(i) + 0x0068))
#define R23_L(i) *((volatile int *)(BASE(i) + 0x006C))
#define R25_L(i) *((volatile int *)(BASE(i) + 0x0070))
#define R27_L(i) *((volatile int *)(BASE(i) + 0x0074))
#define R29_L(i) *((volatile int *)(BASE(i) + 0x0078))
#define R31_L(i) *((volatile int *)(BASE(i) + 0x007C))
#define R1D_L(i) *((volatile int *)(BASE(i) + 0x0180))
#define R1D_H(i) *((volatile int *)(BASE(i) + 0x0184))
#define R3D_L(i) *((volatile int *)(BASE(i) + 0x0188))
#define R3D_H(i) *((volatile int *)(BASE(i) + 0x018C))
#define R5D_L(i) *((volatile int *)(BASE(i) + 0x0190))
#define R5D_H(i) *((volatile int *)(BASE(i) + 0x0194))
#define R7D_L(i) *((volatile int *)(BASE(i) + 0x0198))
#define R7D_H(i) *((volatile int *)(BASE(i) + 0x019C))
#define R9D_L(i) *((volatile int *)(BASE(i) + 0x01A0))
#define R9D_H(i) *((volatile int *)(BASE(i) + 0x01A4))
#define R11D_L(i) *((volatile int *)(BASE(i) + 0x01A8))
#define R11D_H(i) *((volatile int *)(BASE(i) + 0x01AC))
#define R13D_L(i) *((volatile int *)(BASE(i) + 0x01B0))
#define R13D_H(i) *((volatile int *)(BASE(i) + 0x01B4))
#define R15D_L(i) *((volatile int *)(BASE(i) + 0x01B8))
#define R15D_H(i) *((volatile int *)(BASE(i) + 0x01BC))
#define R17D_L(i) *((volatile int *)(BASE(i) + 0x01C0))
#define R17D_H(i) *((volatile int *)(BASE(i) + 0x01C4))
#define R19D_L(i) *((volatile int *)(BASE(i) + 0x01C8))
#define R19D_H(i) *((volatile int *)(BASE(i) + 0x01CC))
#define R21D_L(i) *((volatile int *)(BASE(i) + 0x01D0))
#define R21D_H(i) *((volatile int *)(BASE(i) + 0x01D4))
#define R23D_L(i) *((volatile int *)(BASE(i) + 0x01D8))
#define R23D_H(i) *((volatile int *)(BASE(i) + 0x01DC))
#define R25D_L(i) *((volatile int *)(BASE(i) + 0x01E0))
#define R25D_H(i) *((volatile int *)(BASE(i) + 0x01E4))
#define R27D_L(i) *((volatile int *)(BASE(i) + 0x01E8))
#define R27D_H(i) *((volatile int *)(BASE(i) + 0x01EC))
#define R29D_L(i) *((volatile int *)(BASE(i) + 0x01F0))
#define R29D_H(i) *((volatile int *)(BASE(i) + 0x01F4))
#define R31D_L(i) *((volatile int *)(BASE(i) + 0x01F8))
#define R31D_H(i) *((volatile int *)(BASE(i) + 0x01FC))

// DSP accumulator registers
#define AC0(i) *((volatile int *)(BASE(i) + 0x0200))
#define AC1(i) *((volatile int *)(BASE(i) + 0x0204))
#define AC2(i) *((volatile int *)(BASE(i) + 0x0208))
#define AC3(i) *((volatile int *)(BASE(i) + 0x020C))
#define AC4(i) *((volatile int *)(BASE(i) + 0x0210))
#define AC5(i) *((volatile int *)(BASE(i) + 0x0214))
#define AC6(i) *((volatile int *)(BASE(i) + 0x0218))
#define AC7(i) *((volatile int *)(BASE(i) + 0x021C))
#define AC8(i) *((volatile int *)(BASE(i) + 0x0220))
#define AC9(i) *((volatile int *)(BASE(i) + 0x0224))
#define AC10(i) *((volatile int *)(BASE(i) + 0x0228))
#define AC11(i) *((volatile int *)(BASE(i) + 0x022C))
#define AC12(i) *((volatile int *)(BASE(i) + 0x0230))
#define AC13(i) *((volatile int *)(BASE(i) + 0x0234))
#define AC14(i) *((volatile int *)(BASE(i) + 0x0238))
#define AC15(i) *((volatile int *)(BASE(i) + 0x023C))
// DSP debug registers
#define dbDCSR(i) *((volatile int *)(BASE(i) + 0x0500))
#define Cnt_RUN(i) *((volatile int *)(BASE(i) + 0x0518))
#define dbPCa(i) *((volatile int *)(BASE(i) + 0x0524))
#define dbPCf(i) *((volatile int *)(BASE(i) + 0x0528))
#define dbPCd(i) *((volatile int *)(BASE(i) + 0x052C))
#define dbPCe(i) *((volatile int *)(BASE(i) + 0x0520))
#define dbPCe1(i) *((volatile int *)(BASE(i) + 0x0530))
#define dbPCe2(i) *((volatile int *)(BASE(i) + 0x0534))
#define dbPCe3(i) *((volatile int *)(BASE(i) + 0x0538))
#define dbSAR(i) *((volatile int *)(BASE(i) + 0x053C))
#define dbCNTR(i) *((volatile int *)(BASE(i) + 0x0540))
#define dbSAR1(i) *((volatile int *)(BASE(i) + 0x0544))
#define dbSAR2(i) *((volatile int *)(BASE(i) + 0x0548))
#define dbSAR3(i) *((volatile int *)(BASE(i) + 0x054C))
#define dbSAR4(i) *((volatile int *)(BASE(i) + 0x0550))
#define dbSAR5(i) *((volatile int *)(BASE(i) + 0x0554))
#define dbSAR6(i) *((volatile int *)(BASE(i) + 0x0558))
#define dbSAR7(i) *((volatile int *)(BASE(i) + 0x055C))

#ifdef __cplusplus
}
#endif

#endif  //___MCL_MCT06_H___
