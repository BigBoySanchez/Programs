#
# AtivoAssign2Ex4.asm
#
# Jacob Ativo
# 10/5
# Loading >16-bit numbers 
# and using multu and divu on them
# 

        .text
        .globl  main

main:   ori     $t1, $zero, 0x0018
        sll     $t1, $t1, 16
        ori     $t1, $t1, 0x6A00
        ori     $t2, $zero, 0x0001
        sll     $t2, $t2, 16
        ori     $t2, $t2, 0x3880
        ori     $t3, $zero, 0x0006
        sll     $t3, $t3, 16
        ori     $t3, $t3, 0x1A80
        multu   $t1, $t2
        mfhi    $t4
        mflo    $t5
        sll     $t4, $t4, 27            # b/c hi is 5 bits (5+27 = 32)
        srl     $t6, $t5, 5             # b/c start of zero fill is after 5 bits
        or      $t0, $t4, $t6           # same as (x*y)/32 b/c low 5 bits were thrown out
        divu    $t0, $t3
        mflo    $t7
        sll     $t7, $t7, 5             # (x*y)/32/z*32 = (x*y)/z ONLY WORKS b/c last 5 bits of lo are 0

## End of file