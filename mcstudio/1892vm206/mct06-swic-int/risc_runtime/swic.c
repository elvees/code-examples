// Copyright 2023-2025 RnD Center "ELVEES", JSC
// SPDX-License-Identifier: MIT

// *******************************************************************
//                  Risc-Dsp runtime library
//
// This file implements interface to SpaceWire
//
// *******************************************************************
#include "swic.h"

#include <string.h>  // для memset

#include "dma_port.h"
#include "erlcommon.h"
#include "mct06.h"
#include "swic_v06.h"
#include "system.h"
// DMA_SWIC_WN_VALUE должен быть равен нулю.
// DMA SWIC v3, DMA SWIC v5 обладает особенностью:
// DMA ожидает заполнения DMA_FIFO, если в число слов в FIFO меньше, чем WN.
// При WN не равным нулю возможно возникновение ситуации простоя DMA: дескриптор
// пакета сформирован, DMA канала не занято, но данные не  передаются, поскольку
// количество готовых слов меньше значения WN.
#define DMA_SWIC_WN_VALUE (0x0 << 2)

// Variable for procedure of reset SW device
static unsigned int tx_data_NULL[2 + 4]
    __attribute__((aligned(8), section(".data")));
static unsigned int rx_data_NULL[2 + 4]
    __attribute__((aligned(8), section(".data")));
static unsigned int tx_data_chain_NULL[2 + 4]
    __attribute__((aligned(8), section(".data")));
static unsigned int rx_data_chain_NULL[2 + 4]
    __attribute__((aligned(8), section(".data")));
static unsigned int tx_desc_NULL[2 + 4]
    __attribute__((aligned(8), section(".data")));
static unsigned int rx_desc_NULL[2 + 4]
    __attribute__((aligned(8), section(".data")));
static unsigned int tx_desc_chain_NULL[2 + 4]
    __attribute__((aligned(8), section(".data")));
static unsigned int rx_desc_chain_NULL[2 + 4]
    __attribute__((aligned(8), section(".data")));

UINT_32 RES = 0;

static swic_block_t __swic_block[] = {
#ifdef SWIC_BASE(0)
    {.swic_regs = (swic_regs_t *)SWIC_BASE(0),
     .dma_swic_rx_des = (SPIKE_DMA_CHANNEL *)SWIC0_DMA_RX_DES_BASE,
     .dma_swic_rx_dat = (SPIKE_DMA_CHANNEL *)SWIC0_DMA_RX_DAT_BASE,
     .dma_swic_tx_des = (SPIKE_DMA_CHANNEL *)SWIC0_DMA_TX_DES_BASE,
     .dma_swic_tx_dat = (SPIKE_DMA_CHANNEL *)SWIC0_DMA_TX_DAT_BASE,
     .dma_word_size = DMA_WORD_SIZE},
#endif
#ifdef SWIC_BASE(1)
    {.swic_regs = (swic_regs_t *)SWIC_BASE(1),
     .dma_swic_rx_des = (SPIKE_DMA_CHANNEL *)SWIC1_DMA_RX_DES_BASE,
     .dma_swic_rx_dat = (SPIKE_DMA_CHANNEL *)SWIC1_DMA_RX_DAT_BASE,
     .dma_swic_tx_des = (SPIKE_DMA_CHANNEL *)SWIC1_DMA_TX_DES_BASE,
     .dma_swic_tx_dat = (SPIKE_DMA_CHANNEL *)SWIC1_DMA_TX_DAT_BASE,
     .dma_word_size = DMA_WORD_SIZE},
#endif
#ifdef SWIC_BASE(2)
    {.swic_regs = (swic_regs_t *)SWIC_BASE(2),
     .dma_swic_rx_des = (SPIKE_DMA_CHANNEL *)SWIC2_DMA_RX_DES_BASE,
     .dma_swic_rx_dat = (SPIKE_DMA_CHANNEL *)SWIC2_DMA_RX_DAT_BASE,
     .dma_swic_tx_des = (SPIKE_DMA_CHANNEL *)SWIC2_DMA_TX_DES_BASE,
     .dma_swic_tx_dat = (SPIKE_DMA_CHANNEL *)SWIC2_DMA_TX_DAT_BASE,
     .dma_word_size = DMA_WORD_SIZE},
#endif
#ifdef SWIC_BASE(3)
    {.swic_regs = (swic_regs_t *)SWIC_BASE(3),
     .dma_swic_rx_des = (SPIKE_DMA_CHANNEL *)SWIC3_DMA_RX_DES_BASE,
     .dma_swic_rx_dat = (SPIKE_DMA_CHANNEL *)SWIC3_DMA_RX_DAT_BASE,
     .dma_swic_tx_des = (SPIKE_DMA_CHANNEL *)SWIC3_DMA_TX_DES_BASE,
     .dma_swic_tx_dat = (SPIKE_DMA_CHANNEL *)SWIC3_DMA_TX_DAT_BASE,
     .dma_word_size = DMA_WORD_SIZE},
#endif
};

// Function: swic_reset_tx_desc_2
//
// Resets port.
// The function may be applied to SWIC MC-24R, MC-0428
//
// Parameters:
//      index_port - port number:
//                      0 - 1-st port
//                      1 - 2-nd port
//

static unsigned int swic_reset_tx_desc_2(int index_port);

swic_regs_t *swic_get_regs(int swic_id) {
  return __swic_block[swic_id].swic_regs;
}

swic_block_t swic_get_dev(int swic_id) { return __swic_block[swic_id]; }

void swic_apply_mport_base(unsigned int base_address) {
  int i = 0;
  for (i = 0; i < sizeof(__swic_block) / sizeof(swic_block_t); i += 1) {
    __swic_block[i].swic_regs =
        (swic_regs_t *)(base_address | (unsigned int)__swic_block[i].swic_regs);
    __swic_block[i].dma_swic_rx_des =
        (SPIKE_DMA_CHANNEL *)(base_address |
                              (unsigned int)__swic_block[i].dma_swic_rx_des);
    __swic_block[i].dma_swic_rx_dat =
        (SPIKE_DMA_CHANNEL *)(base_address |
                              (unsigned int)__swic_block[i].dma_swic_rx_dat);
    __swic_block[i].dma_swic_tx_des =
        (SPIKE_DMA_CHANNEL *)(base_address |
                              (unsigned int)__swic_block[i].dma_swic_tx_des);
    __swic_block[i].dma_swic_tx_dat =
        (SPIKE_DMA_CHANNEL *)(base_address |
                              (unsigned int)__swic_block[i].dma_swic_tx_dat);
  }
}
// Clear registers of packet statistic
void swic_clear_cnt_rxx_pack(unsigned int index_port) {
  swic_regs_t *swic_regs = swic_get_regs(index_port);

  swic_regs->cnt_rx_pack._val = 0;
  swic_regs->cnt_rx0_pack._val = 0;
}

// Procedure for configure timing for state mashine
void swic_set_timing(unsigned int index_port) {
  unsigned int t, s;
  swic_regs_t *swic_regs = swic_get_regs(index_port);

  swic_regs->mode_cr._val |= 1 << 14;
  t = swic_regs->tx_speed._val;
  t &= 0xFF0FFFFF;
  s = get_cpu_clock() / (10 * 1000000);
  t |= s << 20;
  swic_regs->tx_speed._val = t;
  swic_regs->mode_cr._val &= ~(1 << 14);
}

void swic_clear(unsigned int index_port) {
  swic_block_t swic_dev = swic_get_dev(index_port);

  swic_dev.swic_regs->mode_cr._val = 0x01;
  swic_dev.swic_regs->tx_speed._val = 0x000;
  swic_dev.swic_regs->status._val = 0xFFFFFFFF;
  swic_clear_cnt_rxx_pack(index_port);

  swic_dev.dma_swic_tx_dat->SPIKE_RUN._val = 0;
  swic_dev.dma_swic_tx_des->SPIKE_RUN._val = 0;
  swic_dev.dma_swic_rx_dat->SPIKE_RUN._val = 0;
  swic_dev.dma_swic_rx_des->SPIKE_RUN._val = 0;
}

void swic_init(unsigned int index_port) {
  swic_regs_t *swic_regs = swic_get_regs(index_port);

  swic_regs->tx_speed._val = 0x302;
  // swic_regs->mode_cr._val = (swic_regs->mode_cr._val&~1) | 0x06 | 0x001C0000;
  swic_regs->mode_cr._val = 0x06 | 0x001C0000;
  swic_regs->status._val = 0xFFFFFFFF;
}

void swic_interrupt_set(unsigned int index_port, unsigned int interrupts) {
  // TODO
  swic_regs_t *swic_regs = swic_get_regs(index_port);
  swic_regs->mode_cr._val |= ((interrupts & 0x7) << 18);
}

void swic_interrupt_unset(unsigned int index_port, unsigned int interrupts) {
  // TODO
  swic_regs_t *swic_regs = swic_get_regs(index_port);
  swic_regs->mode_cr._val =
      swic_regs->mode_cr._val & ~((interrupts & 0x7) << 18);
}

void swic_init_static_mode(unsigned int index_port) {
  swic_regs_t *swic_regs = swic_get_regs(index_port);
  swic_regs->tx_speed._val = 0x300;
  swic_regs->mode_cr._val = 0xe0000001;
}

void swic_init_loop(unsigned int index_port) {
  swic_regs_t *swic_regs = swic_get_regs(index_port);

  swic_regs->tx_speed._val = 0x302;
  swic_regs->mode_cr._val = 0x06 | 1 << 12;
}

int swic_is_connected(unsigned int index_port) {
  swic_regs_t *swic_regs = swic_get_regs(index_port);

  swic_regs->status._val = 0xffffffff;

  if ((swic_regs->status._val & 0x20A0) == 0x20A0) {
    return 1;
  } else {
    return 0;
  }
}

void swic_set_tx_speed(unsigned int index_port, int speed) {
  swic_regs_t *swic_regs = swic_get_regs(index_port);

  if (speed < 0) return;
  unsigned int tx_speed = 0;

  // TODO
  tx_speed = speed / ((unsigned)(XTI / MHz));
  //
  TX_SPEED reg_txs;
  reg_txs._val = swic_regs->tx_speed._val;
  reg_txs.tx_speed = tx_speed;
  swic_regs->tx_speed._val = reg_txs._val;
}

enum ERL_ERROR swic_send_packet(void *src, void *descr, int size, int type) {
  swic_block_t swic_dev = swic_get_dev(1);

  if (size <= 0) return ERL_PROGRAM_ERROR;

  unsigned int wsize = 0;
  memset(descr, 0, swic_dev.dma_word_size / 8);
  if (swic_dev.dma_word_size == 64) {
    wsize = size >> 3;
    wsize = (size & 0x7) ? wsize : (wsize - 1);
  } else {
    wsize = size >> 2;
    wsize = (size & 0x3) ? wsize : (wsize - 1);
  }
  if (wsize > 0xffff) return ERL_PROGRAM_ERROR;

  swic_create_desc(descr, size, type);

  // Prepare SWIC DMA channels
  RES = sys_kernel_va_to_pa((unsigned)descr);
  *((volatile int *)(SWIC1_DMA_TX_DES_BASE + 8)) = RES;
  // swic_dev.dma_swic_tx_des -> SPIKE_IR._val  =
  // sys_kernel_va_to_pa((unsigned)descr);
  RES = 0;
  *((volatile int *)(SWIC1_DMA_TX_DES_BASE)) = RES;
  // swic_dev.dma_swic_tx_des -> SPIKE_CSR._val = 0;

  RES = sys_kernel_va_to_pa((unsigned)src);
  *((volatile int *)(SWIC1_DMA_TX_DAT_BASE + 8)) = RES;
  // swic_dev.dma_swic_tx_dat -> SPIKE_IR._val =
  // sys_kernel_va_to_pa((unsigned)src);
  RES = ((wsize << 16) | DMA_SWIC_WN_VALUE);
  *((volatile int *)(SWIC1_DMA_TX_DAT_BASE)) = RES;
  // swic_dev.dma_swic_tx_dat -> SPIKE_CSR._val = ((wsize << 16) |
  // DMA_SWIC_WN_VALUE );

  // Run transfer
  RES = 1;
  *((volatile int *)(SWIC1_DMA_TX_DES_BASE + 0xC)) = RES;
  *((volatile int *)(SWIC1_DMA_TX_DAT_BASE + 0xC)) = RES;
  // swic_dev.dma_swic_tx_des -> SPIKE_RUN._val = 1;
  // swic_dev.dma_swic_tx_dat -> SPIKE_RUN._val = 1;
  return ERL_NO_ERROR;
}

enum ERL_ERROR swic_prepare_send_packet(unsigned int index_port, void *src,
                                        void *descr, int size, int type) {
  swic_block_t swic_dev = swic_get_dev(index_port);

  if (size <= 0) return ERL_NO_ERROR;
  swic_create_desc(descr, size, type);

  unsigned int wsize = 0;
  if (swic_dev.dma_word_size == 64) {
    wsize = size >> 3;
    wsize = (size & 0x7) ? wsize : (wsize - 1);
  } else {
    wsize = size >> 2;
    wsize = (size & 0x3) ? wsize : (wsize - 1);
  }

  // Prepare SWIC DMA channels
  swic_dev.dma_swic_tx_des->SPIKE_IR._val =
      sys_kernel_va_to_pa((unsigned)descr);
  swic_dev.dma_swic_tx_des->SPIKE_CSR._val = 0;

  swic_dev.dma_swic_tx_dat->SPIKE_IR._val = sys_kernel_va_to_pa((unsigned)src);
  swic_dev.dma_swic_tx_dat->SPIKE_CSR._val =
      ((wsize << 16) | DMA_SWIC_WN_VALUE);

  return ERL_NO_ERROR;
}

enum ERL_ERROR swic_dma_prepare_send(unsigned int index_port, void *src,
                                     void *desc, unsigned int wsize) {
  swic_block_t swic_dev = swic_get_dev(index_port);

  // Prepare SWIC DMA channels
  swic_dev.dma_swic_tx_des->SPIKE_IR._val = sys_kernel_va_to_pa((unsigned)desc);
  swic_dev.dma_swic_tx_des->SPIKE_CSR._val = 0;

  swic_dev.dma_swic_tx_dat->SPIKE_IR._val = sys_kernel_va_to_pa((unsigned)src);
  swic_dev.dma_swic_tx_dat->SPIKE_CSR._val =
      ((wsize << 16) | DMA_SWIC_WN_VALUE);

  return ERL_NO_ERROR;
}

enum ERL_ERROR swic_run_send_packet(unsigned int index_port) {
  swic_block_t swic_dev = swic_get_dev(index_port);

  swic_dev.dma_swic_tx_des->SPIKE_RUN._val = 1;
  swic_dev.dma_swic_tx_dat->SPIKE_RUN._val = 1;
  return ERL_NO_ERROR;
}

unsigned short swic_test_send_packet(unsigned int index_port) {
  swic_block_t swic_dev = swic_get_dev(index_port);

  if (swic_dev.dma_swic_tx_des->SPIKE_RUN.run)
    return 0;
  else
    return 1;
}

enum ERL_ERROR swic_receiver_packet_wait(void) {
  swic_block_t swic_dev = swic_get_dev(0);
  // waiting for receiving descriptor
  while (1) {
    RES = *((volatile int *)(SWIC0_DMA_RX_DES_BASE + 0xC));
    if ((RES & 0x1) == 0) {
      // read cp to reset run state
      RES = swic_dev.dma_swic_rx_des->SPIKE_CP._val;
      break;
    }
  }
  return ERL_NO_ERROR;
}

enum ERL_ERROR swic_receiver_packet_run(void *dst, unsigned int *descr,
                                        unsigned int size) {
  swic_block_t swic_dev = swic_get_dev(0);

  unsigned int wsize = 0;
  memset(descr, 0, swic_dev.dma_word_size / 8);

  if (swic_dev.dma_word_size == 64) {
    wsize = size >> 3;
    wsize = (size & 0x7) ? wsize : (wsize - 1);
  } else {
    wsize = size >> 2;
    wsize = (size & 0x3) ? wsize : (wsize - 1);
  }

  RES = sys_kernel_va_to_pa((unsigned)dst);
  *((volatile int *)(SWIC0_DMA_RX_DAT_BASE + 0x8)) = RES;
  // swic_dev.dma_swic_rx_dat -> SPIKE_IR._val = RES;

  RES = ((wsize << 16) | DMA_SWIC_WN_VALUE);
  *((volatile int *)(SWIC0_DMA_RX_DAT_BASE)) = RES;
  // swic_dev.dma_swic_rx_dat -> SPIKE_CSR._val = ((wsize<<16)|
  // DMA_SWIC_WN_VALUE );

  RES = sys_kernel_va_to_pa((unsigned)descr);
  *((volatile int *)(SWIC0_DMA_RX_DES_BASE + 8)) = RES;
  // swic_dev.dma_swic_rx_des -> SPIKE_IR._val =
  // sys_kernel_va_to_pa((unsigned)descr);
  RES = 0;
  *((volatile int *)(SWIC0_DMA_RX_DES_BASE)) = RES;
  // swic_dev.dma_swic_rx_des -> SPIKE_CSR._val = 0x0;

  RES = 1;
  *((volatile int *)(SWIC0_DMA_RX_DES_BASE + 0xC)) = RES;
  *((volatile int *)(SWIC0_DMA_RX_DAT_BASE + 0xC)) = RES;
  // swic_dev.dma_swic_rx_des -> SPIKE_RUN.run = 1;
  // swic_dev.dma_swic_rx_dat -> SPIKE_RUN.run = 1;
  return ERL_NO_ERROR;
}

enum ERL_ERROR swic_prepare_receiver_packet(unsigned int index_port, void *dst,
                                            unsigned int *descr,
                                            unsigned int word_length) {
  swic_block_t swic_dev = swic_get_dev(index_port);

  memset(descr, 0, swic_dev.dma_word_size / 8);

  if ((word_length == 0) || (word_length > 0x10000)) return ERL_PROGRAM_ERROR;

  swic_dev.dma_swic_rx_dat->SPIKE_IR._val = sys_kernel_va_to_pa((unsigned)dst);
  swic_dev.dma_swic_rx_dat->SPIKE_CSR._val =
      (((word_length - 1) & 0xffff) << 16) | ((0 & 0xF) << 2);
  swic_dev.dma_swic_rx_des->SPIKE_IR._val =
      sys_kernel_va_to_pa((unsigned)descr);
  return ERL_NO_ERROR;
}

enum ERL_ERROR swic_run_prepare_receive_packet(unsigned int index_port) {
  swic_block_t swic_dev = swic_get_dev(index_port);

  swic_dev.dma_swic_rx_des->SPIKE_CSR._val = 1;
  swic_dev.dma_swic_rx_dat->SPIKE_RUN.run = 1;
  return ERL_NO_ERROR;
}

void swic_dma_stop_channels(unsigned int index_port) {
  swic_block_t swic_dev = swic_get_dev(index_port);

  swic_dev.dma_swic_rx_des->SPIKE_RUN._val = 0;
  swic_dev.dma_swic_rx_dat->SPIKE_RUN._val = 0;
  swic_dev.dma_swic_tx_des->SPIKE_RUN._val = 0;
  swic_dev.dma_swic_tx_dat->SPIKE_RUN._val = 0;

#ifndef TARGET_MCB02  // todo
  swic_dev.swic_regs->mode_cr.SWCORE_RST = 1;

  while (swic_dev.dma_swic_rx_des->SPIKE_RUN.run);
  while (swic_dev.dma_swic_tx_des->SPIKE_RUN.run);
  while (swic_dev.dma_swic_rx_dat->SPIKE_RUN.run);
  while (swic_dev.dma_swic_tx_dat->SPIKE_RUN.run);

  swic_dev.swic_regs->mode_cr.SWCORE_RST = 0;
#endif
}

int swic_dma_start_chain(unsigned int *pointer, unsigned int index_port,
                         unsigned int channel_index) {
  swic_block_t swic_dev = swic_get_dev(index_port);

  switch (channel_index) {
    case 0:
      DMA_Port_Load_Chain(swic_dev.dma_swic_rx_des, (DMA_Port_Chain *)pointer);
      break;
    case 1:
      DMA_Port_Load_Chain(swic_dev.dma_swic_rx_dat, (DMA_Port_Chain *)pointer);
      break;
    case 2:
      DMA_Port_Load_Chain(swic_dev.dma_swic_tx_des, (DMA_Port_Chain *)pointer);
      break;
    case 3:
      DMA_Port_Load_Chain(swic_dev.dma_swic_tx_dat, (DMA_Port_Chain *)pointer);
      break;
  }
}

void swic_create_desc(unsigned int *pointer, unsigned int size_in_byte,
                      unsigned int type_of_end_packet) {
  if (((unsigned int)pointer & (__swic_block[0].dma_word_size / 8 - 1)) == 0) {
    memset(pointer, 0, __swic_block[0].dma_word_size / 8);
    pointer[0] = 0x80000000 | (size_in_byte & 0x01FFFFFF) |
                 ((type_of_end_packet & 0x3) << 29);
  }
}

#if (defined(TARGET_MC0428) || defined(TARGET_MC24R))
/*
Функция swic_reset_tx_desc_2(int index_port) Предназначается для сброса
устройства SW (SWIC, DMA, Router*,INT) Используется из swic_clear.

1. Остановить SWIC и убрать прерывания. Link_disable + маскирование всех
прерываний
2. Остановить пользовательские DMA. RDY_Mode.
3. Зарядить цепочки: чтение/запись 1 слова данных, чтение 1 дескриптора.
4. Установить соединение через петлю обратной связи.
5. Ожидать признака завершения передачи/приема данных(метод чтения CSR)
6. В этот момент очередь данных заполнена полностью (без одного слова ведь
наблюдали, что он передает сразу парами - уточнить)
7. Остановить DMA передачи данных, DMA дескрипторов . RDY_Mode.
8. Подготовить прием одного дескриптора.
9. Передать один дескриптор с размером пакета размером в буфер.
10. Ожидать приема 1 дескриптора
11. Проверить его размер.
12. Остановить все DMA. RDY_Mode.
13. Остановить swic и отключить петлю обратной связи.
*/
static unsigned int swic_reset_tx_desc_2(int index_port) {
  swic_block_t swic_dev = swic_get_dev(index_port);

  unsigned int result = 0;
  unsigned int control_bits_last;
#if (defined(TARGET_MC0428))
  const int sw_reset_buffer_length_byte = (12 * 8);
#elif (defined(TARGET_MC24R))
  const int sw_reset_buffer_length_byte = (10 * 8);
#endif

  // 1. Функция всегда вызывается из swic_clear

  // 2. Остановить пользовательские DMA. RDY_Mode.
  swic_dma_stop_channels(index_port);

  // 3. Зарядить цепочки: чтение/запись 1 слова данных, чтение 1 дескриптора.
  control_bits_last = 0 + (1 << 12)  // CHEN
                      + (1 << 13)    // IM
                      + (1 << 0)     // RUN
      ;
  // Цепочка передачи данных
  DMA_Port_Change_Chain_IR_CSR_CP(
      tx_data_chain_NULL, sys_kernel_va_to_pa((unsigned int)tx_data_NULL),
      control_bits_last, sys_kernel_va_to_pa((unsigned int)tx_data_chain_NULL));
  // Цепочка приема данных
  DMA_Port_Change_Chain_IR_CSR_CP(
      rx_data_chain_NULL, sys_kernel_va_to_pa((unsigned int)rx_data_NULL),
      control_bits_last, sys_kernel_va_to_pa((unsigned int)rx_data_chain_NULL));
  // Цепочка приема дескрипторов
  DMA_Port_Change_Chain_IR_CSR_CP(
      rx_desc_chain_NULL, sys_kernel_va_to_pa((unsigned int)rx_desc_NULL),
      control_bits_last, sys_kernel_va_to_pa((unsigned int)rx_desc_chain_NULL));
  swic_clear_cnt_rxx_pack(index_port);  // рекомендация документации
  // Запускаем цепочки
  swic_dma_start_chain(rx_desc_chain_NULL, index_port, 0);  // прием дескриптора
  swic_dma_start_chain(rx_data_chain_NULL, index_port,
                       1);  // прием данных
                            // передача дескриптора не нужна!
  swic_dma_start_chain(tx_data_chain_NULL, index_port, 3);  // передача данных

  // 4. Установить соединение через петлю обратной связи.
  swic_init_loop(index_port);

  // 5. Ожидать признака завершения передачи/приема данных(метод чтения CSR)
  unsigned int c;
  c = 0;
  while (c < 100) {
    // EA_WATCH_DOG_RESET;
    if (
        // При считывании сбрасывается в 0, но если снова равен 1 - передача
        // данных идет
        (swic_dev.dma_swic_rx_dat->csr._val & (1 << 14)) ||
        (swic_dev.dma_swic_rx_des->csr._val & (1 << 14)) ||
        (swic_dev.dma_swic_tx_dat->csr._val & (1 << 14)))
      c = 0;
    c++;
  }

  // 6. В этот момент очередь данных заполнена полностью на (8+2) 64-х слов
  // В п.5 считается, что очищена возможная очередь дескрипторов
  // путем постоянного приема данных+дескрипторов и постоянной подкачки данных.

  // 7. Остановить DMA передачи данных, DMA дескрипторов . RDY_Mode.
  swic_dma_stop_channels(index_port);

  // 8. Подготовить прием одного дескриптора.
  swic_dev.dma_swic_rx_des->ir._val =
      sys_kernel_va_to_pa((unsigned)rx_desc_NULL);
  swic_dev.dma_swic_rx_des->csr._val = 1;

  // 9. Передать один дескриптор с размером пакета равному числу данных в буфере
  // TX 10*8 байт см. п.6.
  //	Этот буфер заполнился при прочистке буфера дескрипторов.
  swic_create_desc(tx_desc_NULL, sw_reset_buffer_length_byte,
                   SWIC_END_PACKET_EOP);
  swic_clear_cnt_rxx_pack(index_port);
  swic_dev.dma_swic_tx_des->ir._val =
      sys_kernel_va_to_pa((unsigned)tx_desc_NULL);
  swic_dev.dma_swic_tx_des->csr._val = 1;

  // 10. Ожидать приема 1 дескриптора
  while (swic_dev.dma_swic_rx_des->run.run);

  // 11. Проверить его размер.
  if ((rx_desc_NULL[0] & 0x00FFFFFF) != sw_reset_buffer_length_byte)
    result = 1;  // вернуть ошибку сброса либо провести дрополнительные действия

  // 12. Остановить все DMA. RDY_Mode.  Этим уничтожатся принятые данные при
  // прочистке.
  swic_dma_stop_channels(index_port);

  // 13. Остановить swic и отключить петлю обратной связи.
  swic_dev.swic_regs->mode_cr._val = 0x01;
  swic_dev.swic_regs->tx_speed._val = 0x000;
  swic_dev.swic_regs->status._val = 0xFFFFFFFF;
  swic_clear_cnt_rxx_pack(index_port);

  return result;
}
#endif

int swic_get_status(int index_port) {
  swic_regs_t *swic_regs = swic_get_regs(index_port);

  return swic_regs->status._val;
}

#ifdef TARGET_MCB02
#undef sys_kernel_va_to_pa
#endif  // TARGET_MCB02
// #endif //
