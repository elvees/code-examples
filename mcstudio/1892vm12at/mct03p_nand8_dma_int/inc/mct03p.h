// Copyright 2023-2025 RnD Center "ELVEES", JSC
// SPDX-License-Identifier: MIT

// *******************************************************************
//                 Risc-Dsp runtime library
//
// This file implements address of nvcom01/02 registers
//
// *******************************************************************
#ifndef ___MCL_MCT03_H___
#define ___MCL_MCT03_H___

#include "mct03p_system.h"

// DMA parameters defines
#define DMA_CONTROLLERS_NUM (2)
#define DMA_CHANNELS_IN_CONTROLLER (4)

// MCT-03P registers

// DMA MemCh Registers

// MemChi Registers(only for 0-3 channels)
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

// MemCh10 Registers
#define CSR_MemCh10 *((volatile int *)0xb82F0400)
#define CP_MemCh10 *((volatile int *)0xb82F0404)
#define IR0_MemCh10 *((volatile int *)0xb82F0408)
#define IR1_MemCh10 *((volatile int *)0xb82F040C)
#define OR_MemCh10 *((volatile int *)0xb82F0410)
#define Y_MemCh10 *((volatile int *)0xb82F0414)
#define RUN_MemCh10 *((volatile int *)0xb82F0418)
// MemCh11 Registers
#define CSR_MemCh11 *((volatile int *)0xb82F0480)
#define CP_MemCh11 *((volatile int *)0xb82F0484)
#define IR0_MemCh11 *((volatile int *)0xb82F0488)
#define IR1_MemCh11 *((volatile int *)0xb82F048C)
#define OR_MemCh11 *((volatile int *)0xb82F0490)
#define Y_MemCh11 *((volatile int *)0xb82F0494)
#define RUN_MemCh11 *((volatile int *)0xb82F0498)
// MemCh12 Registers
#define CSR_MemCh12 *((volatile int *)0xb82F0500)
#define CP_MemCh12 *((volatile int *)0xb82F0504)
#define IR0_MemCh12 *((volatile int *)0xb82F0508)
#define IR1_MemCh12 *((volatile int *)0xb82F050C)
#define OR_MemCh12 *((volatile int *)0xb82F0510)
#define Y_MemCh12 *((volatile int *)0xb82F0514)
#define RUN_MemCh12 *((volatile int *)0xb82F0518)
// MemCh13 Registers
#define CSR_MemCh13 *((volatile int *)0xb82F0580)
#define CP_MemCh13 *((volatile int *)0xb82F0584)
#define IR0_MemCh13 *((volatile int *)0xb82F0588)
#define IR1_MemCh13 *((volatile int *)0xb82F058C)
#define OR_MemCh13 *((volatile int *)0xb82F0590)
#define Y_MemCh13 *((volatile int *)0xb82F0594)
#define RUN_MemCh13 *((volatile int *)0xb82F0598)

// DMA MFBSP_RX_CH Registers

// MFBSP_RX_Ch0
#define MFBSP_CSR_RX_CH0 *((volatile int *)0xB82F8840)
#define MFBSP_CP_RX_CH0 *((volatile int *)0xB82F8844)
#define MFBSP_IR__RX_CH0 *((volatile int *)0xB82F8848)
#define MFBSP_RUN_RX_CH0 *((volatile int *)0xB82F884C)
// MFBSP_RX_Ch1
#define MFBSP_CSR_RX_CH1 *((volatile int *)0xB82F9840)
#define MFBSP_CP_RX_CH1 *((volatile int *)0xB82F9844)
#define MFBSP_IR_RX_CH1 *((volatile int *)0xB82F9848)
#define MFBSP_RUN_RX_CH1 *((volatile int *)0xB82F984C)

// DMA MFBSP_TX_Ch Registers

// MFBSP_TX_Ch0
#define MFBSP_CSR_TX_CH0 *((volatile int *)0xB82F8800)
#define MFBSP_CP_TX_CH0 *((volatile int *)0xB82F8804)
#define MFBSP_IR_TX_CH0 *((volatile int *)0xB82F8808)
#define MFBSP_RUN_TX_CH0 *((volatile int *)0xB82F880C)
// MFBSP_TX_Ch1
#define MFBSP_CSR_TX_CH1 *((volatile int *)0xB82F9800)
#define MFBSP_CP_TX_CH1 *((volatile int *)0xB82F9804)
#define MFBSP_IR_TX_CH1 *((volatile int *)0xB82F9808)
#define MFBSP_RUN_TX_CH1 *((volatile int *)0xB82F980C)

// MFBSP Base Address
#define MFBSP_BASE 0xB82F8000

#define _MFBSPport0 ((mfbsp_port volatile *)0xb82f8000)
#define _MFBSPport1 ((mfbsp_port volatile *)0xb82f9000)

#define _MFBSPdmaTXch0 ((mfbsp_dma_ch volatile *)0xb82f8800)
#define _MFBSPdmaRXch0 ((mfbsp_dma_ch volatile *)0xb82f8840)
#define _MFBSPdmaTXch1 ((mfbsp_dma_ch volatile *)0xb82f9800)
#define _MFBSPdmaRXch1 ((mfbsp_dma_ch volatile *)0xb82f9840)

// MFBSP0 Registers
#define MFBSP0_TX *((volatile int *)0xb82F8000)
#define MFBSP0_RX *((volatile int *)0xb82F8000)
#define MFBSP0_CSR *((volatile int *)0xb82F8004)
#define MFBSP0_DIR *((volatile int *)0xb82F8008)
#define MFBSP0_GPIO *((volatile int *)0xb82F800C)
#define MFBSP0_TCTR *((volatile int *)0xb82F8010)
#define MFBSP0_RCTR *((volatile int *)0xb82F8014)
#define MFBSP0_TSR *((volatile int *)0xb82F8018)
#define MFBSP0_RSR *((volatile int *)0xb82F801C)

// MFBSP1 Registers
#define MFBSP1_TX *((volatile int *)0xb82F9000)
#define MFBSP1_RX *((volatile int *)0xb82F9000)
#define MFBSP1_CSR *((volatile int *)0xb82F9004)
#define MFBSP1_DIR *((volatile int *)0xb82F9008)
#define MFBSP1_GPIO *((volatile int *)0xb82F900C)
#define MFBSP_TCTR *((volatile int *)0xb82F9010)
#define MFBSP1_RCTR *((volatile int *)0xb82F9014)
#define MFBSP1_TSR *((volatile int *)0xb82F9018)
#define MFBSP1_RSR *((volatile int *)0xb82F901C)

// DMA MFBSP_RX_CH base address
#define MFBSP_DMA_RX_CH_BASE 0xB82F8840

// DMA MFBSP_RX_CH base address
#define MFBSP_DMA_TX_CH_BASE 0xB82F8800

// DMA MFBSP offset between channels
#define MFBSP_DMA_CH_OFFSET 0x3FC

// DMA SWIC ch Registers

// SWIC DMA
#define SWIC_DMA(a) *(volatile unsigned *)(0xB82FC800 + (a))

// SWIC DMA RX
#define CSR_SWIC_RX_DES(i) SWIC_DMA(i * 0x1000)
#define CP_SWIC_RX_DES(i) SWIC_DMA(0x4 + (i * 0x1000))
#define IR_SWIC_RX_DES(i) SWIC_DMA(0x8 + (i * 0x1000))
#define RUN_SWIC_RX_DES(i) SWIC_DMA(0xC + (i * 0x1000))
#define CSR_SWIC_RX_DAT(i) SWIC_DMA(0x40 + (i * 0x1000))
#define CP_SWIC_RX_DAT(i) SWIC_DMA(0x44 + (i * 0x1000))
#define IR_SWIC_RX_DAT(i) SWIC_DMA(0x48 + (i * 0x1000))
#define RUN_SWIC_RX_DAT(i) SWIC_DMA(0x4C + (i * 0x1000))

// SWIC DMA TX
#define CSR_SWIC_TX_DES(i) SWIC_DMA(0x80 + (i * 0x1000))
#define CP_SWIC_TX_DES(i) SWIC_DMA(0x84 + (i * 0x1000))
#define IR_SWIC_TX_DES(i) SWIC_DMA(0x88 + (i * 0x1000))
#define RUN_SWIC_TX_DES(i) SWIC_DMA(0x8C + (i * 0x1000))
#define CSR_SWIC_TX_DAT(i) SWIC_DMA(0xC0 + (i * 0x1000))
#define CP_SWIC_TX_DAT(i) SWIC_DMA(0xC4 + (i * 0x1000))
#define IR_SWIC_TX_DAT(i) SWIC_DMA(0xC8 + (i * 0x1000))
#define RUN_SWIC_TX_DAT(i) SWIC_DMA(0xCC + (i * 0x1000))

// SWIC 0 DMA RX
#define CSR_SWIC_RX_DES0 *((volatile int *)0xB82FC800)
#define CP_SWIC_RX_DES0 *((volatile int *)0xB82FC804)
#define IR_SWIC_RX_DES0 *((volatile int *)0xB82FC808)
#define RUN_SWIC_RX_DES0 *((volatile int *)0xB82FC80C)
#define CSR_SWIC_RX_DAT0 *((volatile int *)0xB82FC840)
#define CP_SWIC_RX_DAT0 *((volatile int *)0xB82FC844)
#define IR_SWIC_RX_DAT0 *((volatile int *)0xB82FC848)
#define RUN_SWIC_RX_DAT0 *((volatile int *)0xB82FC84C)

// SWIC 0 DMA TX
#define CSR_SWIC_TX_DES0 *((volatile int *)0xB82FC880)
#define CP_SWIC_TX_DES0 *((volatile int *)0xB82FC884)
#define IR_SWIC_TX_DES0 *((volatile int *)0xB82FC888)
#define RUN_SWIC_TX_DES0 *((volatile int *)0xB82FC88C)
#define CSR_SWIC_TX_DAT0 *((volatile int *)0xB82FC8C0)
#define CP_SWIC_TX_DAT0 *((volatile int *)0xB82FC8C4)
#define IR_SWIC_TX_DAT0 *((volatile int *)0xB82FC8C8)
#define RUN_SWIC_TX_DAT0 *((volatile int *)0xB82FC8CC)

// SWIC 1 DMA RX
#define CSR_SWIC_RX_DES1 *((volatile int *)0xB82FD800)
#define CP_SWIC_RX_DES1 *((volatile int *)0xB82FD804)
#define IR_SWIC_RX_DES1 *((volatile int *)0xB82FD808)
#define RUN_SWIC_RX_DES1 *((volatile int *)0xB82FD80C)
#define CSR_SWIC_RX_DAT1 *((volatile int *)0xB82FD840)
#define CP_SWIC_RX_DAT1 *((volatile int *)0xB82FD844)
#define IR_SWIC_RX_DAT1 *((volatile int *)0xB82FD848)
#define RUN_SWIC_RX_DAT1 *((volatile int *)0xB82FD84C)

// SWIC 1 DMA TX
#define CSR_SWIC_TX_DES1 *((volatile int *)0xB82FD880)
#define CP_SWIC_TX_DES1 *((volatile int *)0xB82FD884)
#define IR_SWIC_TX_DES1 *((volatile int *)0xB82FD888)
#define RUN_SWIC_TX_DES1 *((volatile int *)0xB82FD88C)
#define CSR_SWIC_TX_DAT1 *((volatile int *)0xB82FD8C0)
#define CP_SWIC_TX_DAT1 *((volatile int *)0xB82FD8C4)
#define IR_SWIC_TX_DAT1 *((volatile int *)0xB82FD8C8)
#define RUN_SWIC_TX_DAT1 *((volatile int *)0xB82FD8CC)

// DMA GSWIC ch Registers

// GSWIC 0 DMA RX
#define CSR_GSW_RX_DES0 *((volatile int *)0xB82FE800)
#define CP_GSW_RX_DES0 *((volatile int *)0xB82FE804)
#define IR_GSW_RX_DES0 *((volatile int *)0xB82FE808)
#define RUN_GSW_RX_DES0 *((volatile int *)0xB82FE80C)
#define CSR_GSW_RX_DAT0 *((volatile int *)0xB82FE840)
#define CP_GSW_RX_DAT0 *((volatile int *)0xB82FE844)
#define IR_GSW_RX_DAT0 *((volatile int *)0xB82FE848)
#define RUN_GSW_RX_DAT0 *((volatile int *)0xB82FE84C)

// GWIC 0 DMA TX
#define CSR_GSW_TX_DES0 *((volatile int *)0xB82FE880)
#define CP_GSW_TX_DES0 *((volatile int *)0xB82FE884)
#define IR_GSW_TX_DES0 *((volatile int *)0xB82FE888)
#define RUN_GSW_TX_DES0 *((volatile int *)0xB82FE88C)
#define CSR_GSW_TX_DAT0 *((volatile int *)0xB82FE8C0)
#define CP_GSW_TX_DAT0 *((volatile int *)0xB82FE8C4)
#define IR_GSW_TX_DAT0 *((volatile int *)0xB82FE8C8)
#define RUN_GSW_TX_DAT0 *((volatile int *)0xB82FE8CC)

// GWIC 1 DMA RX
#define CSR_GSW_RX_DES1 *((volatile int *)0xB82FF800)
#define CP_GSW_RX_DES1 *((volatile int *)0xB82FF804)
#define IR_GSW_RX_DES1 *((volatile int *)0xB82FF808)
#define RUN_GSW_RX_DES1 *((volatile int *)0xB82FF80C)
#define CSR_GSW_RX_DAT1 *((volatile int *)0xB82FF840)
#define CP_GSW_RX_DAT1 *((volatile int *)0xB82FF844)
#define IR_GSW_RX_DAT1 *((volatile int *)0xB82FF848)
#define RUN_GSW_RX_DAT1 *((volatile int *)0xB82FF84C)

// GWIC 1 DMA TX
#define CSR_GSW_TX_DES1 *((volatile int *)0xB82FF880)
#define CP_GSW_TX_DES1 *((volatile int *)0xB82FF884)
#define IR_GSW_TX_DES1 *((volatile int *)0xB82FF888)
#define RUN_GSW_TX_DES1 *((volatile int *)0xB82FF88C)
#define CSR_GSW_TX_DAT1 *((volatile int *)0xB82FF8C0)
#define CP_GSW_TX_DAT1 *((volatile int *)0xB82FF8C4)
#define IR_GSW_TX_DAT1 *((volatile int *)0xB82FF8C8)
#define RUN_GSW_TX_DAT1 *((volatile int *)0xB82FF8CC)

// SWIC Registers

// SWIC Registers
#define SWIC0_BASE (0xB82FC000)
#define SWIC1_BASE (0xB82FD000)

#define SWIC0_DMA_RX_DES_BASE (0xB82FC800)
#define SWIC0_DMA_RX_DAT_BASE (0xB82FC840)
#define SWIC0_DMA_TX_DES_BASE (0xB82FC880)
#define SWIC0_DMA_TX_DAT_BASE (0xB82FC8C0)

#define SWIC1_DMA_RX_DES_BASE (0xB82FD800)
#define SWIC1_DMA_RX_DAT_BASE (0xB82FD840)
#define SWIC1_DMA_TX_DES_BASE (0xB82FD880)
#define SWIC1_DMA_TX_DAT_BASE (0xB82FD8C0)

#define SWIC_A(a) *(volatile unsigned *)(0xB82FC000 + (a))

#define HW_VER(i) SWIC_A(i * 0x1000)
#define STATUS(i) SWIC_A(0x4 + (i * 0x1000))
#define RX_CODE(i) SWIC_A(0x8 + (i * 0x1000))
#define MODE_CR(i) SWIC_A(0xC + (i * 0x1000))
#define TX_SPEED(i) SWIC_A(0x10 + (i * 0x1000))
#define TX_CODE(i) SWIC_A(0x14 + (i * 0x1000))
#define RX_SPEED(i) SWIC_A(0x18 + (i * 0x1000))
#define CNT_RX0_PACK(i) SWIC_A(0x1C + (i * 0x1000))
#define CNT_RX_PACK(i) SWIC_A(0x20 + (i * 0x1000))
#define ISR_L(i) SWIC_A(0x24 + (i * 0x1000))
#define ISR_H(i) SWIC_A(0x28 + (i * 0x1000))
#define TRUE_TIME(i) SWIC_A(0x2C + (i * 0x1000))
#define TOUT_CODE(i) SWIC_A(0x30 + (i * 0x1000))
#define ISR_TOUT_L(i) SWIC_A(0x34 + (i * 0x1000))
#define ISR_TOUT_H(i) SWIC_A(0x38 + (i * 0x1000))
#define LOG_ADDR(i) SWIC_A(0x3C + (i * 0x1000))

// SWIC0 Registers
#define HW_VER0 *((volatile int *)0xB82FC000)
#define STATUS0 *((volatile int *)0xB82FC004)
#define RX_CODE0 *((volatile int *)0xB82FC008)
#define MODE_CR0 *((volatile int *)0xB82FC00C)
#define TX_SPEED0 *((volatile int *)0xB82FC010)
#define TX_CODE0 *((volatile int *)0xB82FC014)
#define RX_SPEED0 *((volatile int *)0xB82FC018)
#define CNT_RX0_PACK0 *((volatile int *)0xB82FC01C)
#define CNT_RX_PACK0 *((volatile int *)0xB82FC020)
#define ISR_L0 *((volatile int *)0xB82FC024)
#define ISR_H0 *((volatile int *)0xB82FC028)
#define TRUE_TIME0 *((volatile int *)0xB82FC02C)
#define TOUT_CODE0 *((volatile int *)0xB82FC030)
#define ISR_TOUT_L0 *((volatile int *)0xB82FC034)
#define ISR_TOUT_H0 *((volatile int *)0xB82FC038)
#define LOG_ADDR0 *((volatile int *)0xB82FC03C)

// SWIC1 Registers
#define HW_VER1 *((volatile int *)0xB82FD000)
#define STATUS1 *((volatile int *)0xB82FD004)
#define RX_CODE1 *((volatile int *)0xB82FD008)
#define MODE_CR1 *((volatile int *)0xB82FD00C)
#define TX_SPEED1 *((volatile int *)0xB82FD010)
#define TX_CODE1 *((volatile int *)0xB82FD014)
#define RX_SPEED1 *((volatile int *)0xB82FD018)
#define CNT_RX0_PACK1 *((volatile int *)0xB82FD01C)
#define CNT_RX_PACK1 *((volatile int *)0xB82FD020)
#define ISR_L1 *((volatile int *)0xB82FD024)
#define ISR_H1 *((volatile int *)0xB82FD028)
#define TRUE_TIME1 *((volatile int *)0xB82FD02C)
#define TOUT_CODE1 *((volatile int *)0xB82FD030)
#define ISR_TOUT_L1 *((volatile int *)0xB82FD034)
#define ISR_TOUT_H1 *((volatile int *)0xB82FD038)
#define LOG_ADDR1 *((volatile int *)0xB82FD03C)

// GSWIC0 Registers
#define GSW_HW_VER0 *((volatile int *)0xB82FE000)
#define GSW_STATUS0 *((volatile int *)0xB82FE004)
#define GSW_RX_CODE0 *((volatile int *)0xB82FE008)
#define GSW_MODE_CR0 *((volatile int *)0xB82FE00C)
#define GSW_TX_CONTROL0 *((volatile int *)0xB82FE010)
#define GSW_TX_CODE0 *((volatile int *)0xB82FE014)
#define GSW_CNT_RX_PACK0 *((volatile int *)0xB82FE020)
#define GSW_ISR_L0 *((volatile int *)0xB82FE024)
#define GSW_ISR_H0 *((volatile int *)0xB82FE028)
#define GSW_TRUE_TIME0 *((volatile int *)0xB82FE02C)
#define GSW_TOUT_CODE0 *((volatile int *)0xB82FE030)
#define GSW_ISR_TOUT_L0 *((volatile int *)0xB82FE034)
#define GSW_ISR_TOUT_H0 *((volatile int *)0xB82FE038)
#define GSW_LOG_ADDR0 *((volatile int *)0xB82FE03C)
#define GSW_PMA_STATUS0 *((volatile int *)0xB82FE040)
#define GSW_PMA_MODE0 *((volatile int *)0xB82FE044)
#define GSW_PMA_TX_LB0 *((volatile int *)0xB82FE080)
#define GSW_PMA_RX_LB0 *((volatile int *)0xB82FE084)

// GSWIC1 Registers
#define GSW_HW_VER1 *((volatile int *)0xB82FF000)
#define GSW_STATUS1 *((volatile int *)0xB82FF004)
#define GSW_RX_CODE1 *((volatile int *)0xB82FF008)
#define GSW_MODE_CR1 *((volatile int *)0xB82FF00C)
#define GSW_TX_CONTROL1 *((volatile int *)0xB82FF010)
#define GSW_TX_CODE1 *((volatile int *)0xB82FF014)
#define GSW_CNT_RX_PACK1 *((volatile int *)0xB82FF020)
#define GSW_ISR_L1 *((volatile int *)0xB82FF024)
#define GSW_ISR_H1 *((volatile int *)0xB82FF028)
#define GSW_TRUE_TIME1 *((volatile int *)0xB82FF02C)
#define GSW_TOUT_CODE1 *((volatile int *)0xB82FF030)
#define GSW_ISR_TOUT_L1 *((volatile int *)0xB82FF034)
#define GSW_ISR_TOUT_H1 *((volatile int *)0xB82FF038)
#define GSW_LOG_ADDR1 *((volatile int *)0xB82FF03C)
#define GSW_PMA_STATUS1 *((volatile int *)0xB82FF040)
#define GSW_PMA_MODE1 *((volatile int *)0xB82FF044)
#define GSW_PMA_TX_LB1 *((volatile int *)0xB82FF080)
#define GSW_PMA_RX_LB1 *((volatile int *)0xB82FF084)

// UART0 Registers
#define UART0_RBR *((volatile int *)0xb82F3000)
#define UART0_THR *((volatile int *)0xb82F3000)
#define UART0_IER *((volatile int *)0xb82F3004)
#define UART0_IIR *((volatile int *)0xb82F3008)
#define UART0_FCR *((volatile int *)0xb82F3008)
#define UART0_LCR *((volatile int *)0xb82F300C)
#define UART0_MCR *((volatile int *)0xb82F3010)
#define UART0_LSR *((volatile int *)0xb82F3014)
#define UART0_MSR *((volatile int *)0xb82F3018)
#define UART0_SPR *((volatile int *)0xb82F301C)
#define UART0_DLL *((volatile int *)0xb82F3000)
#define UART0_DLM *((volatile int *)0xb82F3004)
#define UART0_SCLR *((volatile int *)0xb82F3014)

// UART1 Registers
#define UART1_RBR *((volatile int *)0xb82F3400)
#define UART1_THR *((volatile int *)0xb82F3400)
#define UART1_IER *((volatile int *)0xb82F3404)
#define UART1_IIR *((volatile int *)0xb82F3408)
#define UART1_FCR *((volatile int *)0xb82F3408)
#define UART1_LCR *((volatile int *)0xb82F340C)
#define UART1_MCR *((volatile int *)0xb82F3410)
#define UART1_LSR *((volatile int *)0xb82F3414)
#define UART1_MSR *((volatile int *)0xb82F3418)
#define UART1_SPR *((volatile int *)0xb82F341C)
#define UART1_DLL *((volatile int *)0xb82F3400)
#define UART1_DLM *((volatile int *)0xb82F3404)
#define UART1_SCLR *((volatile int *)0xb82F3414)

//
// External UART registers.
//
#define MC_R(a) *(volatile unsigned *)(0xB82F0000 + (a))

#define MC_RBR(i) MC_R(0x3000 + (i * 0x400)) /* �������� �������� ������� */
#define MC_THR(i) MC_R(0x3000 + (i * 0x400)) /* ���������� �������� ������� */
#define MC_IER(i)                                               \
  MC_R(0x3004 + (i * 0x400)) /* ������� ���������� ���������� \
                              */
#define MC_IIR(i) \
  MC_R(0x3008 + (i * 0x400)) /* ������� ������������� ���������� */
#define MC_FCR(i) MC_R(0x3008 + (i * 0x400)) /* ������� ���������� FIFO */
#define MC_LCR(i) MC_R(0x300C + (i * 0x400)) /* ������� ���������� ������ */
#define MC_MCR(i) MC_R(0x3010 + (i * 0x400)) /* ������� ���������� ������� */
#define MC_LSR(i) MC_R(0x3014 + (i * 0x400)) /* ������� ��������� ����� */
#define MC_MSR(i) MC_R(0x3018 + (i * 0x400)) /* ������� ��������� ������� */
#define MC_SPR(i) MC_R(0x301C + (i * 0x400)) /* ������� Scratch Pad */
#define MC_DLL(i) MC_R(0x3000 + (i * 0x400)) /* ������� �������� ������� */
#define MC_DLM(i) MC_R(0x3004 + (i * 0x400)) /* ������� �������� ������� */
#define MC_SCLR(i) \
  MC_R(0x3014 + (i * 0x400)) /* ������� ������������ (scaler) */

// IT0 Registers
#define ITCSR0 *((volatile int *)0xb82F5020)
#define ITPERIOD0 *((volatile int *)0xb82F5024)
#define ITCOUNT0 *((volatile int *)0xb82F5028)
#define ITSCALE0 *((volatile int *)0xb82F502C)

// WDT Registers
#define WTCSR *((volatile int *)0xb82F5010)
#define WTPERIOD *((volatile int *)0xb82F5014)
#define WTCOUNT *((volatile int *)0xb82F5018)
#define WTSCALE *((volatile int *)0xb82F501C)

// IT1 Registers
#define ITCSR1 *((volatile int *)0xb82F5000)
#define ITPERIOD1 *((volatile int *)0xb82F5004)
#define ITCOUNT1 *((volatile int *)0xb82F5008)
#define ITSCALE1 *((volatile int *)0xb82F500C)
/*
//MFBSP0 Registers
#define	TX_MFBSP0		*((volatile int *)0xb82F8000)
#define	RX_MFBSP0		*((volatile int *)0xb82F8000)
#define	CSR_MFBSP0		*((volatile int *)0xb82F8004)
#define	DIR_MFBSP0		*((volatile int *)0xb82F8008)
#define	GPIO_DR0		*((volatile int *)0xb82F800C)
#define	TCTR0			*((volatile int *)0xb82F8010)
#define	RCTR0			*((volatile int *)0xb82F8014)
#define	TSR0			*((volatile int *)0xb82F8018)
#define	RSR0			*((volatile int *)0xb82F801C)
#define	TCTR_RATE0		*((volatile int *)0xb82F8020)
#define	RCTR_RATE0		*((volatile int *)0xb82F8024)

//MFBSP1 Registers
#define	TX_MFBSP1		*((volatile int *)0xb82F9000)
#define	RX_MFBSP1		*((volatile int *)0xb82F9000)
#define	CSR_MFBSP1		*((volatile int *)0xb82F9004)
#define	DIR_MFBSP1		*((volatile int *)0xb82F9008)
#define	GPIO_DR1		*((volatile int *)0xb82F900C)
#define	TCTR1			*((volatile int *)0xb82F9010)
#define	RCTR1			*((volatile int *)0xb82F9014)
#define	TSR1			*((volatile int *)0xb82F9018)
#define	RSR1			*((volatile int *)0xb82F901C)
#define	TCTR_RATE1		*((volatile int *)0xb82F9020)
#define	RCTR_RATE1		*((volatile int *)0xb82F9024)
*/
// MPORT Registers
#define CSCON0 *((volatile int *)0xb82F1000)
#define CSCON1 *((volatile int *)0xb82F1004)
#define CSCON2 *((volatile int *)0xb82F1008)
#define CSCON3 *((volatile int *)0xb82F100C)
#define CSCON4 *((volatile int *)0xb82F1010)
#define SDRCON *((volatile int *)0xb82F1014)
#define SDRTMR *((volatile int *)0xb82F1018)
#define SDRCSR *((volatile int *)0xb82F101C)
#define CSR_EXT *((volatile int *)0xb82F1024)
#define AERROR_EXT *((volatile int *)0xb82F1028)
#define NRFTMR *((volatile int *)0xb82F102C)
#define NDFPSR *((volatile int *)0xb82F1030)
#define NDFTMW *((volatile int *)0xb82F1034)
#define NDFTMR *((volatile int *)0xb82F1038)
#define NDFWPR *((volatile int *)0xb82F103C)

// System Registers
#define CR_PLL *((volatile int *)0xb82F4000)
#define CLK_EN *((volatile int *)0xb82F4004)
#define CLK_EN_CORE (1 << 0)
#define CLK_EN_MFBSP0 (1 << 8)
#define CLK_EN_MFBSP1 (1 << 9)
#define CLK_EN_DMA0 (1 << 12)
#define CLK_EN_DMA1 (1 << 13)
#define CLK_EN_SWIC0 (1 << 24)
#define CLK_EN_SWIC1 (1 << 25)
#define CLK_EN_GSWIC0 (1 << 26)
#define CLK_EN_GSWIC1 (1 << 27)

#define SYS_CSR(i) *((volatile int *)(0xb82F4008 + 0x40 * i))
#define MASKR0(i) *((volatile int *)(0xb82F4010 + 0x40 * i))
#define QSTR0(i) *((volatile int *)(0xb82F4014 + 0x40 * i))
#define MASKR1(i) *((volatile int *)(0xb82F4018 + 0x40 * i))
#define QSTR1(i) *((volatile int *)(0xb82F401C + 0x40 * i))
#define MASKR2(i) *((volatile int *)(0xb82F4020 + 0x40 * i))
#define QSTR2(i) *((volatile int *)(0xb82F4024 + 0x40 * i))
#define MASKR3(i) *((volatile int *)(0xb82F4028 + 0x40 * i))
#define QSTR3(i) *((volatile int *)(0xb82F402C + 0x40 * i))
#define MASKR4(i) *((volatile int *)(0xb82F4038 + 0x40 * i))
#define QSTR4(i) *((volatile int *)(0xb82F403C + 0x40 * i))
#define IRQM *((volatile int *)0xb82F4030)
// #define	MASKR(i)		*((volatile int *)0xb82F4010 + (i*8))
// #define	QSTR(i)			*((volatile int *)0xb82F4014 + (i*8))

// Hamming code registers
#define CSR_CRAM0A *((volatile int *)0xb82F4400)
#define AERROR_CRAM0A *((volatile int *)0xb82F4404)
#define CSR_CRAM0B *((volatile int *)0xb82F4408)
#define AERROR_CRAM0B *((volatile int *)0xb82F440C)
#define CSR_CRAM1A *((volatile int *)0xb82F4410)
#define AERROR_CRAM1A *((volatile int *)0xb82F4414)
#define CSR_CRAM1B *((volatile int *)0xb82F4418)
#define AERROR_CRAM1B *((volatile int *)0xb82F441C)
#define CSR_CRAM2A *((volatile int *)0xb82F4420)
#define AERROR_CRAM2A *((volatile int *)0xb82F4424)
#define CSR_CRAM2B *((volatile int *)0xb82F4428)
#define AERROR_CRAM2B *((volatile int *)0xb82F442C)
#define CSR_CRAM3A *((volatile int *)0xb82F4430)
#define AERROR_CRAM3A *((volatile int *)0xb82F4434)
#define CSR_CRAM3B *((volatile int *)0xb82F4438)
#define AERROR_CRAM3B *((volatile int *)0xb82F443C)
#define CSR_ICACHE *((volatile int *)0xb82F4800)
#define AERROR_ICACHE *((volatile int *)0xb82F4804)
#define CSR_DCACHE *((volatile int *)0xb82F4C00)
#define AERROR_DCACHE *((volatile int *)0xb82F4C04)

#endif  //___MCL_MCT03_H___
