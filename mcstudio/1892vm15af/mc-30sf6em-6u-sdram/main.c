// Copyright 2023-2025 RnD Center "ELVEES", JSC
// SPDX-License-Identifier: MIT

#define BASE_ADDR 0x80002000
#define SIZE 64
// Регистр конфигурации типа SDRAM
#define SDRCON *((volatile int *)0xb82f1014)
// Регистр временных параметров памяти типа SDRAM
#define SDRTMR *((volatile int *)0xb82f1018)
// Регистр управления режимами памяти типа SDRAM
#define SDRCSR *((volatile int *)0xb82f101c)

// Заполнение массива
void FillArray(unsigned int *array, unsigned int len) {
  unsigned int i;

  for (i = 0; i < len; i++) {
    array[i] = i;
  }
}

// Заполнение нулями
void ZeroArray(unsigned int *array, unsigned int len) {
  unsigned int i;

  for (i = 0; i < len; i++) {
    array[i] = 0;
  }
}

// Функция считывания из памяти
void Read(unsigned addr, unsigned len, unsigned *array) {
  unsigned int i;

  for (i = 0; i < len; i++) {
    array[i] = *(unsigned int *)addr;
    addr += 4;
  }
}

// Функция записи массива в память
void Write(unsigned addr, unsigned len, const unsigned *data) {
  while (len--) {
    *(unsigned int *)addr = *data++;  // Берётся следующее значение из массива.
    addr += 4;
  }
}

// Функция сравнения
unsigned int VerifyArray(unsigned int *array1, unsigned int *array2,
                         unsigned int len) {
  unsigned int i;

  for (i = 0; i < len; i++) {
    if (array1[i] != array2[i]) {
      return 0;
    }
  }

  return 1;
}

int main() {
  // инициализация SDRAM
  SDRCON = 0x06180030;
  SDRTMR = 0x00740111;
  SDRCSR = 0x40;
  SDRCSR = 0x1;

  unsigned int out;
  unsigned int InputArray[SIZE];
  unsigned int OutputArray[SIZE];

  FillArray(InputArray, SIZE);
  ZeroArray(OutputArray, SIZE);

  Write(BASE_ADDR, SIZE, InputArray);
  Read(BASE_ADDR, SIZE, OutputArray);

  out = VerifyArray(OutputArray, InputArray, SIZE);

  // Здесь необходимо поставить точку останова
  return out;
}
