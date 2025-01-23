// Copyright 2023-2025 RnD Center "ELVEES", JSC
// SPDX-License-Identifier: MIT

#include "system.h"

#include "mct06.h"

unsigned int sys_kernel_pa_to_va(unsigned int pa) {
  if (pa < 0x40000000) return (pa + 0xa0000000);
  if (pa < 0xC0000000) return (pa - 0x40000000);
  return pa;
}
unsigned int sys_kernel_va_to_pa(unsigned int va) {
  if (va >= 0xE0000000) return va;
  if (va >= 0xa0000000) return (va - 0xa0000000);
  if (va < 0x80000000) return (va + 0x40000000);
  return sys_kernel_va_to_pa(va | 0x20000000);  // cache address
}

unsigned get_cpu_clock(void) {
  if (CR_PLL & 0x80)
    if (CR_PLL & 0x7f)
      return ((XTI) * (CR_PLL & 0x7f));
    else
      return XTI >> 4;
  else
    return XTI;
}

unsigned get_dsp_clock(void) {
#if (defined(TARGET_NVCOM02T) || defined(TARGET_MC30SF6))
  return ((XTI) * ((CR_PLL & 0x7f0000) >> 16));
#else
  return 0;
#endif
};

unsigned _get_cpu_id(void) {
#if (defined(TARGET_MCT04))
  return 0;
#else
  return 0;
#endif
}
