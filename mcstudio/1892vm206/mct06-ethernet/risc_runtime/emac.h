// Copyright 2023-2025 RnD Center "ELVEES", JSC
// SPDX-License-Identifier: MIT

#ifndef _EMAC_H_
#define _EMAC_H_

#define PHY_ADDR 000
#define EMAC0 0
#define EMAC1 1
#define MAX_FRAME_LEN 1518

// LAN8710A Registers
#define PHY_BCR 0     // Basic Control Register
#define PHY_BSR 1     // Basic Status Register
#define PHY_ID1 2     // PHY Identifier 1
#define PHY_ID2 3     // PHY Identifier 2
#define PHY_ANAR 4    // Auto-Negotiation Advertisement Register
#define PHY_ANLPAR 5  // Auto-Negotiation Link Partner Ability Register
#define PHY_ANER 6    // Auto-Negotiation Expansion Register
#define PHY_MCSR 17   // Mode Control/Status Register
#define PHY_SM 18     // Special Modes
#define PHY_SECR 26   // Symbol Error Counter Register
#define PHY_CSIR 27   // Control / Status Indication Register
#define PHY_ISR 29    // Interrupt Source Register
#define PHY_IMR 30    // Interrupt Mask Register
#define PHY_SCSR 31   // PHY Special Control/Status Register

#define PHY_SOFT_RESET_BIT 15
#define PHY_AN_EN_BIT 12

#define tx_run_des(ch) EMAC_TX_DES_RUN(ch) = 1;
#define tx_run_dat(ch) EMAC_TX_DAT_RUN(ch) = 1;
#define rx_run_des(ch) EMAC_RX_DES_RUN(ch) = 1;
#define rx_run_dat(ch) EMAC_RX_DAT_RUN(ch) = 1;

// Verify errors defines
#define BAD_MAC 1
#define WRONG_TYPE 2
#define BAD_DATA 3

// EMAC Registers bits
#define ALL_EN 9
#define BC_EN 8
#define MC_EN 7
#define UC_EN 5
#define PAS_BAD_FRAME 0

#define FULLD 5
#define EN_TX 2
#define EN_RX 1
#define EN_MAC 0

typedef struct __attribute__((__packed__)) {
  char da[6];
  char sa[6];
  unsigned short len_or_type;
  char data[1500];
} mac_frame;

int phy_read_reg(int ch, int reg);
int phy_write_reg(int ch, int reg, int value);
void emac_init(int ch, char* u_mac);
void prepare_tx_port(int ch, char* da_mac, unsigned int* desc,
                     unsigned char* array, int len);
void prepare_tx_dma(int ch, unsigned int* desc, mac_frame* array, int len);
void tx_run(int ch);
void rx_run(int ch);
void prepare_rx_port(int ch, unsigned int* desc, mac_frame* array);
void prepare_rx_dma(int ch, unsigned int* desc, unsigned char* array, int len);

#endif
