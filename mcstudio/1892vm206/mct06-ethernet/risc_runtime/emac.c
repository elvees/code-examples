// Copyright 2023-2025 RnD Center "ELVEES", JSC
// SPDX-License-Identifier: MIT

#include "emac.h"

#include "mct06.h"

int phy_read_reg(int ch, int reg) {
  EMAC_MD_CONTROL(ch) =
      (PHY_ADDR << 24) | (1 << 29) | (reg << 16) | (0b01U << 30);

  while (!(EMAC_MD_STATUS(ch) && (1 << 29)));

  delay(1000);

  return EMAC_MD_STATUS(ch) & 0xFFFF;
}

int phy_write_reg(int ch, int reg, int value) {
  int tmout = 0;

  EMAC_MD_CONTROL(ch) =
      (PHY_ADDR << 24) | (reg << 16) | (1 << 29) | (0b10U << 30) | (value << 0);

  while (!(EMAC_MD_STATUS(ch) && (1 << 29))) {
    if (tmout > 10000) return 1;
    tmout++;
  }

  return 0;
}

// Функция инициализации порта EMAC
void emac_init(int ch, char* u_mac) {
  // Включение контроллера, бит EN_MAC
  EMAC_MAC_CSR(ch) |= (1 << EN_MAC);

  EMAC_LEN_BORDER_RX(ch) = MAX_FRAME_LEN;

  // Включение дуплексного режима, выдача разрешения на прием/передачу
  EMAC_MAC_CSR(ch) |= (1 << FULLD) | (1 << EN_RX) | (1 << EN_TX);

  EMAC_UC_ADDR1(ch) = (u_mac[4] & 0xFF) | (u_mac[5] & 0xFF) << 8;
  EMAC_UC_ADDR2(ch) = (u_mac[0] & 0xFF) | (u_mac[1] & 0xFF) << 8 |
                      (u_mac[2] & 0xFF) << 16 | (u_mac[3] & 0xFF) << 24;

  EMAC_RX_CTR(ch) =
      (1 << PAS_BAD_FRAME) | (1 << UC_EN) | (1 << MC_EN) | (1 << BC_EN);
}

void prepare_tx_port(int ch, char* da_mac, unsigned int* desc,
                     unsigned char* array, int len) {
  desc[0] = len;
  desc[1] = (1 << 4) | (1 << 5);

  EMAC_SRC_ADDR1(ch) =
      (EMAC_UC_ADDR1(ch) << 8) | ((EMAC_UC_ADDR2(ch) >> 24) & 0xFF);
  EMAC_SRC_ADDR2(ch) = EMAC_UC_ADDR2(ch);

  EMAC_DST_ADDR1(ch) = (da_mac[4] & 0xFF) | (da_mac[5] & 0xFF) << 8;
  EMAC_DST_ADDR2(ch) = (da_mac[0] & 0xFF) | (da_mac[1] & 0xFF) << 8 |
                       (da_mac[2] & 0xFF) << 16 | (da_mac[3] & 0xFF) << 24;

  EMAC_TYPE(ch) = 0x88B6;

  EMAC_TX_DES_IR(ch) = virt_to_phys((unsigned int)desc);
  EMAC_TX_DAT_IR(ch) = virt_to_phys((unsigned int)array);

  EMAC_TX_DES_CSR(ch) = (0 << 2) | (0x0 << 16) | (1 << 13);
  EMAC_TX_DAT_CSR(ch) = (0 << 2) | ((len - 1) << 16) | (1 << 13);
}

void prepare_tx_dma(int ch, unsigned int* desc, mac_frame* array, int len) {
  desc[0] = len;

  EMAC_TX_DES_IR(ch) = virt_to_phys((unsigned int)desc);
  EMAC_TX_DAT_IR(ch) = virt_to_phys((unsigned int)array);

  EMAC_TX_DES_CSR(ch) = (0 << 2) | (0x0 << 16) | (1 << 13);
  EMAC_TX_DAT_CSR(ch) = (0 << 2) | ((len - 1) << 16) | (1 << 13);
}

void prepare_rx_dma(int ch, unsigned int* desc, unsigned char* array, int len) {
  EMAC_RX_DES_IR(ch) = virt_to_phys((unsigned int)desc);
  EMAC_RX_DAT_IR(ch) = virt_to_phys((unsigned int)array);

  EMAC_RX_DES_CSR(ch) = (0 << 2) | (0x0 << 16);
  EMAC_RX_DAT_CSR(ch) = (0 << 2) | ((len - 1) << 16);
}
