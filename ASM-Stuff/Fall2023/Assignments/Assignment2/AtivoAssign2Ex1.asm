#
# AtivoAssign2Ex1.asm
#
# Jacob Ativo
# 10/5
# Looking at how load immediate works
# and using addu for the first time
#

        .text
        .globl  main

main:   li      $t1, 456        # one instruction. li does lui only if top and bottom 16 bits are not empty (456 < 2^16)
        li      $t2, -229       # two instructions. it loads upper 16 bits and or's with bottom sixteen (-229 < 0 AND 229 is not a power of two)
        li      $t3, 325        # one instruction. (325 < 2^16, so top sixteen bits are empty)
        li      $t4, -552       # two instructions (-552 < 0 AND 552 is not a power of two), so top and bottom 16 bits are not empty.
        addu    $t0, $t1, $t2   # ignoring overflow and putting sum in $t0 
        addu    $t0, $t0, $t3
        addu    $t0, $t0, $t4   # comes out to 0

## End of file