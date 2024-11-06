// Copyright 2023-2025 RnD Center "ELVEES", JSC
// SPDX-License-Identifier: MIT

#include "gspw.h"
#include "mct06.h"

#define FREQ 120
#define GSWIC_SPEED 125

unsigned int sys_kernel_va_to_pa(unsigned int va) {
  if (va >= 0xE0000000) return va;
  if (va >= 0xa0000000) return (va - 0xa0000000);
  if (va < 0x80000000) return (va + 0x40000000);
  return sys_kernel_va_to_pa(va | 0x20000000);  // cache address
}

void Sleep(uint32_t delay) {
  for (int i = 0; i < delay; i++) asm volatile("nop");
}
void SleepMs(uint32_t ms) {
  uint32_t ms_ = ms * FREQ * 1000;
  for (int i = 0; i < ms_; i++) asm volatile("nop");
}

int main() {
  CR_PLL = (FREQ == 120) ? 0x00000098 : 0x00000094;
  CLK_EN = 0x00000301;
  Sleep(15);

  int err_counter;
  unsigned int Desc[1] __attribute__((aligned(8)));
  unsigned int txDesc[1] __attribute__((aligned(8)));
  unsigned int packet_len = 16;
  unsigned int tr_data[packet_len] __attribute__((aligned(8)));
  unsigned int rv_data[packet_len] __attribute__((aligned(8)));

  for (int i = 0; i < packet_len - 1; i++) {
    tr_data[i + 1] = tr_data[i] + (1 << i);
  }

  while (1) {
    Open(CH1, GSWIC_SPEED, AUTOSTART);
    Open(CH0, GSWIC_SPEED, LINKSTART);

    while (IsConnected(CH0) && IsConnected(CH1)) {
      memset(rv_data, 0, packet_len * sizeof(int));

      gswic_receiver_packet_run(rv_data, Desc, packet_len * sizeof(int));

      gswic_send_packet(tr_data, txDesc, packet_len * sizeof(int), 1);

      gswic_receiver_packet_wait();

      for (int i = 0; i < packet_len; i++) {
        err_counter += (tr_data[i] != rv_data[i]) ? 1 : 0;
      }

      if (!err_counter) {
        /* Place breakpoint here */
        asm("nop");
        break;
      }
    }

    Close(CH0);
    Close(CH1);
  }
  return 0;
}
