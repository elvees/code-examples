// Copyright 2023-2025 RnD Center "ELVEES", JSC
// SPDX-License-Identifier: MIT

#ifndef __MYTYPES_H
#define __MYTYPES_H

typedef unsigned int UINT_32;
typedef unsigned short UINT_16;
typedef unsigned char UINT_8;
typedef int INT_32;
typedef short INT_16;
typedef char INT_8;
typedef int BOOL;
typedef unsigned char byte;
typedef unsigned char BYTE;
typedef unsigned long DWORD;
typedef unsigned short WORD;
typedef long long INT_64;
typedef long long unsigned int UINT_64;
typedef unsigned int size_t;

typedef unsigned int HANDLE;
typedef void (*CALLBACK_FUNCTION)(void);

#define TRUE 1
#define FALSE 0
// #define NULL	(void*)0

#define SwapShort(x) (((x) >> 8 & 0x00ff) | ((x) << 8 & 0xff00))
#define SwapLong(x)                                     \
  (((x) >> 24 & 0x000000ff) | ((x) >> 8 & 0x0000ff00) | \
   ((x) << 8 & 0x00ff0000) | ((x) << 24 & 0xff000000))

#endif /* __MYTYPES_H */
