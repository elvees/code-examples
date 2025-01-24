// Copyright 2023-2025 RnD Center "ELVEES", JSC
// SPDX-License-Identifier: MIT

#include "risc_runtime/mct06.h"
#include "risc_runtime/mytypes.h"
#include "risc_runtime/risc_interrupt.h"

void pause() {
  int i = 0;
  for (i = 0; i < 1000000; i++) asm("nop");
}

void swic_int_handler(void) {
  STATUS(SWIC_BASE(0)) = 0x1000;  // Сбрасываем прерывание

  /* Place breakpoint here */
  asm("nop");
}
int main() {
  CR_PLL = 0x8A819494;

  unsigned int packet_len = 16;
  unsigned int Desc[1] __attribute__((aligned));
  unsigned int txDesc[1] __attribute__((aligned));
  unsigned int tr_data[packet_len] __attribute__((aligned(8)));
  unsigned int rv_data[packet_len] __attribute__((aligned(8)));
  int i;
  int err_counter;

  risc_enable_interrupts();
  risc_set_interrupts_vector(INTH_B8000180);
  risc_enable_interrupt(RISC_INT_SW_LINK0, 0);
  risc_register_interrupt(swic_int_handler, RISC_INT_SW_LINK0);

  swic_clear(0);
  swic_clear(1);

  swic_init(0);
  swic_init(1);

  pause();

  /* Проверка соединения */
  while (!swic_is_connected(0));

  /* Установка скорости */
  swic_set_tx_speed(0, 350);

  /* Проверка соединения */
  while (!swic_is_connected(0));

  /* Подготовка отправляемого пакета */
  for (i = 0; i < packet_len - 1; i++) {
    tr_data[i + 1] = tr_data[i] + (1 << i);
  }

  while (1) {
    /* Очистка принимающего массива */
    memset(rv_data, 0, packet_len * sizeof(int));

    /* Запуск принимающего DMA */
    swic_receiver_packet_run(rv_data, Desc[0], packet_len * sizeof(int));

    /* Отправка пакета */
    swic_send_packet(tr_data, txDesc[0], packet_len * sizeof(int), 1);

    /* Ожидание получения пакеты */
    swic_receiver_packet_wait();

    for (i = 0; i < packet_len; i++) {
      err_counter += (tr_data[i] != rv_data[i]) ? 1 : 0;
    }

    if (!err_counter) {
      /* Place breakpoint here */
      asm("nop");
    }
  }

  return 0;
}
