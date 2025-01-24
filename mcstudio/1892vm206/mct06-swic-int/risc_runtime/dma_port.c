// Copyright 2023-2025 RnD Center "ELVEES", JSC
// SPDX-License-Identifier: MIT

// *******************************************************************/
//
// This file implements dma memory channels interface
//
// *******************************************************************/

#include "dma_port.h"

#include "mytypes.h"
void DMA_Port_Change_Chain_IR_CSR_CP(unsigned int* pointer, unsigned int IR,
                                     unsigned int CSR, unsigned int CP) {
  if ((((unsigned int)pointer) & 0x7) == 0) {
    pointer[0] = 0;
    pointer[1] = IR;
    pointer[2] = CP;
    pointer[3] = CSR;
  }
}

void MCB02_DMA_Port_Change_Chain_IR_CSR_CP(unsigned int* pointer,
                                           unsigned int IR, unsigned int CSR,
                                           unsigned int CP) {
  if ((((unsigned int)pointer) & 0x7) == 0) {
    pointer[0] = IR;
    pointer[1] = CP;
    pointer[2] = CSR;
    pointer[3] = 0;
  }
}

void DMA_Port_Configure_Chain(DMA_Port_Chain* current, DMA_Port_Chain* next,
                              unsigned int word64_amount, unsigned int run,
                              unsigned int im, unsigned int chen,
                              unsigned int* data_addr) {
  unsigned int csr_data = 0;

  csr_data =
      (word64_amount << 16) | (im << 13) | (chen << 12) | (0xF << 2) | (run);

  current->_CSR._val = csr_data;
  current->_CP._val = sys_kernel_va_to_pa((unsigned int)&(next->_Reserved)) | 1;
  current->_IR._val = sys_kernel_va_to_pa((unsigned int)data_addr);
}

void DMA_Port_Load_Chain(DMA_CHANNEL* dma_port, DMA_Port_Chain* first) {
  dma_port->cp._val = (sys_kernel_va_to_pa((unsigned int)first) | 1);
}

void MCB02_DMA_Port_Load_Chain(DMA_CHANNEL* dma_port,
                               MCB02_DMA_Port_Chain* first) {
  dma_port->cp._val = ((unsigned int)first | 1);  //->_CP._val;
}

void MCB02_DMA_Port_Configure_Chain(MCB02_DMA_Port_Chain* current,
                                    MCB02_DMA_Port_Chain* next,
                                    unsigned int word64_amount,
                                    unsigned int run, unsigned int im,
                                    unsigned int chen,
                                    unsigned int* data_addr) {
  unsigned int csr_data = 0;

  csr_data =
      (word64_amount << 16) | (im << 13) | (chen << 12) | (0xF << 2) | (run);

  current->_CSR._val = csr_data;
  current->_CP._val = sys_kernel_va_to_pa((unsigned int)&(next->_IR)) | 1;
  current->_IR._val = sys_kernel_va_to_pa((unsigned int)data_addr);
}

void DMA_Port_Wait(DMA_CHANNEL* dma_port) {
  //    while (dma_port->run.run);
  while (dma_port->run.run) {
    asm("nop");
  };
}

void DMA_Port_Start(DMA_CHANNEL* dma_port) { dma_port->run._val = 1; }
#define DMA_CH4_IR_ *((volatile int*)(0xb8301108))
#define DMA_CH0_IR_ *((volatile int*)(0xb8301008))
void DMA_Port_Load_Data_tr(DMA_CHANNEL* pointer, void* IR, unsigned int CSR) {
  pointer->csr._val = CSR;
  unsigned int addr_physical_array = sys_kernel_va_to_pa((unsigned)IR);
  DMA_CH4_IR_ = addr_physical_array;
  // pointer -> ir._val  = sys_kernel_va_to_pa((unsigned)IR);
}
UINT_32 TIME_ = 100000;
void DMA_Port_Load_Data_rx(DMA_CHANNEL* pointer, void* IR, unsigned int CSR) {
  pointer->csr._val = CSR;
  unsigned int addr_physical_array = sys_kernel_va_to_pa((unsigned)IR);
  DMA_CH0_IR_ = addr_physical_array;
  // pointer -> ir._val  = sys_kernel_va_to_pa((unsigned)IR);
}
void DMA_Port_Load_Data(DMA_CHANNEL* pointer, void* IR, unsigned int CSR) {
  pointer->csr._val = CSR;
  pointer->ir._val = sys_kernel_va_to_pa((unsigned)IR);
}
