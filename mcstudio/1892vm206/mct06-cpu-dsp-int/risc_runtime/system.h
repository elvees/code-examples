// Copyright 2023-2025 RnD Center "ELVEES", JSC
// SPDX-License-Identifier: MIT

// *******************************************************************
//
// This file implements macros for mips coprocessors cp0 and cp1
//  registers read-write access
//
// *******************************************************************
#ifndef _SYSTEM_H_
#define _SYSTEM_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "mct06.h"
// quartz frequency
#define MHz 1000000

#define XTI (5 * MHz)
#define XTI_125 (125 * MHz)
#define XTI_11 (11 * MHz)
#define RTCXTI (32768)

#define MC_R(a) *(volatile unsigned*)(0xB82F0000 + (a))
#define C0_CONFIG 16
#define MC_CSR MC_R(0x4008)

#define MC_CSR_FM 0x00000001
#define MC_CSR_TST_CACHE 0x00000800
#define MC_CSR_FLUSH_I 0x00001000
#define MC_CSR_FLUSH_D 0x00004000

#define MAX_BENCHMARK 10

#define ISALIGNED64(x) ((((unsigned int)(x)) & 0x7) == 0)

// C0 coprocessor registers
#define C0_INDEX 0     /* индекс доступа к TLB */
#define C0_RANDOM 1    /* индекс TLB для команды Write Random */
#define C0_ENTRYLO0 2  /* строки для чётных страниц TLB */
#define C0_ENTRYLO1 3  /* строки для нечётных страниц TLB */
#define C0_CONTEXT 4   /* указатель на таблицу PTE */
#define C0_PAGEMASK 5  /* маска размера страниц TLB */
#define C0_WIRED 6     /* граница привязанных строк TLB */
#define C0_BADVADDR 8  /* виртуальный адрес последнего исключения */
#define C0_COUNT 9     /* таймер */
#define C0_ENTRYHI 10  /* информация соответствия виртуального адреса */
#define C0_COMPARE 11  /* предельное значение для прерывания по таймеру */
#define C0_STATUS 12   /* режимы функционирования процессора */
#define C0_CAUSE 13    /* причина последнего исключения */
#define C0_EPC 14      /* адрес возврата из исключения */
#define C0_PRID 15     /* идентификатор процессора */
#define C0_CONFIG 16   /* информация о возможностях процессора */
#define C0_LLADDR 17   /* физический адрес последней команды LL */
#define C0_ERROREPC 30 /* адрес возврата из исключения ошибки */

//
// read C0 coprocessor register.
//
#define mips_read_c0_register(reg)                            \
  ({                                                          \
    int __value;                                              \
    asm volatile("mfc0	%0, $%1" : "=r"(__value) : "K"(reg)); \
    __value;                                                  \
  })

//
// read C0 coprocessor register with select
//
#define mips_read_c0_select(reg, sel)                                       \
  ({                                                                        \
    int __value;                                                            \
    asm volatile("mfc0	%0, $%1, %2" : "=r"(__value) : "K"(reg), "K"(sel)); \
    __value;                                                                \
  })

//
// write C0 coprocessor register.
//
#define mips_write_c0_register(reg, value)                \
  do {                                                    \
    asm volatile("mtc0	%z0, $%1 \n	nop \n	nop \n	nop"     \
                 :                                        \
                 : "r"((unsigned int)(value)), "K"(reg)); \
  } while (0)

//
// write C0 coprocessor register with select
//
#define mips_write_c0_select(reg, sel, value)                       \
  do {                                                              \
    asm volatile("mtc0	%z0, $%1, %2 \n	nop \n	nop \n	nop"           \
                 :                                                  \
                 : "r"((unsigned int)(value)), "K"(reg), "K"(sel)); \
  } while (0)

//
// read FPU (C1 coprocessor) register.
//
#define mips_read_fpu_register(reg)                           \
  ({                                                          \
    int __value;                                              \
    asm volatile("mfc1	%0, $%1" : "=r"(__value) : "K"(reg)); \
    __value;                                                  \
  })

//
// write FPU (C1 coprocessor) register.
//
#define mips_write_fpu_register(reg, value)                  \
  do {                                                       \
    asm volatile("mtc1	%z0, $%1" : : "r"(value), "K"(reg)); \
  } while (0)

//
// read FPU control register.
//
#define mips_read_fpu_control(reg)                            \
  ({                                                          \
    int __value;                                              \
    asm volatile("cfc1	%0, $%1" : "=r"(__value) : "K"(reg)); \
    __value;                                                  \
  })

//
// write FPU control register.
//
#define mips_write_fpu_control(reg, value)                                   \
  do {                                                                       \
    asm volatile("ctc1	%z0, $%1" : : "r"((unsigned int)(value)), "K"(reg)); \
  } while (0)

// Section: Functions
//
// Function: sys_kernel_pa_to_va
//
// Translation physical address to virtual address in kernel mode.
//
// Parameters:
//      pa      - physical address
//
// > char* sdram_pointer = (char*) sys_kernel_pa_to_va(0x00000000);
//
// See also:
//
//
unsigned int sys_kernel_pa_to_va(unsigned int pa);

// Function: sys_kernel_va_to_pa
//
// Translation virtual address to physical address in kernel mode.
//
// Parameters:
//      va      - virtual address
//
// > dma_ch->IR0 = sys_kernel_va_to_pa((unsigned) src); //convert programm's
// pointers to physical addresses > dma_ch->IR1 = sys_kernel_va_to_pa((unsigned)
// dst);
//
// See also:
//
//
unsigned int sys_kernel_va_to_pa(unsigned int va);

// Function: get_cpu_clock
//
// Get CPU frequency
//
// Returns:
//		CPU clock
//
unsigned get_cpu_clock(void);

// Function: get_dsp_clock
//
// Get DSP frequency
//
// Returns:
//		CPU clock
//
unsigned get_dsp_clock(void);

// Function: _get_cpu_id
//
// Get MIPS CPU id in MIPS multicore system
//
// Returns:
//		MIPS CPU id
//
unsigned _get_cpu_id(void);

#ifdef __cplusplus
}
#endif

#endif  // _SYSTEM_H_
