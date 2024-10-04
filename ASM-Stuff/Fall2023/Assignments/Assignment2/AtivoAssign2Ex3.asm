#
# AtivoAssign2Ex3.asm
#
# Jacob Ativo
# 10/5
# Looking at the difference between
# add and addu by adding big numbers
#

        .text
        .globl  main

main:   ori     $t1, $zero, 0x7000
        sll     $t1, $t1, 16
        addu    $t0, $t1, $t1       # result should be incorrect since $t1 is adding positive numbers and getting a negative sum (leading bit = 1)
        add     $t2, $t1, $t1       # BOOM! program will "trap" due to overflow

## End of file