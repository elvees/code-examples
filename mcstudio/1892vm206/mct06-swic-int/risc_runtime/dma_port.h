// Copyright 2023-2025 RnD Center "ELVEES", JSC
// SPDX-License-Identifier: MIT

// *******************************************************************/
//
//          This file contains description for dma register,
//          description for dma channel for elvees DMA port,
//                       functions for DMA
//
// *******************************************************************/
#ifndef __DMA_PORT_H__
#define __DMA_PORT_H__

#define FIELD_BIT(top, bottom) (top - bottom + 1)

#include <stddef.h>

#include "mytypes.h"
// Control and status register
// reset bit end and done if read
typedef union {
  volatile unsigned int _val;
  struct {
    volatile unsigned run : FIELD_BIT(0, 0);
    volatile unsigned : FIELD_BIT(1, 1);
    volatile unsigned wn : FIELD_BIT(5, 2);
    volatile unsigned ADDR_SORT : FIELD_BIT(7, 7);
    volatile unsigned : FIELD_BIT(11, 6);
    volatile unsigned chen : FIELD_BIT(12, 12);
    volatile unsigned im : FIELD_BIT(13, 13);
    volatile unsigned end : FIELD_BIT(14, 14);
    volatile unsigned done : FIELD_BIT(15, 15);
    volatile unsigned wcx : FIELD_BIT(31, 16);
  };
} CSR;

// Chain register
typedef union {
  volatile unsigned int _val;
} CP;

// Address of data or descriptor
typedef union {
  volatile UINT_32 _val;

} IR;

// Pseudoregister
// Writing: control RUN bit of CSR register
// Reading: CSR register. Bits END and DONE will not reset.
typedef union {
  volatile unsigned int _val;
  struct {
    volatile unsigned run : FIELD_BIT(0, 0);
  };
} RUN;
// DMA port descriptor
typedef struct {
  CSR csr;
  CP cp;
  IR ir;
  RUN run;
} DMA_CHANNEL;
// DMA port chain descriptor
// SPIKE_DMA_SWIC
typedef struct {
  CSR SPIKE_CSR;
  CP SPIKE_CP;
  IR SPIKE_IR;
  RUN SPIKE_RUN;
} SPIKE_DMA_CHANNEL;
typedef struct {
  unsigned int _Reserved;
  IR _IR;
  CP _CP;
  CSR _CSR;
} DMA_Port_Chain __attribute__((aligned(8)));

// DMA port chain special descriptor for mcb02 board
typedef struct {
  IR _IR;
  CP _CP;
  CSR _CSR;
  unsigned int _Reserved;
} MCB02_DMA_Port_Chain __attribute__((aligned(8)));

// Function DMA_Port_Change_Chain_IR_CSR_CP /
//          MCB02_DMA_Port_Change_Chain_IR_CSR_CP
//
// These functions configures IR, CSR and CP parameters of
// chosen dma chain element
// MCB02_* is a special function, because of different dma registers places in
// the MCB02 board
//
// Parameters:
//       pointer - chosen dma-chain element address
//       IR      - index register (physical memory address)
//       CSR     - control and status register
//       CP      - initial address of the DMA transfer parameter
//                 block for self-initialization
//
// '
//      DMA_Port_Change_Chain_IR_CSR_CP(
//                 &chosen_dma_chain_element,
//                 another_dma_chain_element->_IR._val,
//                 another_dma_chain_element->_CP._val,
//                 another_dma_chain_element._val
//                                     );
// '
//
void DMA_Port_Change_Chain_IR_CSR_CP(unsigned int* pointer, unsigned int IR,
                                     unsigned int CSR, unsigned int CP);
void MCB02_DMA_Port_Change_Chain_IR_CSR_CP(unsigned int* pointer,
                                           unsigned int IR, unsigned int CSR,
                                           unsigned int CP);

// Function: DMA_Port_Configure_Chain
//
// This function configures dma chain element
//
// Parameters:
//       current   - current dma-chain element address
//       next      - next dma-chain element address
//       run       - launching permission
//       im        - END-bit permission
//       chen      - self-initialization procedure permission
//       data_addr - data's source address
//
// '
//      DMA_Port_Configure_Chain(
//                            &dma_chain[0],
//                            &dma_chain[0],
//                            0,
//                            1,
//                            1,
//                            data_addr
//                              );
// '
//
// See also:
//      Manual_1892VM7YA.pdf (page 175)
//
void DMA_Port_Configure_Chain(DMA_Port_Chain* current, DMA_Port_Chain* next,
                              unsigned int word64_amount, unsigned int run,
                              unsigned int im, unsigned int chen,
                              unsigned int* data_addr);

// Function: DMA_Port_Load_Chain /
//           MCB02_DMA_Port_Load_Chain
//
// These functions loads chosen configuration
// into DMA-port registers
// MCB02_* is a special function, because of using special addresses
//
// Parameters:
//      first - configuration structure address
//
// '
//      DMA_Port_Load_Chain(&dma_chain[0], ready_dma_chain);
// '
//
void DMA_Port_Load_Chain(DMA_CHANNEL* dma_port, DMA_Port_Chain* first);
void MCB02_DMA_Port_Load_Chain(DMA_CHANNEL* dma_port,
                               MCB02_DMA_Port_Chain* first);

// Function: DMA_Port_Wait
//
// This function waits for the DMA channel to stop (run bit goes 0).
// May be blocked program
//
// Parameters:
//      dma_port - pointer on DMA_CHANNEL struct
//
void DMA_Port_Wait(DMA_CHANNEL* dma_port);

// Function: DMA_Port_Start
//
// This function starts the DMA channel.
//
// Parameters:
//      dma_port - pointer on DMA_CHANNEL struct
//
void DMA_Port_Start(DMA_CHANNEL* dma_port);

// Function: DMA_Port_Load_Data
//
// This function loads the DMA port registers with function arguments.
//
void DMA_Port_Load_Data(DMA_CHANNEL* pointer, void* IR, unsigned int CSR);

#endif  // __DMA_PORT_H__
