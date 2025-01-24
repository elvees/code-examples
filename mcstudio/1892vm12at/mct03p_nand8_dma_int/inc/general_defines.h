// Copyright 2023-2025 RnD Center "ELVEES", JSC
// SPDX-License-Identifier: MIT

#pragma once

typedef unsigned int uint32;
typedef uint32 uint;
typedef unsigned short uint16;
typedef uint16 ushort;
typedef unsigned char uint8;
typedef unsigned char uchar;
typedef uint8 ubyte;
// typedef char byte;

#define ON true
#define OFF false

#define ENABLE true
#define DISABLE false

#define ERROR (-1)

#define START true
#define STOP false

#define UNION_BIT(x) (1)
#define FIELD_BIT(top, bottom) (top - bottom + 1)

#define INT_TO_SHORT(x) (x * 2)
#define INT_TO_BYTE(x) (x * 4)
#define INT_TO_BIT(x) (x * 32)

#define SHORT_TO_INT(x) ((x + 1) / 2)
#define SHORT_TO_BYTE(x) (x * 2)
#define SHORT_TO_BIT(x) (x * 16)

#define BYTE_TO_INT(x) ((x + 3) / 4)
#define BYTE_TO_SHORT(x) ((x + 1) / 2)
#define BYTE_TO_BIT(x) (x * 8)

#define BIT_TO_INT(x) ((x + 31) / 32)
#define BIT_TO_SHORT(x) ((x + 15) / 16)
#define BIT_TO_BYTE(x) ((x + 7) / 8)

#define MHz_TO_Hz(x) (x * 1000000)
#define Hz_TO_MHz(x) (x / (double)1000000)

static uint Compose2ShortToInt(ushort upper31_16, ushort bottom15_0) {
  return upper31_16 << 16 | bottom15_0;
}

static uint Switch2ShortInInt(uint twisted) {
  return twisted << 16 | twisted >> 16;
}
