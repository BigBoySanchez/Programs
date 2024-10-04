#
# AtivoAssign2Ex5.asm
#
# Jacob Ativo
# 10/5
# Making a polynomial equation using labels
# stores the answer in another label
# 

        
        .data
x:      .word   0
answer: .word   0

        .text
        .globl  main

main:   lw      $t0, x
        nop
        nop
        sll     $t2, $t0, 2             # same as multiplying x by 4 (4x)
        addu    $t2, $t2, $t0           # then adding x again, making 5 (5x)
        multu   $t0, $t0                # making x^2
        mflo    $t1                     # $t1 is for x^n
        sll     $t3, $t1, 2             # same as 4*x^2
        subu    $t3, $zero, $t3         # NOT $t2 (makes -4x^2) 
        addu    $t3, $t3, $t1           # same as -4x^2+x^2
        multu   $t1, $t0                # x^3 now
        mflo    $t1
        sll     $t4, $t1, 1             # 2x^3
        addiu   $t0, $t2, 12            # 12 + 5x
        addu    $t0, $t0, $t3           # 12 + 5x - 3x^2
        addu    $t0, $t0, $t4           # 12 + 5x - 3x^2 + 2x^3
        sw      $t0, answer

## End of file