// Copyright 2023-2025 RnD Center "ELVEES", JSC
// SPDX-License-Identifier: MIT

//*******************************************************************************
// Содержит следующие макросы для доступа к регистрам:
// DMA_MEM_CH0n, DMA_MEM_CH0(n)
// DMA_MEM_CH1n, DMA_MEM_CH1(n)  где  (n=0...3)
//
// Пример использования:
// 	tmp = DMA_MEM_CH00.CSR.data;	//Чтение регистра CSR канала
// DMA_MEM_CH00 как 32 битное слово tmp = DMA_MEM_CH01.CSR.bits.WN;	//Чтение
// значения поля WN регистра CSR канала DMA_MEM_CH01 DMA_MEM_CH10.Y.bits.OY =
// tmp;	//Запись значения в поле OY регистра Y канала DMA_MEM_CH10
//******************************************************************************/
#ifndef MCT03P_DMA_MEM_CH_REGS_H_
#define MCT03P_DMA_MEM_CH_REGS_H_

//==============================================================================
//	CSR
//==============================================================================
struct __attribute__((packed,
                      aligned(4))) DMA_MEM_CH_CSR_BITS {  // bits  description
  Uint16 RUN : 1;  // Состояние работы канала DMA
  Uint16 DIR : 1;  // Направление обмена данными
  Uint16 WN : 4;   // Пакет данных, который передается по коммутатору AXI Switch
  Uint16 EN64 : 1;       // Формат передаваемых данных по коммутатору	AXI
                         // Switch
  Uint16 START_DSP : 1;  // Разрешение запуска работы DSP-ядра
  Uint16 MODE : 1;       // Режим модификации адреса регистра IR0
  Uint16 IR1_2D : 1;     // Режим модификации адреса регистра IR1
  Uint16 MASK : 1;       // Маска внешнего запроса прямого доступа nDMAR
  Uint16 rsrv_1 : 1;     // Резерв
  Uint16 CHEN : 1;       // Разрешение выполнения очередной процедуры
                         // самоинициализации
  Uint16 IM : 1;         // Маска разрешение установки признака END
  Uint16 END : 1;        // Признак завершения передачи блока данных (при IM=1)
  Uint16 DONE : 1;  // Признак завершения передачи блока данных (при CHEN=0)
  Uint16 WCX : 16;  // Число слов данных, которые должен передать канал DMA
};

union DMA_MEM_CH_CSR_REG {
  Uint32 data;
  struct DMA_MEM_CH_CSR_BITS bits;
};

//==================================================
//	OR
//==================================================
struct __attribute__((packed,
                      aligned(4))) DMA_MEM_CH_OR_BITS {  // bits  description
  Uint16 OR0 : 16;  // Смещение (приращение) адреса для индексного регистра IR0
  Uint16 OR1 : 16;  // Смещение (приращение) адреса для индексного регистра IR1
};

union DMA_MEM_CH_OR_REG {
  Uint32 data;
  struct DMA_MEM_CH_OR_BITS bits;
};

//==================================================
//	Y
//==================================================
struct __attribute__((packed,
                      aligned(4))) DMA_MEM_CH_Y_BITS {  // bits  description
  Uint16 OY : 16;   // Смещение (приращение) адреса памяти в 32-разрядных словах
                    // по направлению Y
  Uint16 WCY : 16;  // Число строк по Y направлению
};

union DMA_MEM_CH_Y_REG {
  Uint32 data;
  struct DMA_MEM_CH_Y_BITS bits;
};

//==============================================================================
// DMA_MEM структура
//==============================================================================
typedef volatile struct {
  union DMA_MEM_CH_CSR_REG CSR;     // Регистр управления и состояния
  union DATA_REG_COMMON_UNION CP;   // Регистр указателя цепочки
  union DATA_REG_COMMON_UNION IR0;  // Регистр индекса "0"
  union DATA_REG_COMMON_UNION IR1;  // Регистр индекса "1"
  union DMA_MEM_CH_OR_REG OR;       // Регистр смещений
  union DMA_MEM_CH_Y_REG
      Y;  // Регистр параметров направления Y при двухмерной адресации
  union DMA_MEM_CH_CSR_REG
      RUN;  // На запись:Псевдорегистр управления состоянием бита RUN регистра
            // CSR0 На чтение: Регистр управления и состояния без сброса битов
            // “END” и ”DONE”
} DMA_MEM_REGS_TYPE;

//==================================================
//	Макросы
//==================================================
#define DMA_MEM_CH00 (*((DMA_MEM_REGS_TYPE*)DMA_MEM_CH00_ADDR))
#define DMA_MEM_CH01 (*((DMA_MEM_REGS_TYPE*)DMA_MEM_CH01_ADDR))
#define DMA_MEM_CH02 (*((DMA_MEM_REGS_TYPE*)DMA_MEM_CH02_ADDR))
#define DMA_MEM_CH03 (*((DMA_MEM_REGS_TYPE*)DMA_MEM_CH03_ADDR))

#define DMA_MEM_CH10 (*((DMA_MEM_REGS_TYPE*)DMA_MEM_CH10_ADDR))
#define DMA_MEM_CH11 (*((DMA_MEM_REGS_TYPE*)DMA_MEM_CH11_ADDR))
#define DMA_MEM_CH12 (*((DMA_MEM_REGS_TYPE*)DMA_MEM_CH12_ADDR))
#define DMA_MEM_CH13 (*((DMA_MEM_REGS_TYPE*)DMA_MEM_CH13_ADDR))

#define DMA_MEM_CH0(num) \
  (*((DMA_MEM_REGS_TYPE*)(DMA_MEM_CH00_ADDR + 0x80 * num)))
#define DMA_MEM_CH1(num) \
  (*((DMA_MEM_REGS_TYPE*)(DMA_MEM_CH10_ADDR + 0x80 * num)))
//==============================================================================

#endif /* MCT03P_DMA_MEM_CH_REGS_H_ */
