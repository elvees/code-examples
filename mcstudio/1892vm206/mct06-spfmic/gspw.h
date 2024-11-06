// Copyright 2023-2025 RnD Center "ELVEES", JSC
// SPDX-License-Identifier: MIT

#ifndef GSPW_H_
#define GSPW_H_

#define uint32_t unsigned int
#define LINKSTART 0
#define AUTOSTART 1
#define CH0 0
#define CH1 1

//**************************GSPW*Offsets************************************//

#define PORT_REGIME_OFFSET 0  // MODE_R reg
#define DMA_ENABLED_OFFSET 10

#define PORT_CONNECTED_OFFSET 5  // STATE_R reg
#define PORT_ERRORED_OFFSET 6
#define PORT_CONNECT_OFFSET 7
#define PORT_ERROR_OFFSET 8

#define PWDn_TX_OFFSET 0  // PMA_MODE reg
#define PWDn_RX_OFFSET 1
#define COMMA_EN_OFFSET 2
#define COMPARE_EN_OFFSET 3
#define PMA_RX_SPEED_OFFSET 4
#define PMA_RX_SPEED_MASK 0x7F
#define ALIGN_MODE_OFFSET 11
#define ALIGN_MODE_MASK 0x3
#define EN_PMA_RX_OFFSET 13
#define CDR_MODE_OFFSET 14
#define CDR_MODE_MASK 0x3
#define LB_EN_RX_OFFSET 16
#define PMA_TX_SPEED_OFFSET 17
#define PMA_TX_SPEED_MASK 0x7F
#define EN_PMA_TX_OFFSET 24
#define LB_EN_TX_OFFSET 25

#define LINKDISABLED_OFFSET 0  // GIGA_SPW_MODE reg
#define AUTOSTART_OFFSET 1
#define LINKSTART_OFFSET 2
#define BDS_RESET_OFFSET 3
#define KOEFF_10_LOCAL_OFFSET 9
#define KOEFF_10_LOCAL_MASK 0x1FF

#define KOEFF_COMMA_OFFSET 0  // GIGA_SPW_TRANSMISSION_PARAMETERS reg
#define KOEFF_COMMA_MASK 0x3F
#define DISCONNECT_COUNTER_OFFSET 6
#define DISCONNECT_COUNTER_MASK 0xF

//**************************GSPW*Functions************************************//
void Open(uint32_t ch, uint32_t speed, int mode);
uint32_t GetCoeffSpd(uint32_t speed);
uint32_t GetCommaCoeff(uint32_t speed);
uint32_t IsConnected(uint32_t ch);
void Close(uint32_t ch);

//**************************GSPW*DMA*Functions*******************************//
void gswic_create_desc(unsigned int *pointer, unsigned int size_in_byte,
                       unsigned int type_of_end_packet);
void gswic_receiver_packet_run(void *dst, void *descr, unsigned int size);
void gswic_send_packet(void *src, void *descr, int size, int type);
void gswic_receiver_packet_wait(void);

#endif
