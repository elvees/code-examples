// Copyright 2023-2025 RnD Center "ELVEES", JSC
// SPDX-License-Identifier: MIT

// *******************************************************************/
//     This file contains swic register map for device version 06
//
// *******************************************************************/
#ifndef __SWIC_V05_H__
#define __SWIC_V05_H__

#include "dma_port.h"

#define FIELD_BIT(top, bottom) (top - bottom + 1)

#define SWIC_END_PACKET_NO_END 3
#define SWIC_END_PACKET_EOP 1
#define SWIC_END_PACKET_EEP 2
#define SWIC_END_PACKET_NO_END_AND_LOG_ADDR 0

#ifndef TARGET_MCB02
#define DMA_WORD_SIZE (64)
#else
#define DMA_WORD_SIZE (32)
#endif

// Number of device version
typedef union {
  volatile unsigned int _val;
} HW_VER;

// Status register
typedef union {
  volatile unsigned int _val;
  struct {
    volatile unsigned dc_err : FIELD_BIT(0, 0);
    volatile unsigned p_err : FIELD_BIT(1, 1);
    volatile unsigned esc_err : FIELD_BIT(2, 2);
    volatile unsigned credit_err : FIELD_BIT(3, 3);
    volatile unsigned : FIELD_BIT(4, 4);
    volatile unsigned DS_state : FIELD_BIT(7, 5);  // ранее link_state
    volatile unsigned : FIELD_BIT(8, 8);           // rx_buf_full
    volatile unsigned rx_buf_empty : FIELD_BIT(9, 9);
    volatile unsigned : FIELD_BIT(10, 10);  // tx_buf_full
    volatile unsigned tx_buf_empty : FIELD_BIT(11, 11);
    volatile unsigned got_first_bit : FIELD_BIT(12, 12);
    volatile unsigned connected : FIELD_BIT(13, 13);
    volatile unsigned got_time : FIELD_BIT(14, 14);
    volatile unsigned got_int : FIELD_BIT(15, 15);
    volatile unsigned got_ack : FIELD_BIT(16, 16);
    volatile unsigned fl_control : FIELD_BIT(17, 17);
    volatile unsigned link_irq0 : FIELD_BIT(18, 18);  // irq0
    volatile unsigned err_irq0 : FIELD_BIT(19, 19);   // irq1
    volatile unsigned time_irq0 : FIELD_BIT(20, 20);  // irq2
    volatile unsigned cc_11 : FIELD_BIT(21, 21);
    volatile unsigned cc_01 : FIELD_BIT(22, 22);
    volatile unsigned : FIELD_BIT(29, 23);
    volatile unsigned s_lvds_rx : FIELD_BIT(30, 30);
    volatile unsigned d_lvds_rx : FIELD_BIT(31, 31);
  };
} STATUS;

// Register of control code received from net
typedef union {
  volatile unsigned int _val;
  struct {
    volatile unsigned time_code : FIELD_BIT(7, 0);
    volatile unsigned int_code_C01 : FIELD_BIT(15, 8);
    volatile unsigned ack_code_C10 : FIELD_BIT(23, 16);
    volatile unsigned cc_11 : FIELD_BIT(31, 24);
  };
} RX_CODE;

// Control register
typedef union {
  volatile unsigned int _val;
  struct {
    volatile unsigned link_disabled : FIELD_BIT(0, 0);
    volatile unsigned auto_start : FIELD_BIT(1, 1);
    volatile unsigned link_start : FIELD_BIT(2, 2);
    volatile unsigned : FIELD_BIT(3, 3);
    volatile unsigned : FIELD_BIT(4, 4);
    volatile unsigned DSM_rst : FIELD_BIT(5, 5);     // link_rst
    volatile unsigned SWCORE_RST : FIELD_BIT(6, 6);  // rdy_mode
    volatile unsigned : FIELD_BIT(7, 7);
    volatile unsigned test_type : FIELD_BIT(8, 8);
    volatile unsigned tx_single : FIELD_BIT(9, 9);
    volatile unsigned rx_single : FIELD_BIT(10, 10);
    volatile unsigned : FIELD_BIT(11, 11);  // lvds_loopback
    volatile unsigned codec_loopback : FIELD_BIT(12, 12);
    volatile unsigned link_DS_loopback : FIELD_BIT(13, 13);  // link_loopback
    volatile unsigned coeff_10_wr : FIELD_BIT(14, 14);
    volatile unsigned auto_speed : FIELD_BIT(15, 15);
    volatile unsigned dirq_regime : FIELD_BIT(16, 16);
    volatile unsigned : FIELD_BIT(17, 17);
    volatile unsigned link_mask_irq0 : FIELD_BIT(18, 18);
    volatile unsigned err_mask_irq1 : FIELD_BIT(19, 19);
    volatile unsigned time_mask_irq2 : FIELD_BIT(20, 20);
    volatile unsigned ctr : FIELD_BIT(21, 21);
    volatile unsigned tcode_mask : FIELD_BIT(22, 22);
    volatile unsigned int_mask : FIELD_BIT(23, 23);
    volatile unsigned cc_11_mask : FIELD_BIT(24, 24);
    volatile unsigned cc_01_mask : FIELD_BIT(25, 25);
    volatile unsigned int_tout_mask : FIELD_BIT(26, 26);
    volatile unsigned : FIELD_BIT(28, 27);              // int_tout_allow
    volatile unsigned lvds_regime : FIELD_BIT(29, 29);  // lvds_mode
    volatile unsigned s_lvds_tx : FIELD_BIT(30, 30);
    volatile unsigned d_lvds_tx : FIELD_BIT(31, 31);
  };
} MODE_CR;

// Register of transmit speed and lvds control
typedef union {
  volatile unsigned int _val;
  struct {
    volatile unsigned tx_speed : FIELD_BIT(7, 0);
    volatile unsigned pll_tx_en : FIELD_BIT(8, 8);
    volatile unsigned lvds_en : FIELD_BIT(9, 9);
    volatile unsigned tx_speed_10 : FIELD_BIT(17, 10);
    volatile unsigned pll_tx_en_10 : FIELD_BIT(18, 18);
    volatile unsigned lvds_en_10 : FIELD_BIT(19, 19);
    volatile unsigned coeff_10 : FIELD_BIT(28, 20);
    volatile unsigned : FIELD_BIT(31, 29);
  };
} TX_SPEED;

// Register of control code for transmit to net
typedef union {
  volatile unsigned int _val;
  struct {
    volatile unsigned code_val : FIELD_BIT(5, 0);
    volatile unsigned code_type : FIELD_BIT(7, 6);
    volatile unsigned : FIELD_BIT(31, 8);
  };
} TX_CODE;

// Register of reception speed for SpaceWire link.
typedef union {
  volatile unsigned int _val;
  struct {
    volatile unsigned rx_speed : FIELD_BIT(7, 0);
    volatile unsigned : FIELD_BIT(31, 8);
  };
} RX_SPEED;

// Register of counter for packet with zero length
// Not implemented
typedef union {
  volatile unsigned int _val;
} CNT_RX0_PACK;

// Register of counter for packet with nonzero length
typedef union {
  volatile unsigned int _val;
} CNT_RX_PACK;

// Register ISR. Low bits
typedef union {
  volatile unsigned int _val;
} ISR_L;

// Register ISR. High bits
typedef union {
  volatile unsigned int _val;
} ISR_H;

// Register of time marker
typedef union {
  volatile unsigned int _val;
  struct {
    volatile unsigned true_time : FIELD_BIT(5, 0);
    volatile unsigned : FIELD_BIT(7, 6);
    volatile unsigned cur_time : FIELD_BIT(31, 8);
  };
} TRUE_TIME;

// Register of timeout duration
typedef union {
  volatile unsigned int _val;
  struct {
    volatile unsigned glob_cou : FIELD_BIT(15, 0);
    volatile unsigned loc_RESET_SW_ACK : FIELD_BIT(19, 16);  // loc_cou1
    volatile unsigned loc_RESET_T1_ACK : FIELD_BIT(23, 20);  // loc_cou2
    volatile unsigned : FIELD_BIT(31, 24);
  };
} TOUT_CODE;

// Register of timeout flags of ISR. Low bits
typedef union {
  volatile unsigned int _val;
} ISR_TOUT_L;

// Register of timeout flags of ISR. High bits
typedef union {
  volatile unsigned int _val;
} ISR_TOUT_H;

// Register of logical address
typedef union {
  volatile unsigned int _val;
} LOG_ADDR;

// Register of type for distributed interrupts
typedef union {
  volatile unsigned int _val;
} ACK_NONACK_REGIME;

// Register of timeout value
typedef union {
  volatile unsigned int _val;
  struct {
    volatile unsigned loc_reset_sw_nack : FIELD_BIT(3, 0);
    volatile unsigned loc_reset_t1_nack : FIELD_BIT(7, 4);
    volatile unsigned loc_tg : FIELD_BIT(11, 8);
    volatile unsigned loc_th : FIELD_BIT(15, 12);
    volatile unsigned loc_isr_change : FIELD_BIT(19, 16);
    volatile unsigned : FIELD_BIT(31, 20);
  };
} ISR_TOUTS2;

// Register of
typedef union {
  volatile unsigned int _val;
} ISR_HANDLER_TERM_FUNCT;

// Register of
typedef union {
  volatile unsigned int _val;
  struct {
    volatile unsigned last_port : FIELD_BIT(4, 0);
    volatile unsigned : FIELD_BIT(22, 5);
    volatile unsigned code_num : FIELD_BIT(28, 23);
    volatile unsigned code_hl : FIELD_BIT(29, 29);
    volatile unsigned code_type : FIELD_BIT(31, 30);
  };
} ISR_SPEC;

// Register of
typedef union {
  volatile unsigned int _val;
} ISR_1101;

// Register of
typedef union {
  volatile unsigned int _val;
} ISR_MACK_1101;

// Register of
typedef union {
  volatile unsigned int _val;
  struct {
    volatile unsigned g_reset_int : FIELD_BIT(15, 0);
    volatile unsigned l_reset_cou : FIELD_BIT(21, 16);
    volatile unsigned r_mode : FIELD_BIT(22, 22);
    volatile unsigned w_int : FIELD_BIT(31, 23);
  };
} INT_RESET;

// Register of
typedef union {
  volatile unsigned int _val;
  struct {
    volatile unsigned irq_credit_error_extra_fct : FIELD_BIT(0, 0);
    volatile unsigned irq_credit_error_extra_nchar : FIELD_BIT(1, 1);
    volatile unsigned irq_rx_speed_violation : FIELD_BIT(2, 2);
    volatile unsigned : FIELD_BIT(3, 3);   // irq_banned_data_req
    volatile unsigned : FIELD_BIT(4, 4);   // irq_banned_eop_req
    volatile unsigned : FIELD_BIT(5, 5);   // irq_banned_eep_req
    volatile unsigned : FIELD_BIT(6, 6);   // irq_banned_fct_req
    volatile unsigned : FIELD_BIT(7, 7);   // irq_banned_time_req
    volatile unsigned : FIELD_BIT(8, 8);   // rx_4_bit_in
    volatile unsigned : FIELD_BIT(12, 9);  // rx_4_bit_in_data
    volatile unsigned rx_fifo_eop_counter : FIELD_BIT(18, 13);
    volatile unsigned rx_fifo_data_counter : FIELD_BIT(24, 19);
    volatile unsigned : FIELD_BIT(31, 25);
  };
} STATUS2;

// Register of
typedef union {
  volatile unsigned int _val;
  struct {
    volatile unsigned : FIELD_BIT(0, 0);  // spwd_drop_packet
    volatile unsigned send_nulls_only : FIELD_BIT(1, 1);
    volatile unsigned ccode_send_mask : FIELD_BIT(2, 2);
    volatile unsigned ccode_res_mask : FIELD_BIT(3, 3);
    volatile unsigned int_send_mask : FIELD_BIT(4, 4);
    volatile unsigned int_res_mask : FIELD_BIT(5, 5);
    volatile unsigned ack_send_mask : FIELD_BIT(6, 6);
    volatile unsigned ack_res_mask : FIELD_BIT(7, 7);
    volatile unsigned host_int_code : FIELD_BIT(10, 8);
    volatile unsigned host_ack_code : FIELD_BIT(13, 11);
    volatile unsigned sdirq_regime : FIELD_BIT(14, 14);
    volatile unsigned spw_int_code : FIELD_BIT(17, 15);
    volatile unsigned spw_ack_code : FIELD_BIT(20, 18);
    volatile unsigned time_send_mask : FIELD_BIT(21, 21);
    volatile unsigned time_res_mask : FIELD_BIT(22, 22);
    volatile unsigned add_res_mask : FIELD_BIT(23, 23);
    volatile unsigned err_regime : FIELD_BIT(24, 24);
    volatile unsigned : FIELD_BIT(31, 25);
  };
} MODE_CR2;

// Register of
typedef union {
  volatile unsigned int _val;
} INT_H_MACK;

// Register of
typedef union {
  volatile unsigned int _val;
} INT_L_MACK;

// Register of
typedef union {
  volatile unsigned int _val;
} ACK_H_MACK;

// Register of
typedef union {
  volatile unsigned int _val;
} ACKL_L_MACK;

// Register of
typedef union {
  volatile unsigned int _val;
  struct {
    volatile unsigned auto_cou : FIELD_BIT(4, 0);
    volatile unsigned control_time : FIELD_BIT(15, 5);
    volatile unsigned auto_cou_fls : FIELD_BIT(17, 16);
    volatile unsigned : FIELD_BIT(30, 18);
    volatile unsigned control_regime : FIELD_BIT(31, 31);
  };
} AUTO_SPEED_MANAGE;

// Register of
typedef union {
  volatile unsigned int _val;
} ISR_SOURCE_TERM_FUNCT;

// Register of
typedef union {
  volatile unsigned int _val;
} ISR_SPEC_TERM_FUNCT;

// Register of
typedef union {
  volatile unsigned int _val;
} ISR_L_RESET;

// Register of
typedef union {
  volatile unsigned int _val;
} ISR_H_RESET;

// SWIC registers group
typedef volatile struct {
  HW_VER hw_ver;
  STATUS status;
  RX_CODE rx_code;
  MODE_CR mode_cr;
  TX_SPEED tx_speed;
  TX_CODE tx_code;
  RX_SPEED rx_speed;
  CNT_RX0_PACK cnt_rx0_pack;  // Not implemented
  CNT_RX_PACK cnt_rx_pack;
  ISR_L isr_l;
  ISR_H isr_h;
  TRUE_TIME true_time;
  TOUT_CODE tout_code;
  ISR_TOUT_L isr_tout_l;
  ISR_TOUT_H isr_tout_h;
  LOG_ADDR log_addr;
  ACK_NONACK_REGIME ack_nonack_regime;
  ISR_TOUTS2 isr_touts2;
  ISR_HANDLER_TERM_FUNCT isr_handler_term_funct;
  ISR_SPEC isr_spec;
  ISR_1101 isr_1101;
  ISR_MACK_1101 isr_mack_1101;
  INT_RESET int_reset;
  STATUS2 status2;
  MODE_CR2 mode_cr2;
  INT_H_MACK int_h_mack;
  INT_L_MACK int_l_mack;
  ACK_H_MACK ack_h_mack;
  ACKL_L_MACK ackl_l_mack;
  AUTO_SPEED_MANAGE auto_speed_manage;
  ISR_SOURCE_TERM_FUNCT isr_source_term_funct;
  ISR_SPEC_TERM_FUNCT isr_spec_term_funct;
  ISR_L_RESET isr_l_reset;
  ISR_H_RESET isr_h_reset;
} swic_regs_t;

typedef struct {
  swic_regs_t* swic_regs;
  SPIKE_DMA_CHANNEL* dma_swic_rx_des;
  SPIKE_DMA_CHANNEL* dma_swic_rx_dat;
  SPIKE_DMA_CHANNEL* dma_swic_tx_des;
  SPIKE_DMA_CHANNEL* dma_swic_tx_dat;
  const int dma_word_size;
} swic_block_t;

#endif  // __SWIC_V05_H__
