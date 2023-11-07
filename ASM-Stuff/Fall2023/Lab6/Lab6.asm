#
# Lab6.asm
#
# Jacob Ativo
# 11/7
# Using the shift
# multiply method in MIPS
#

        .text
        .globl  main

main:   li      $v0, 4          # print out the first prompt
        la      $a0, out1
        syscall
        
        li      $v0, 5          # gets first num
        syscall
        move    $t0, $v0        # and moves it to $t0

        li      $v0, 4          # print out the second prompt
        la      $a0, out2
        syscall

        li      $v0, 5          # gets second num
        syscall
        move    $t1, $v0        # and moves it to $t1

        li      $t2, 0          # clearing $t2 (home of result)
        mult    $t0, $t1        # checking result before changing registers
        mflo    $t3             # assuming results are <=32 bits for simplicity

while:  andi    $t4, $t0, 1     # t4 has 0 on even, 1 on odd
        beqz    $t4, shift      # skip if num1 / 2^n is even
        nop
        addu    $t2, $t2, $t1   # otherwise, add num2 * 2^n to result
shift:  srl     $t0, $t0, 1     # num1 /= 2
        sll     $t1, $t1, 1     # num2 *= 2
        bgtz    $t0, while      # goes while num1 != 0, since num1 is unsigned
        nop

        li      $v0, 4          # print out the shift result text
        la      $a0, done1
        syscall

done:   li      $v0, 10
        syscall

#
# Data segment
#
        .data
out1:   .asciiz "\nEnter the first number: "
out2:   .asciiz "\nEnter the second number: "
done1:  .asciiz "\nThe result from shifting: "
done2:  .asciiz "\nThe real result: "
# End of file