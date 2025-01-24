// Copyright 2023-2025 RnD Center "ELVEES", JSC
// SPDX-License-Identifier: MIT

//*******************************************************************************
//		Микросхема 1892ВМ12Т (MCT-03P)
// 		Адреса устройств для программного доступа.
//
//*****************************************************************************/

#ifndef MCT03P_MEM_MAP_H_
#define MCT03P_MEM_MAP_H_

#define KSEG1_SHIFT 0xa0000000
//==============================================================
//		CRAM
//==============================================================
#define CRAM_ADDR 0x18000000 + KSEG1_SHIFT
#define SIZE_CRAM 0x80
//==============================================================
//		CPU
//==============================================================
#define CPU_REGS_BASE_ADDR 0x182f0000 + KSEG1_SHIFT
//==========================================================
#define DMA_MEM_CH00_ADDR (CPU_REGS_BASE_ADDR + 0x0000)
#define DMA_MEM_CH01_ADDR (CPU_REGS_BASE_ADDR + 0x0080)
#define DMA_MEM_CH02_ADDR (CPU_REGS_BASE_ADDR + 0x0100)
#define DMA_MEM_CH03_ADDR (CPU_REGS_BASE_ADDR + 0x0180)

#define DMA_MEM_CH10_ADDR (CPU_REGS_BASE_ADDR + 0x0400)
#define DMA_MEM_CH11_ADDR (CPU_REGS_BASE_ADDR + 0x0480)
#define DMA_MEM_CH12_ADDR (CPU_REGS_BASE_ADDR + 0x0500)
#define DMA_MEM_CH13_ADDR (CPU_REGS_BASE_ADDR + 0x0580)
//==========================================================
#define MFBSP0_ADDR (CPU_REGS_BASE_ADDR + 0x8000)
#define MFBSP1_ADDR (CPU_REGS_BASE_ADDR + 0x9000)

#define DMA_MFBSP_TX_CH0_ADDR (CPU_REGS_BASE_ADDR + 0x8800)
#define DMA_MFBSP_RX_CH0_ADDR (CPU_REGS_BASE_ADDR + 0x8840)
#define DMA_MFBSP_TX_CH1_ADDR (CPU_REGS_BASE_ADDR + 0x9800)
#define DMA_MFBSP_RX_CH1_ADDR (CPU_REGS_BASE_ADDR + 0x9840)
//==========================================================
#define SWIC0_ADDR (CPU_REGS_BASE_ADDR + 0xc000)
#define SWIC1_ADDR (CPU_REGS_BASE_ADDR + 0xd000)

#define DMA_SW0_RX_DES_CH0_ADDR (CPU_REGS_BASE_ADDR + 0xc800)
#define DMA_SW0_RX_DAT_CH0_ADDR (CPU_REGS_BASE_ADDR + 0xc840)
#define DMA_SW0_TX_DES_CH0_ADDR (CPU_REGS_BASE_ADDR + 0xc880)
#define DMA_SW0_TX_DAT_CH0_ADDR (CPU_REGS_BASE_ADDR + 0xc8c0)

#define DMA_SW1_RX_DES_CH1_ADDR (CPU_REGS_BASE_ADDR + 0xd800)
#define DMA_SW1_RX_DAT_CH1_ADDR (CPU_REGS_BASE_ADDR + 0xd840)
#define DMA_SW1_TX_DES_CH1_ADDR (CPU_REGS_BASE_ADDR + 0xd880)
#define DMA_SW1_TX_DAT_CH1_ADDR (CPU_REGS_BASE_ADDR + 0xd8c0)
//==========================================================
#define GSWIC0_ADDR (CPU_REGS_BASE_ADDR + 0xe000)
#define GSWIC1_ADDR (CPU_REGS_BASE_ADDR + 0xf000)

#define DMA_GSW0_RX_DES_CH0_ADDR (CPU_REGS_BASE_ADDR + 0xe800)
#define DMA_GSW0_RX_DAT_CH0_ADDR (CPU_REGS_BASE_ADDR + 0xe840)
#define DMA_GSW0_TX_DES_CH0_ADDR (CPU_REGS_BASE_ADDR + 0xe880)
#define DMA_GSW0_TX_DAT_CH0_ADDR (CPU_REGS_BASE_ADDR + 0xe8c0)

#define DMA_GSW1_RX_DES_CH1_ADDR (CPU_REGS_BASE_ADDR + 0xf800)
#define DMA_GSW1_RX_DAT_CH1_ADDR (CPU_REGS_BASE_ADDR + 0xf840)
#define DMA_GSW1_TX_DES_CH1_ADDR (CPU_REGS_BASE_ADDR + 0xf880)
#define DMA_GSW1_TX_DAT_CH1_ADDR (CPU_REGS_BASE_ADDR + 0xf8c0)
//==========================================================
#define UART0_ADDR (CPU_REGS_BASE_ADDR + 0x3000)
#define UART1_ADDR (CPU_REGS_BASE_ADDR + 0x3400)

#define IT1_ADDR (CPU_REGS_BASE_ADDR + 0x5000)
#define WDT_ADDR (CPU_REGS_BASE_ADDR + 0x5010)
#define IT0_ADDR (CPU_REGS_BASE_ADDR + 0x5020)

#define MPORT_ADDR (CPU_REGS_BASE_ADDR + 0x1000)

#define SYS_REG_ADDR (CPU_REGS_BASE_ADDR + 0x4000)

#define HAMMING_CRAM_ADDR (CPU_REGS_BASE_ADDR + 0x4400)
#define HAMMING_ICACHE_ADDR (CPU_REGS_BASE_ADDR + 0x4800)
#define HAMMING_DCACHE_ADDR (CPU_REGS_BASE_ADDR + 0x4C00)

//=============================================================
typedef unsigned int Uint32;
typedef unsigned short Uint16;

//==================================================
union DATA_REG_COMMON_UNION {
  unsigned int data;
};
//=============================================================

#endif /* MCT03P_MEM_MAP_H_ */
