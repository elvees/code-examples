// Copyright 2023-2025 RnD Center "ELVEES", JSC
// SPDX-License-Identifier: MIT

#define BASE_ADDR 0xBC000000  // Базовый адрес ПЗУ подключенной к nCS3
#define SIZE 16  // Размер записываемого массива (в 32-разрядных словах)

#define CR_PLL *(unsigned int*)0xB82F4000
#define CSCON3 *(unsigned int*)0xB82F100C
#define SDRCSR *(unsigned int*)0xB82F101C
#define APPLY_BIT (1 << 6)
// Для установки поля ADDR регистра CSCON3
#define SET_CS3_ADDR(x) 0x10F0000 | (x << 20)

// Команды управления ПЗУ (см.главу 7 даташита на память)
#define UNLOCK_CMD1_A 0xAA8
#define UNLOCK_CMD1_D 0xAAAAAAAA
#define UNLOCK_CMD2_A 0x554
#define UNLOCK_CMD2_D 0x55555555
#define PROGRAM_SETUP 0xA0A0A0A0
#define SETUP_CMD 0x80808080
#define SECTOR_ERASE_CMD 0x30303030

int ret;

// Функция стирания одного сектора ПЗУ
void sector_erase(unsigned int erase_addr) {
  CSCON3 = SET_CS3_ADDR(0x2);
  SDRCSR = APPLY_BIT;
  *(unsigned int*)(BASE_ADDR + UNLOCK_CMD1_A) = UNLOCK_CMD1_D;

  CSCON3 = SET_CS3_ADDR(0x1);
  SDRCSR = APPLY_BIT;
  *(unsigned int*)(BASE_ADDR + UNLOCK_CMD2_A) = UNLOCK_CMD2_D;

  CSCON3 = SET_CS3_ADDR(0x2);
  SDRCSR = APPLY_BIT;
  *(unsigned int*)(BASE_ADDR + UNLOCK_CMD1_A) = SETUP_CMD;

  CSCON3 = SET_CS3_ADDR(0x2);
  SDRCSR = APPLY_BIT;
  *(unsigned int*)(BASE_ADDR + UNLOCK_CMD1_A) = UNLOCK_CMD1_D;

  CSCON3 = SET_CS3_ADDR(0x1);
  SDRCSR = APPLY_BIT;
  *(unsigned int*)(BASE_ADDR + UNLOCK_CMD2_A) = UNLOCK_CMD2_D;

  CSCON3 = SET_CS3_ADDR(0x0);
  SDRCSR = APPLY_BIT;
  *(unsigned int*)erase_addr = SECTOR_ERASE_CMD;

  check_dq2dq6_toggling();
}

// Подготовка ПЗУ к циклу записи 1 байта
void write_unlock_cycle() {
  CSCON3 = SET_CS3_ADDR(0x2);
  SDRCSR = APPLY_BIT;
  *(unsigned int*)(BASE_ADDR + UNLOCK_CMD1_A) = UNLOCK_CMD1_D;

  CSCON3 = SET_CS3_ADDR(0x1);
  SDRCSR = APPLY_BIT;
  *(unsigned int*)(BASE_ADDR + UNLOCK_CMD2_A) = UNLOCK_CMD2_D;

  CSCON3 = SET_CS3_ADDR(0x2);
  SDRCSR = APPLY_BIT;
  *(unsigned int*)(BASE_ADDR + UNLOCK_CMD1_A) = PROGRAM_SETUP;
}

// Функция записи одного 32-разрядного слова
void write_word(unsigned int addr, unsigned int word) {
  write_unlock_cycle();

  CSCON3 = SET_CS3_ADDR(0x0);
  SDRCSR = APPLY_BIT;
  *(unsigned int*)addr = (word & 0xFF);

  check_dq2dq6_toggling();

  write_unlock_cycle();

  CSCON3 = SET_CS3_ADDR(0x1);
  SDRCSR = APPLY_BIT;
  *(unsigned int*)addr = ((word >> 8) & 0xFF);

  check_dq2dq6_toggling();

  write_unlock_cycle();

  CSCON3 = SET_CS3_ADDR(0x2);
  SDRCSR = APPLY_BIT;
  *(unsigned int*)addr = ((word >> 16) & 0xFF);

  check_dq2dq6_toggling();

  write_unlock_cycle();

  CSCON3 = SET_CS3_ADDR(0x3);
  SDRCSR = APPLY_BIT;
  *(unsigned int*)addr = ((word >> 24) & 0xFF);

  check_dq2dq6_toggling();
}

void pause(int t) {
  for (int i = 0; i < t; i++) asm("nop");
}

// Заполнение массива тестовыми данными
void fill_array(unsigned int* array) {
  for (int i = 0; i < SIZE; i++) array[i] = i + 1;
}

// Функция проверки памяти на переключение (см. пункт 7.8 "Write Operation
// Status" даташита) Переключение памяти происходит при операциях записи или
// стирания
int check_dq2dq6_toggling(void) {
  int t_count = 0, t_out = 0, d = 0, d_past = 0xff;

  while (1) {
    d = *(unsigned int*)BASE_ADDR;

    if (d != d_past) {
      pause(1);
      t_out++;
      t_count = 0;
    }
    d_past = d;
    t_count++;

    if (t_count > 100000) break;
    if (t_out > 30000000) return 0;  // Выход по таймауту
  }
  return 1;
}

// Проверка соответствия записанных данных тестовому массиву
// Возвращаемое значение: 0 - ошибок нет, 1 - есть ошибка.
int verify(unsigned int start_addr, unsigned int* arr, unsigned int len) {
  for (int i = 0; i < len; i++) {
    if (*(unsigned int*)(start_addr + (0x4 * i)) != arr[i]) return 1;
  }
  return 0;
}

int main(void) {
  // Установка PLL: MPORT 50 МГц, ЦПУ 100 МГц
  CR_PLL = 0x8A94;

  unsigned int array[SIZE];

  fill_array(array);

  sector_erase(BASE_ADDR);

  for (int i = 0; i < SIZE; i++) {
    write_word(BASE_ADDR + (0x4 * i), array[i]);
  }

  ret = verify(BASE_ADDR + 0x0, array, SIZE);

  /* Здесь необходимо поставить точку останова */
  asm("nop");

  return ret;
}
