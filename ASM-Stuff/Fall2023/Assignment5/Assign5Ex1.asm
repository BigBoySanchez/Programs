#
# Assign5Ex1.asm
#
# Jacob Ativo
# 11/14
# Evaluates an arithmetic expression
# with 2 floating point variables
#
# Settings: Load delays ON; Branch delays ON, Pseudoinstructions ON
# 

        .data
prX:    .asciiz "\nEnter a value for x: "
prY:    .asciiz "\nEnter a value for y: "
ans:    .asciiz "\nThe result is: "

        .text
        .globl  main

main:   la      $a0, prX                    # print the x prompt
        li      $v0, 4
        syscall

        li      $v0, 6                      # reads x as a single float
        syscall
        mov.s   $f1, $f0                    # and moves it to $f1 to make room for y

        la      $a0, prY                    # print the y prompt
        li      $v0, 4
        syscall

        li      $v0, 6                      # reads y as a single float
        syscall

exit:   li      $v0, 10
        syscall          

