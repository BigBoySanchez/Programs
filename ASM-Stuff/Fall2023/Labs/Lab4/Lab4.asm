# 
# Lab4.asm
#
# Jacob Ativo
# 10/10
# Writing control structures in MIPS
# 

        .text
        .globl  main

main:   ori     $t0, $zero, 0           # home of a
        ori     $t1, $zero, 0           # home of b
        ori     $t2, $zero, 10          # to hold the limit for the loop (10)
        
first:  bgeu    $t0, $t2, second        # start of while loop (ends when a >= 10)
        addu    $t1, $t1, $t0           # b += a
        addiu   $t0, $t0, 1             # a++
        j       first                   # goes back to start no matter what

second: ori     $t0, $zero, 0           # resetting variables
        ori     $t1, $zero, 0

do:     addu    $t1, $t1, $t0           # start of do-while (b += a)
        addiu   $t0, $t0, 1             # a++
        bltu    $t0, $t2, do            # loops again if a < 10

third:  ori     $t1, $zero, 0           # b is reset

        ori     $t0, $zero, 0           # a is set to 0 right before loop starts
for:    bgeu    $t0, $t2, fourth        # similar to while loop, goes to next fragment when a >= 10
        addu    $t1, $t1, $t0           # b += a
        addiu   $t0, $t0, 1             # a++
        j       for                     # goes back to start no matter what

fourth: ori     $t0, $zero, 0           # resetting a and b again
        ori     $t1, $zero, 0
        bgtu    $t0, $t1, endif         # skip body of if when a > b
        li      $t1, 10                 # b = 10 (only when a <= b)
endif:  j       fifth

fifth:  ori     $t0, $zero, 0           # resetting a and b
        ori     $t1, $zero, 0
        bgeu    $t0, $t1, else          # does else code when a >= b
        li      $t1, 10                 # b = 10 when a < b
        j       exit                    # skips over else block                 
else:   li      $t0, 20                 # a = 20 when a >= b

exit:   li      $v0, 10                 # exiting properly
        syscall 