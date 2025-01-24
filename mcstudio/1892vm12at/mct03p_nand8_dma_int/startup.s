# Copyright 2023-2025 RnD Center "ELVEES", JSC
# SPDX-License-Identifier: MIT

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
    bne    $2,$4,1b
    nop
# Переход на main()
2:  lui $2,%hi(main)
    ori $2,%lo(main)
    jr $2
    nop
# Переход в отладочный режим с помощью специального break
# break 0x1=.word 0x4d
    break 0x1
    nop

3:  b 3b
    nop
    .end _start
