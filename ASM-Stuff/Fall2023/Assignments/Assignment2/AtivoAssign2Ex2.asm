#
# AtivoAssign2Ex2.asm
#
# Jacob Ativo
# 10/5
# Looking at how addu, and sll 
# can be used for multiplication
#

        .text
        .globl  main

main:   ori     $t0, $zero, 0       # initializing to $t0 t0 0
        addu    $t0, $t0, 4096      # adding 4096 to it 16 times
        addu    $t0, $t0, 4096      # same as 4096 * 16 (or 0x1000 * 0x10)
        addu    $t0, $t0, 4096
        addu    $t0, $t0, 4096
        addu    $t0, $t0, 4096
        addu    $t0, $t0, 4096
        addu    $t0, $t0, 4096
        addu    $t0, $t0, 4096
        addu    $t0, $t0, 4096
        addu    $t0, $t0, 4096
        addu    $t0, $t0, 4096
        addu    $t0, $t0, 4096
        addu    $t0, $t0, 4096
        addu    $t0, $t0, 4096
        addu    $t0, $t0, 4096
        addu    $t0, $t0, 4096
        li      $t1, 4096           # using sll to make $t1 = $t0 
        sll     $t1, $t1, 4         # 4 is magic number b/c 1 left shift in hex = 4 left shifts in binary
        li      $t2, 4096           # using repeated addition to make $t2 = $t0
        addu    $t2, $t2, $t2       # start off with 2*4096. adding to itself is the same as doubling
        addu    $t2, $t2, $t2       # now 4*4096
        addu    $t2, $t2, $t2       # now 8*4096
        addu    $t2, $t2, $t2       # now 16*4096, which is the goal 

## End of file