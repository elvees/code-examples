// Copyright 2023-2025 RnD Center "ELVEES", JSC
// SPDX-License-Identifier: MIT

// *******************************************************************
//                 Risc-Dsp runtime library
//
// Interface to enable/disable risc interrupts
// by setting MASKR0, MASKR1, MASKR2
// This file contains handler function. Don't use it!
// Use library interface
//
// *******************************************************************

#include "risc_interrupt.h"

#include "mct06.h"
#include "system.h"

#define MASKR_NUM_MAX (5)
static volatile RISC_INTERRUPT risc_hnlr_func[MASKR_NUM_MAX * 32 + 16] = {
    RISC_INTERRUPT_UNKNOWN};
#define CPU_NUMS (1)
#define MASKR_NUMS (6)
static volatile int* MASKR[CPU_NUMS][MASKR_NUMS] = {
    &MASKR0(0), &MASKR1(0), &MASKR2(0), &MASKR3(0), &MASKR4(0), &MASKR_DSP};

static volatile int* QSTR[CPU_NUMS][MASKR_NUMS] = {
    &QSTR0(0), &QSTR1(0), &QSTR2(0), &QSTR3(0), &QSTR4(0), &QSTR_DSP};

#define SET_TR_CRAM() SYS_CSR(_get_cpu_id()) |= 2
#define UNSET_TR_CRAM() SYS_CSR(_get_cpu_id()) &= ~(2)
void risc_set_interrupts_vector(INTERRUPT_VECTORS loc) {
  unsigned int temp = 0;
  asm volatile("mfc0 %0, $12" : "=r"(temp));
  temp &= ~(4);
  asm volatile("mtc0 %0, $12" ::"r"(temp));

  switch (loc) {
    case INTH_80000180:
      mips_write_c0_register(C0_CAUSE, 0);
      temp = mips_read_c0_register(C0_STATUS);
      temp &= ~(1 << 22);
      mips_write_c0_register(C0_STATUS, temp);
      UNSET_TR_CRAM();
      break;
    case INTH_B8000180:
      mips_write_c0_register(C0_CAUSE, 0);
      temp = mips_read_c0_register(C0_STATUS);
      temp &= ~(1 << 22);
      mips_write_c0_register(C0_STATUS, temp);
      SET_TR_CRAM();
      break;
    case INTH_BFC00380:
      mips_write_c0_register(C0_CAUSE, 0);
      temp = mips_read_c0_register(C0_STATUS);
      temp |= (1 << 22);
      mips_write_c0_register(C0_STATUS, temp);
      break;
    case INTH_80000200:
      mips_write_c0_register(C0_CAUSE, (1 << 23));
      temp = mips_read_c0_register(C0_STATUS);
      temp &= ~(1 << 22);
      mips_write_c0_register(C0_STATUS, temp);
      UNSET_TR_CRAM();
      break;
    case INTH_B8000200:
      mips_write_c0_register(C0_CAUSE, (1 << 23));
      temp = mips_read_c0_register(C0_STATUS);
      temp &= ~(1 << 22);
      mips_write_c0_register(C0_STATUS, temp);
      SET_TR_CRAM();
      break;
    case INTH_BFC00400:
      mips_write_c0_register(C0_CAUSE, (1 << 23));
      temp = mips_read_c0_register(C0_STATUS);
      temp |= (1 << 22);
      mips_write_c0_register(C0_STATUS, temp);
      break;
  };
}

void risc_disable_interrupts() {
  unsigned int CP0_Status = mips_read_c0_register(C0_STATUS);
  CP0_Status &= ~(0x1);
  mips_write_c0_register(C0_STATUS, CP0_Status);
  *QSTR[0][0] = 0x0;
}

void risc_enable_interrupts() {
  unsigned int CP0_Status;
  CP0_Status = mips_read_c0_register(C0_STATUS);
  CP0_Status &= ~((1 << 1) | (1 << 2));
  CP0_Status |= ((1 << 22) | (1 << 0) | (1 << 14));
  mips_write_c0_register(C0_STATUS, CP0_Status);
}
void risc_reset_cause() {
  unsigned int CP0_Cause;
  CP0_Cause = mips_read_c0_register(C0_CAUSE);
  CP0_Cause &= 0x7F83;
  mips_write_c0_register(C0_CAUSE, CP0_Cause);
}
static int type_to_index(RISC_INTERRUPT_TYPE type) {
  unsigned int index = 0;
  unsigned int temp = 0;
  temp = type >> 8;
  if (temp == 8)
    return (129 + (type & 0xFF));
  else {
    index = (type) & 0x1F;
    index |= (type & ~0x1F) >> 3;
  }
  return index;
}

enum ERL_ERROR risc_register_interrupt(RISC_INTERRUPT fn,
                                       RISC_INTERRUPT_TYPE type) {
  if (fn != 0) {
    unsigned int index = type_to_index(type);
    risc_hnlr_func[index] = fn;
  } else
    return ERL_UNITIALIZED_ARG;
  return ERL_NO_ERROR;
}

// TODO

static int get_power_of(unsigned int v) {
  int cnt = 0;
  asm volatile(
      "move $t2, %1\n\t"
      "clz $t3, $t2\n\t"
      "move %0, $t3\n\t"
      : "=r"(cnt)
      : "r"(v));
  return 31 - cnt;
}

static int get_cause_risc(unsigned int v, unsigned int cpu_id) {
  int i = 0;
  unsigned int qstr_num = 6, temp;
  for (i = 0; i < 5; i++) {
    temp = (v >> (10 + i)) & 1;
    if (temp) qstr_num = i;
  }

  if ((qstr_num >= 0) && (qstr_num <= 2)) {
    unsigned int maskr_val = *MASKR[cpu_id][qstr_num];
    unsigned int qstr_val = *QSTR[cpu_id][qstr_num];
    unsigned int bit = get_power_of(maskr_val & qstr_val);
    return (qstr_num << 8) | bit;
  } else if (qstr_num == 3) {
    unsigned int maskr_val = *MASKR[cpu_id][qstr_num];
    unsigned int qstr_val = *QSTR[cpu_id][qstr_num];
    if (maskr_val & qstr_val) {
      unsigned int bit = get_power_of(maskr_val & qstr_val);
      return (qstr_num << 8) | bit;
    } else {
      unsigned int maskr_val = *MASKR[cpu_id][qstr_num + 1];
      unsigned int qstr_val = *QSTR[cpu_id][qstr_num + 1];
      unsigned int bit = get_power_of(maskr_val & qstr_val);
      return (qstr_num + 1 << 8) | bit;
    }

  } else if (v & 0x8000) {
    // RISC_INT_COMPARE
    return RISC_COMPARE;
  } else if (v & 0x4000) {
    switch (QSTR_DSP) {
      case 0x1:
        return DSP_INT_PI0;
        break;
      case 0x2:
        return DSP_INT_SE0;
        break;
      case 0x4:
        return DSP_INT_BREAK0;
        break;
      case 0x8:
        return DSP_INT_STP0;
        break;
      case 0x100:
        return DSP_INT_PI1;
        break;
      case 0x200:
        return DSP_INT_SE1;
        break;
      case 0x400:
        return DSP_INT_BREAK1;
        break;
      case 0x800:
        return DSP_INT_STP1;
        break;
      case 0x10000000:
        return DSP_INT_WAIT;
        break;
      default:
        return ERL_UNITIALIZED_ARG;
        break;
    }
  }
  // Exceptions
  if (((v & 0x7F) >> 2) == 1)
    return RICS_EXC_MOD;
  else if (((v & 0x7F) >> 2) == 2)
    return RICS_EXC_TLBL;
  else if (((v & 0x7F) >> 2) == 3)
    return RICS_EXC_TLBS;
  else if (((v & 0x7F) >> 2) == 4)
    return RICS_EXC_ADEL;
  else if (((v & 0x7F) >> 2) == 5)
    return RICS_EXC_ADES;
  else if (((v & 0x7F) >> 2) == 8)
    return RICS_EXC_SYS;
  else if (((v & 0x7F) >> 2) == 9)
    return RICS_EXC_BP;
  else if (((v & 0x7F) >> 2) == 10)
    return RICS_EXC_RI;
  else if (((v & 0x7F) >> 2) == 11)
    return RICS_EXC_CPU;
  else if (((v & 0x7F) >> 2) == 12)
    return RICS_EXC_OV;
  else if (((v & 0x7F) >> 2) == 13)
    return RICS_EXC_TRAP;
  else if (((v & 0x7F) >> 2) == 15)
    return RICS_EXC_FPE;
  else if (((v & 0x7F) >> 2) == 24)
    return RICS_EXC_MCHECK;
  return 0;
}

void risc_enable_interrupt(RISC_INTERRUPT_TYPE type, int cpu_id) {
  unsigned int CP0_Status = 0;
  unsigned int qstr_num = 0;
  unsigned int qstr_bit = 0;

  qstr_num = (type >> 8) & 0xFF;
  qstr_bit = type & 0xFF;
  if ((qstr_num >= 0) && (qstr_num < 6)) {
    CP0_Status = mips_read_c0_register(C0_STATUS);

    CP0_Status |= 1 << (10 + ((qstr_num == 4) ? 3 : qstr_num));
    CP0_Status |= 1;

    mips_write_c0_register(C0_STATUS, CP0_Status);

    *MASKR[cpu_id][qstr_num] |= 1 << (qstr_bit);  // [10:8]
  } else if (type == RISC_COMPARE) {
    // RISC_COMPARE
    CP0_Status = mips_read_c0_register(C0_STATUS);
    mips_write_c0_register(C0_STATUS, (CP0_Status | 0x8001));
  }
}

void risc_disable_interrupt(RISC_INTERRUPT_TYPE type, int cpu_id) {
  unsigned int CP0_Status = 0;
  unsigned int qstr_num = 0;
  unsigned int qstr_bit = 0;

  qstr_num = (type >> 8) & 0xFF;
  qstr_bit = type & 0xFF;
  if (qstr_bit != 0) {
    *MASKR[cpu_id][qstr_num] &= ~(1 << (qstr_bit));
  } else if (qstr_num < 6) {
    asm volatile("mfc0 %0, $12" : "=r"(CP0_Status));
    CP0_Status &= ~(1 << (10 + qstr_num));
    asm volatile("mtc0 %0, $12" ::"r"(CP0_Status));
  }
}

void risc_common_handler(int cpu_id) {
  unsigned int v = 0;
  int cause = 0;
  asm volatile("mfc0 %0, $13" : "=r"(v));
  cause = get_cause_risc(v, 0);
  int index = type_to_index(cause);

  if ((cause <= RISC_INT_MEMCH_MAX) &&
      (cause >= RISC_INT_MEMCH0)  // calls handler
      && (risc_hnlr_func[index] !=
          RISC_INTERRUPT_UNKNOWN))  // for all DMA memch interrupts
  {
    risc_hnlr_func[index](cause);  // arg - RISC_INT_MEMCHx value
  }

  else {
    if ((cause <= 31) && (cause >= 0)  // calls handler
        && (risc_hnlr_func[index] !=
            RISC_INTERRUPT_UNKNOWN))  // for all interrupts
    {
      risc_hnlr_func[index](cause);  // arg - RISC_INT_... value
    } else if (risc_hnlr_func[index] != RISC_INTERRUPT_UNKNOWN) {
      risc_hnlr_func[index](-1);
    }
  }
}
