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
# Register use:
# $f0 --- y
# $f1 --- x
# $f2 --- 5.4xy
# $f3 --- -12.3y
# $f4 --- 18.23x
# $f12 -- answer
#

        .data
prX:    .asciiz "\nEnter a value for x: "
prY:    .asciiz "Enter a value for y: "
ans:    .asciiz "\nThe result is: "

        .text
        .globl  main

main:   la      $a0, prX                # print the x prompt
        li      $v0, 4
        syscall

        li      $v0, 6                  # reads x as a single float
        syscall
        mov.s   $f1, $f0                # and moves it to $f1 to make room for y

        la      $a0, prY                # print the y prompt
        li      $v0, 4
        syscall

        li      $v0, 6                  # reads y as a single float
        syscall

        li.s    $f3, 5.4                # loads 5.4 into $f3
        mul.s   $f2, $f0, $f1           # puts xy into $f2
        mul.s   $f2, $f2, $f3           # 5.4xy in $f2

        li.s    $f3, -12.3              # loads -12.3 into $f3
        mul.s   $f3, $f3, $f0           # -12.3y in $f3

        li.s    $f4, 18.23              # loads 18.23 in $f4
        mul.s   $f4, $f4, $f1           # 18.23x in $f4

        li.s    $f12, -8.23             # adding everything together
        add.s   $f12, $f12, $f4         # 18.23x - 8.23
        add.s   $f12, $f12, $f3         # - 12.3y + 18.23x - 8.23
        add.s   $f12, $f12, $f2         # 5.4xy - 12.3y + 18.23x - 8.23

        la      $a0, ans                # print answer prompt
        li      $v0, 4
        syscall

        li      $v0, 2                  # print floating point answer
        syscall                    

        li      $v0, 10
        syscall
# End of file          

