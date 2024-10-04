#
# AtivoAssign2Ex6.asm
#
# Jacob Ativo
# 10/5
# Making an equation using 2 labels
# I tried keeping it to 2 registers, but I couldn't

        .data
x:      .word   0
y:      .word   0
answer: .word   0

        .text
        .globl  main

main:   lw      $t0, x
        lw      $t1, y
        sll     $t2, $t0, 1         # making 2x and stalling for y load
        subu    $t2, $t2, $t1       # 2x-y
        multu   $t0, $t1            # making xy
        mflo    $t0
        addu    $t2, $t0, $t2       # xy+2x-y
        sll     $t0, $t0, 1         # 2xy
        addu    $t0, $t0, $t2       # makes 3xy+2x-y
        addiu   $t0, $t0, 2         # 3xy+2x-y+2
        sll     $t0, $t0, 1         # makes 2(3xy+2x-y+2)
        sll     $t2, $t0, 1         # makes 4(3xy+2x-y+2)
        addu    $t0, $t0, $t2       # 6(3xy+2x-y+2) = 18xy+12x-6y+12
        sw      $t0, answer

## End of file