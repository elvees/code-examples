// Copyright 2023-2025 RnD Center "ELVEES", JSC
// SPDX-License-Identifier: MIT

#include <stdio.h>

#include "risc_runtime/emac.h"
#include "risc_runtime/mct06.h"
#include "risc_runtime/risc_interrupt.h"

void delay(int ticks) {
  for (int i = 0; i < ticks; i++) asm("nop");
}

unsigned int virt_to_phys(unsigned int virtaddr) {
  switch (virtaddr >> 28 & 0xE) {
    default:
      return virtaddr + 0x40000000; /* kuseg */
    case 0x8:
      return virtaddr - 0x80000000; /* kseg0 */
    case 0xA:
      return virtaddr - 0xA0000000; /* kseg1 */
    case 0xC:
      return virtaddr; /* kseg2 */
    case 0xE:
      return virtaddr; /* kseg3 */
  }
}

// Обработчик прерывания TX_INT от EMAC0
void tx_handler(void) {
  EMAC_INT_CSR(0) |= (unsigned int)(1U << 31);  // Сброс прерывания

  /* Здесь необходимо поставить точку останова */
  asm("nop");
}

// Обработчик прерывания RX_INT от EMAC1
void rx_handler(void) {
  EMAC_INT_CSR(1) |= (unsigned int)(1 << 27);  // Сброс прерывания

  /* Здесь необходимо поставить точку останова */
  asm("nop");
}

int verify_mac_frame(mac_frame* src, mac_frame* dst, int len) {
  for (int i = 0; i < 6; i++)
    if ((src->sa[i]) != (dst->sa[i])) return BAD_MAC;

  for (int i = 0; i < 6; i++)
    if ((src->da[i]) != (dst->da[i])) return BAD_MAC;

  if (src->len_or_type != dst->len_or_type) return WRONG_TYPE;

  for (int i = 0; i < len; i++) {
    if ((src->data[i]) != (dst->data[i])) return BAD_DATA;
  }

  return 0;
}

unsigned int verify_array(unsigned char* array1, unsigned char* array2,
                          unsigned int len) {
  for (int i = 0; i < len; i++) {
    if (array1[i] != array2[i]) return 1;
  }

  return 0;
}

int main(void) {
  CR_PLL = 0x9099;

  int phy_id, bsr0 = 0, bsr1, ret;
  char tx_mac[6] = {0x00, 0x50, 0xC2, 0xE1, 0xF5, 0xA5};
  char rx_mac[6] = {0x00, 0x50, 0xC2, 0xE1, 0xF5, 0xB5};

  unsigned int tx_descript_array[2] __attribute__((aligned(8)));
  unsigned int rx_descript_array[2] __attribute__((aligned(8)));
  unsigned char input_array[64] __attribute__((aligned(8)));
  unsigned char output_array[78] __attribute__((aligned(8)));

  memset(tx_descript_array, 0x00, 2 * sizeof(int));
  memset(rx_descript_array, 0x00, 2 * sizeof(int));
  memset(input_array, 0xAA, 64 * sizeof(char));
  memset(output_array, 0, 64 * sizeof(char));

  // Кадры Ethernet II, формируемые вручную
  mac_frame tx_frame __attribute__((aligned(8)));
  mac_frame rx_frame __attribute__((aligned(8)));

  // Формирование кадра
  for (int i = 0; i < 2; i++) {
    memcpy(tx_frame.sa, tx_mac, 6);
    memcpy(tx_frame.da, rx_mac, 6);
    tx_frame.len_or_type = 0xB688;
    memcpy(&(tx_frame.data), input_array, 50);
  }

  // Включение прерываний от MDI, TX_INT и RX_INT
  risc_enable_interrupts();
  risc_set_interrupts_vector(INTH_B8000180);
  risc_enable_interrupt(RISC_INT_MAC0_TX_INT, 0);
  risc_enable_interrupt(RISC_INT_MAC1_RX_INT, 0);
  risc_register_interrupt(tx_handler, RISC_INT_MAC0_TX_INT);
  risc_register_interrupt(rx_handler, RISC_INT_MAC1_RX_INT);

  // Инициализация портов EMAC
  emac_init(EMAC0, tx_mac);
  emac_init(EMAC1, rx_mac);

  // Чтение id микросхемы Ethernet PHY
  phy_id = phy_read_reg(EMAC0, 2) << 16;
  phy_id |= phy_read_reg(EMAC0, 3);

  if (phy_id != 0x7c0f1)
    asm("nop");  // Если id не соответствует микросхеме LAN8710A

  // Программный сброс PHY
  phy_write_reg(EMAC0, PHY_BCR, (1 << PHY_SOFT_RESET_BIT));
  phy_write_reg(EMAC1, PHY_BCR, (1 << PHY_SOFT_RESET_BIT));

  // Включение режима автосогласования
  phy_write_reg(EMAC0, PHY_BCR, (1 << PHY_AN_EN_BIT));
  phy_write_reg(EMAC1, PHY_BCR, (1 << PHY_AN_EN_BIT));

  // Ожидание соединения, читая регистр Basic Status Register микросхемы
  // LAN8710A
  while (!((bsr0 & (1 << 2)) && (bsr1 & (1 << 2)))) {
    bsr0 = phy_read_reg(EMAC0, PHY_BSR);
    bsr1 = phy_read_reg(EMAC1, PHY_BSR);
  }

  while (1) {
    /* Передача кадра сформированного в памяти вручную */

    // Подготовка передающего и принимающего DMA каналов
    prepare_tx_dma(EMAC0, tx_descript_array, &tx_frame, 64);
    prepare_rx_dma(EMAC1, rx_descript_array, (unsigned char*)&rx_frame, 64);

    // Запуск DMA на прием
    rx_run_des(EMAC1);
    rx_run_dat(EMAC1);

    // Запуск DMA на передачу
    tx_run_des(EMAC0);
    tx_run_dat(EMAC0);

    // Ожидание окончания работы DMA
    while (EMAC_RX_DES_RUN(EMAC1) & 0x1);

    // Проверка корректности принятого кадра
    ret = verify_mac_frame(&rx_frame, &tx_frame, 50);

    /* Здесь необходимо поставить точку останова */
    asm("nop");

    memset(tx_descript_array, 0x00, 8);
    memset(rx_descript_array, 0x00, 8);

    /* Передача кадра, формируемого контроллером */

    // Подготовка кадра, передающего и принимающего DMA каналов
    prepare_tx_port(EMAC0, rx_mac, tx_descript_array, input_array, 64);
    prepare_rx_dma(EMAC1, rx_descript_array, output_array, 78);

    // Запуск DMA на прием
    rx_run_des(EMAC1);
    rx_run_dat(EMAC1);

    // Запуск DMA на передачу
    tx_run_des(EMAC0);
    tx_run_dat(EMAC0);

    // Ожидание окончания работы DMA
    while (EMAC_RX_DES_RUN(EMAC1) & 0x1);

    // Проверка корректности принятого массива
    ret = verify_array(input_array, output_array + 14, 64);

    /* Здесь необходимо поставить точку останова */
    asm("nop");

    memset(tx_descript_array, 0x00, 8);
    memset(rx_descript_array, 0x00, 8);
  }
}
