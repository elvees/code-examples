// Copyright 2023-2025 RnD Center "ELVEES", JSC
// SPDX-License-Identifier: MIT
#include "gspw.h"

#include "mct06.h"

uint32_t GetCoeffSpd(uint32_t speed) {
  if (speed > 120) switch (speed) {
      case 125:
        return 25;
      case 312:
        return 48;
      case 625:
        return 64;
      case 1250:
        return 96;
      default:
        return 96;
    }
  return speed / 5;
}

uint32_t GetCommaCoeff(uint32_t speed) {
  if (speed < 312)
    return 1;
  else
    return 8;
}

void Open(uint32_t ch, uint32_t speed, int mode) {
  uint32_t rx_speed_k = GetCoeffSpd(speed);
  uint32_t tx_speed_k = GetCoeffSpd(speed);
  uint32_t comma = GetCommaCoeff(speed);
  uint32_t k10 = speed / 10;

  // Установка режима порта GSpW:
  SPFMIC_MODE_R(ch) |= (1 << PORT_REGIME_OFFSET) | (1 << DMA_ENABLED_OFFSET);

  // Сброс PMA:
  SPFMIC_PMA_MODE(ch) = 0;

  // Cброс BDS:
  SPFMIC_GIGA_SPW_MODE(ch) |= (1 << BDS_RESET_OFFSET);

  // Cброс параметров установки соединения (повторно):
  SPFMIC_GIGA_SPW_MODE(ch) &=
      ~((1 << LINKDISABLED_OFFSET) | (1 << AUTOSTART_OFFSET) |
        (1 << LINKSTART_OFFSET) | (1 << BDS_RESET_OFFSET));
  SPFMIC_GIGA_SPW_MODE(ch) |= (1 << LINKDISABLED_OFFSET);

  // Установка значения comma и disconnect_counter:
  SPFMIC_GIGA_SPW_TRANSMISSION_PARAMETERS(ch) &=
      ~(KOEFF_COMMA_MASK << KOEFF_COMMA_OFFSET) |
      (DISCONNECT_COUNTER_MASK << DISCONNECT_COUNTER_OFFSET);
  SPFMIC_GIGA_SPW_TRANSMISSION_PARAMETERS(ch) |=
      (comma & KOEFF_COMMA_MASK) << KOEFF_COMMA_OFFSET |
      (0xF & DISCONNECT_COUNTER_MASK) << DISCONNECT_COUNTER_OFFSET;

  // Установка PMA_MODE на низкой скорости
  SPFMIC_PMA_MODE(ch) = ((1 & PMA_RX_SPEED_MASK) << PMA_RX_SPEED_OFFSET) |
                        ((3 & ALIGN_MODE_MASK) << ALIGN_MODE_OFFSET) |
                        (1 << EN_PMA_RX_OFFSET) |
                        ((1 & PMA_TX_SPEED_MASK) << PMA_TX_SPEED_OFFSET) |
                        (1 << EN_PMA_TX_OFFSET) | (1 << PWDn_TX_OFFSET);
  Sleep(155);

  // Повышение скорости PMA
  SPFMIC_PMA_MODE(ch) |=
      ((rx_speed_k & PMA_RX_SPEED_MASK) << PMA_RX_SPEED_OFFSET) |
      ((tx_speed_k & PMA_TX_SPEED_MASK) << PMA_TX_SPEED_OFFSET);

  // Установка AUTOSTART/LINKSTART и koeff_10_local
  if (mode == AUTOSTART)
    SPFMIC_GIGA_SPW_MODE(ch) =
        (1 << AUTOSTART_OFFSET) |
        ((k10 & KOEFF_10_LOCAL_MASK) << KOEFF_10_LOCAL_OFFSET);
  else if (mode == LINKSTART)
    SPFMIC_GIGA_SPW_MODE(ch) =
        (1 << LINKSTART_OFFSET) |
        ((k10 & KOEFF_10_LOCAL_MASK) << KOEFF_10_LOCAL_OFFSET);
  Sleep(155);

  // Включение приемника PMA
  SPFMIC_PMA_MODE(ch) |= (1 << PWDn_RX_OFFSET) | (1 << COMMA_EN_OFFSET) |
                         (1 << COMPARE_EN_OFFSET) |
                         ((1 & ALIGN_MODE_MASK) << ALIGN_MODE_OFFSET) |
                         ((3 & CDR_MODE_MASK) << CDR_MODE_OFFSET);
  Sleep(155);
  SleepMs(1);

  // Обнуление GIGA_SPW_STATUS
  SPFMIC_GIGA_SPW_STATUS(ch) = 0xffffffff;
}

uint32_t IsConnected(uint32_t ch) {
  int tOut = 10000;

  while (tOut) {
    if ((SPFMIC_STATE_R(ch)) & (1 << PORT_CONNECTED_OFFSET))
      SPFMIC_STATE_R(ch) |= (1 << PORT_CONNECTED_OFFSET);
    if ((SPFMIC_STATE_R(ch)) & (1 << PORT_ERRORED_OFFSET))
      SPFMIC_STATE_R(ch) |= (1 << PORT_ERRORED_OFFSET);
    if ((SPFMIC_STATE_R(ch)) & (1 << PORT_CONNECT_OFFSET)) return 1;
    if ((SPFMIC_STATE_R(ch)) & (1 << PORT_ERROR_OFFSET)) return 0;

    tOut--;
  }

  return 0;
}

void Close(uint32_t ch) {
  SPFMIC_GIGA_SPW_MODE(ch) &=
      ~((1 << LINKDISABLED_OFFSET) | (1 << AUTOSTART_OFFSET) |
        (1 << LINKSTART_OFFSET) | (1 << BDS_RESET_OFFSET));
  SPFMIC_GIGA_SPW_MODE(ch) |= (1 << LINKDISABLED_OFFSET);

  SPFMIC_STATE_R(ch) |=
      (1 << PORT_CONNECTED_OFFSET) | (1 << PORT_ERRORED_OFFSET);

  SPFMIC_PMA_MODE(ch) &= ~((1 << EN_PMA_RX_OFFSET) | (1 << EN_PMA_TX_OFFSET) |
                           (1 << PWDn_TX_OFFSET) | (1 << PWDn_RX_OFFSET) |
                           ((0x7F & PMA_RX_SPEED_MASK) << PMA_RX_SPEED_OFFSET) |
                           ((0x7F & PMA_TX_SPEED_MASK) << PMA_TX_SPEED_OFFSET) |
                           (1 << LB_EN_RX_OFFSET) | (1 << LB_EN_TX_OFFSET) |
                           (1 << COMMA_EN_OFFSET) | (1 << COMPARE_EN_OFFSET));

  Sleep(155);
  SleepMs(1);

  SPFMIC_GIGA_SPW_MODE(ch) |= (1 << BDS_RESET_OFFSET);

  SPFMIC_GIGA_SPW_MODE(ch) &=
      ~((1 << LINKDISABLED_OFFSET) | (1 << AUTOSTART_OFFSET) |
        (1 << LINKSTART_OFFSET) | (1 << BDS_RESET_OFFSET));
  SPFMIC_GIGA_SPW_MODE(ch) |= (1 << LINKDISABLED_OFFSET);
}

void gswic_create_desc(unsigned int *pointer, unsigned int size_in_byte,
                       unsigned int type_of_end_packet) {
  if (((unsigned int)pointer & (64 / 8 - 1)) == 0) {
    memset(pointer, 0, 64 / 8);
    pointer[0] = 0x80000000 | (size_in_byte & 0x01FFFFFF) |
                 ((type_of_end_packet & 0x3) << 29);
  }
}

void gswic_receiver_packet_run(void *dst, void *descr, unsigned int size) {
  uint32_t RES;
  unsigned int wsize = 0;

  memset(descr, 0, 64 / 8);

  wsize = size >> 3;
  wsize = (size & 0x7) ? wsize : (wsize - 1);

  RES = sys_kernel_va_to_pa((unsigned)dst);
  *((volatile int *)(0x182F7840 + 0x8)) = RES;

  RES = ((wsize << 16) | (0x0 << 2));
  *((volatile int *)(0x182F7840)) = RES;

  RES = sys_kernel_va_to_pa((unsigned)descr);
  *((volatile int *)(0x182F7800 + 8)) = RES;

  RES = 0;
  *((volatile int *)(0x182F7800)) = RES;

  RES = 1;
  *((volatile int *)(0x182F7800 + 0xC)) = RES;
  *((volatile int *)(0x182F7840 + 0xC)) = RES;
}

void gswic_send_packet(void *src, void *descr, int size, int type) {
  uint32_t RES;
  unsigned int wsize = 0;

  wsize = size >> 3;
  wsize = (size & 0x7) ? wsize : (wsize - 1);

  memset(descr, 0, 64 / 8);

  gswic_create_desc(descr, size, type);

  RES = sys_kernel_va_to_pa((unsigned)descr);
  *((volatile int *)(0x182F8880 + 8)) = RES;

  RES = 0;
  *((volatile int *)(0x182F8880)) = RES;

  RES = sys_kernel_va_to_pa((unsigned)src);
  *((volatile int *)(0x182F88C0 + 8)) = RES;

  RES = ((wsize << 16) | (0x0 << 2));
  *((volatile int *)(0x182F88C0)) = RES;

  RES = 1;
  *((volatile int *)(0x182F8880 + 0xC)) = RES;
  *((volatile int *)(0x182F88C0 + 0xC)) = RES;
}

void gswic_receiver_packet_wait(void) {
  int RES;

  while (1) {
    RES = *((volatile int *)(0x182F7800 + 0xC));
    if ((RES & 0x1) == 0) {
      // read cp to reset run state
      RES = *((volatile int *)(0x182F7800 + 0x4));
      break;
    }
  }
}
