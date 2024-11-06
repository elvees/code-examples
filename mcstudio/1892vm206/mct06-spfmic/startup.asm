# Copyright 2023-2025 RnD Center "ELVEES", JSC
# SPDX-License-Identifier: MIT

# Стартовый код для проектов без использования библиотеки newlib
# Назначает адрес стека и области small-переменных (адресация по регистру gp), обнуляет область неинициализированных переменных, разрешает доступ к FPU, переходит на main()
    .set	noreorder
    .set	mips32
    .text
#------------------------------------------------
# Точка входа в программу
#
_start: .global _start
    .ent _start
    la $28,_gp		  # Установка gp
    la $29,__stack    # Установка sp
# Очистка области неинициализированных переменных
    la $2,_bss_start
    la $4,_end
    beq $2,$4,2f
    nop
1:  sw $0,0($2)
    addiu $2,4
    bne	$2,$4,1b
    nop
# Разрешение доступа к FPU
    mfc0 $2,$12
    lui $3,0x2000
    or $2,$2,$3
    mtc0 $2,$12
# Переход на main()
2:  la $2, (main)
    jr $2
    nop

3:  b 3b
    nop
    .end _start
