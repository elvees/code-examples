// Copyright 2023-2025 RnD Center "ELVEES", JSC
// SPDX-License-Identifier: MIT

#include "risc_runtime/mct06.h"
#include "risc_runtime/risc_interrupt.h"

int ExitStatus = 3;
int interupt_flag = 0;

extern unsigned int DSP0_In_A;
extern unsigned int DSP0_In_B;
extern unsigned int DSP0_Out_C;
extern unsigned int DSP0_calculate;

void DSP0_handler(void) {
  DCSR(0) = 0;  // Сбрасываем прерывание
  interupt_flag = 1;

  /* Place breakpoint here */
  asm("nop");
}

int main() {
  unsigned int DSP0_InputA = 5;
  unsigned int DSP0_InputB = 2;
  unsigned int DSP0_OutputC;

  risc_enable_interrupts();
  risc_set_interrupts_vector(INTH_B8000180);
  risc_enable_interrupt(DSP_INT_STP0, 0);
  risc_register_interrupt(DSP0_handler, DSP_INT_STP0);

  while (1) {
    DSP0_In_A = DSP0_InputA;
    DSP0_In_B = DSP0_InputB;
    DSP0_OutputC = 0;
    // настраиваем регистры DSP(i)
    DCSR(0) = 0;
    SR(0) = 0;
    // заносим в регистр PC ядeр DSP(i) адрес функции DSP(i)_calculate()
    // запускаем DSP(i)
    PC(0) = ((unsigned int)&DSP0_calculate - 0xb8440000) >> 2;
    DCSR(0) = 0x4000;

    // ждём пока ядро MIPS обработает прерывание
    while (!interupt_flag);

    DSP0_OutputC = DSP0_Out_C;
    if (DSP0_OutputC == (DSP0_In_A + DSP0_In_B)) {
      ExitStatus = 0;
      /* Place breakpoint here */
      asm("nop");
    } else
      ExitStatus = 1;
  }

  return ExitStatus;
}
