// Copyright 2023-2025 RnD Center "ELVEES", JSC
// SPDX-License-Identifier: MIT

// *****************************************************************
//                  Risc-Dsp runtime library
//
// This file implements interface to SpaceWire Interface Controller.
//
// There are 3 function groups:
// 1) Functions needed for working with group called "ports"
// 2) Functions needed for working with DMA
// 3) Functions needed for working with transaction packets
//
// *******************************************************************

#ifndef _SWIC_H_
#define _SWIC_H_

#include "erlcommon.h"
#include "swic_v06.h"

#define MAX_PACKET_LEN 1024

#ifdef __cplusplus
extern "C" {
#endif

// 1-ST FUNCTIONS GROUP

// Section: Functions
//
// Function: get_swic_dev
//
// Gets pointer to selected SWIC channel registers.
//
// Parameters:
//      swic_id      - number of requested SWIC channel
//
// Return:
//		NULL        - swic_id is not in 0..3 range (possible SWIC memory
// channels are 					  swic0, swic1,
// swic2(mcb only), swic3(mcb only)) 		Pointer to swic<id> registers -
// otherway
//
// > get_swic_dev(0);
//
swic_regs_t* swic_get_regs(int swic_id);

swic_block_t swic_get_dev(int swic_id);

void swic_apply_mport_base(unsigned int base_address);

// Function: swic_clear_cnt_rxx_pack
//
// Clears hardware packets' counters
//
// Parameters:
//      index_port - port number:
//                      0 - 1-st port
//                      1 - 2-nd port
//
void swic_clear_cnt_rxx_pack(unsigned int index_port);

// Function: swic_set_timing
//
// Configures timing for spacewire state machine
//
// The swic_set_timing function may produce error if the SWIC port is in Running
// state. The function may be applied only after hw reset or after swic_clear
// call.
//
// Parameters:
//      index_port - port number:
//                      0 - 1-st port
//                      1 - 2-nd port
//
void swic_set_timing(unsigned int index_port);

// Function: swic_clear
//
// Stops the connection and clears all port statuses
//                              (error and interruption bits)
//
// Parameters:
//      index_port - port number:
//                      0 - 1-st port
//                      1 - 2-nd port
//
void swic_clear(unsigned int index_port);

// Function: swic_init
//
// Starts the connection with sending NULL char to link
// Setups LINK_MASK=1, ERR_MASK=1, TIME_MASK=1 in MODE_CR register.
//
// The swic_init function may produce error if the SWIC port is in Running
// state. The function may be applied only after hw reset or after swic_clear
// call.
//
// Parameters:
//      index_port - port number:
//                      0 - 1-st port
//                      1 - 2-nd port
//
void swic_init(unsigned int index_port);

// Function: swic_init_static_mode
//
// Configures swic to output pins direct control
//
// The swic_init_static_mode function may produce error if the SWIC port is in
// Running state. The function may be applied only after hw reset or after
// swic_clear call.
//
// Parameters:
//      index_port - port number:
//                      0 - 1-st port
//                      1 - 2-nd port
//
void swic_init_static_mode(unsigned int index_port);

// Function: swic_init_loop
//
// Starts the connection with internal codec loopback
// SpaceWire port is connected with itself
//
// The swic_init_loop function may produce error if the SWIC port is in Running
// state. The function may be applied only after hw reset or after swic_clear
// call.
//
// Parameters:
//      index_port - port number:
//                      0 - 1-st port
//                      1 - 2-nd port
//
void swic_init_loop(unsigned int index_port);

// Function: swic_is_connected
//
// Checks that connection in port is established
//
// Parameters:
//      index_port - port number:
//                      0 - 1-st port
//                      1 - 2-nd port
//
int swic_is_connected(unsigned int index_port);

// Function: swic_set_tx_speed
//
// Sets tx speed, if it's more than limited speed, then do nothing
//
// Parameters:
//      index_port - port number:
//                      0 - 1-st port
//                      1 - 2-nd port
//      speed      - connection speed in Mbps
//
void swic_set_tx_speed(unsigned int index_port, int speed);

// Function: swic_interrupt_set
//
// Set interrupts in mode_cr.
//
// Parameters:
//      index_port - port number:
//                      0 - 1-st port
//                      1 - 2-nd port
//      interrupts - interrupts bits
//
void swic_interrupt_set(unsigned int index_port, unsigned int interrupts);

// Function: swic_interrupt_unset
//
// Unset interrupts in mode_cr.
//
// Parameters:
//      index_port - port number:
//                      0 - 1-st port
//                      1 - 2-nd port
//      interrupts - interrupts bits
//
void swic_interrupt_unset(unsigned int index_port, unsigned int interrupts);

// Function: swic_get_status
//
// Return status register.
//
// Parameters:
//      index_port - port number:
//                      0 - 1-st port
//                      1 - 2-nd port
//
int swic_get_status(int index_port);

// 2-ND FUNCTIONS GROUP

// Function: swic_dma_prepare_send
//
// Prepares dma transfer
//
// Parameters:
//      index_port - port number:
//                      0 - 1-st port
//                      1 - 2-nd port
//      src        - virtual data address
//      desc       - virtual descriptor address
//      wsize      - words amount for transmit
//
enum ERL_ERROR swic_dma_prepare_send(unsigned int index_port, void* src,
                                     void* desc, unsigned int wsize);

// Function: swic_dma_start_chain
//
// Begins dma transfer starting from selected chain element
//
// Parameters:
//      pointer         - chain element pointer
//      index_port      - port number:
//                          0 - 1-st port
//                          1 - 2-nd port
//
//      channel_index   - index of dma channel:
//                          SWIC_DMA_CHANNEL_RX_DES
//                          SWIC_DMA_CHANNEL_RX_DAT
//                          SWIC_DMA_CHANNEL_TX_DES
//                          SWIC_DMA_CHANNEL_TX_DAT
//
int swic_dma_start_chain(unsigned int* pointer, unsigned int index_port,
                         unsigned int channel_index);

// Function: swic_dma_stop_channels
//
// Stops all dma channels for selected port
//
// Parameters:
//      index_port - port number:
//                      0 - 1-st port
//                      1 - 2-nd port
//
void swic_dma_stop_channels(unsigned int index_port);

// 3-RD FUNCTIONS GROUP

// Function: swic_receiver_packet_wait
//
// Waits for one packet would be received
// Reset bits END and DONE in CSR registers.
//
// Parameters:
//      index_port - port number:
//                      0 - 1-st port
//                      1 - 2-nd port
//
enum ERL_ERROR swic_receiver_packet_wait(void);

// Function: swic_prepare_send_packet
//
// Prepares one packet transfer to selected port
//
// Parameters:
//      index_port - port number:
//                      0 - 1-st port
//                      1 - 2-nd port
//      src        - data pointer
//      descr      - descriptor pointer
//      size       - data size in bytes
//      type       - end of packet type
//
// See also:
//      "swic_v03.h"
//
enum ERL_ERROR swic_prepare_send_packet(unsigned int index_port, void* src,
                                        void* descr, int size, int type);

// Function: swic_run_send_packet
//
// Begins one packet transfer
//
// Parameters:
//      index_port - port number:
//                      0 - 1-st port
//                      1 - 2-nd port
//
// See also:
//      <swic_prepare_send_packet>
//
enum ERL_ERROR swic_run_send_packet(unsigned int index_port);

// Function: swic_send_packet
//
// Prepares and sends one packet to selected port
// (swic_prepare_send_packet + swic_run_send_packet = swic_send_packet)
//
// Parameters:
//      index_port - port number:
//                      0 - 1-st port
//                      1 - 2-nd port
//      src        - data pointer
//      descr      - descriptor pointer
//      size       - data size in bytes
//      type       - end of packet type
//
// See also:
//      "swic_v03.h"
//
enum ERL_ERROR swic_send_packet(void* src, void* descr, int size, int type);

// Function: swic_test_send_packet
//
// Tests selected port for transferability
//
// Parameters:
//      index_port - port number:
//                      0 - 1-st port
//                      1 - 2-nd port
// Return:
//      0 - packet may not be sent
//      1 - packet may be sent
//
unsigned short swic_test_send_packet(unsigned int index_port);

// Function: swic_prepare_receiver_packet
//
// Prepares one packet receiving
//
// Parameters:
//      index_port  - port number:
//                      0 - 1-st port
//                      1 - 2-nd port
//      dst         - pointer of memory for packet
//      descr       - pointer of memory for descriptor
//      word_length - max size of memory for packet in word
//
enum ERL_ERROR swic_prepare_receiver_packet(unsigned int index_port, void* dst,
                                            unsigned int* descr,
                                            unsigned int word_length);

// Function: swic_prepare_receiver_packet
//
// Begins one packet receiving
//
// Parameters:
//      index_port - port number:
//                      0 - 1-st port
//                      1 - 2-nd port
//
// See also:
//      <swic_prepare_receiver_packet>
//
enum ERL_ERROR swic_run_prepare_receive_packet(unsigned int index_port);

// Function: swic_receiver_packet_run
//
// Prepares and begins one packet receiving
// swic_prepare_receiver_packet + swic_run_prepare_receive_packet =
// swic_receiver_packet_run
//
// Parameters:
//      index_port  - port number:
//                      0 - 1-st port
//                      1 - 2-nd port
//      dst         - packet memory pointer
//      descr       - descriptor memory pointer
//      word_length - max words amount (memory size) for packet
//
enum ERL_ERROR swic_receiver_packet_run(void* dst, unsigned int* descr,
                                        unsigned int word_length);

// Function: swic_create_desc
//
// Creates one descriptor in memory
//
// Parameters:
//      pointer            - pointer for descriptor memory
//      size_in_byte       - packet size in bytes
//      type_of_end_packet - end of packet type
//
// See also:
//      "swic_v03.h"
//
void swic_create_desc(unsigned int* pointer, unsigned int size_in_byte,
                      unsigned int type_of_end_packet);

#ifdef __cplusplus
}
#endif

#endif  // _SWIC_H_
