#
# Lab7.asm
# 
# Jacob Ativo
# Takes an int from the user, n (n >= 1) and 
# adds the squares of all ints from 1 to n
# 
# Settings: Bare Machine OFF, Allow Pseudo Instructions ON, 
# 	    Load Exception File OFF, Delayed Branches ON, 
# 	    Delayed Loads ON, Mapped IO OFF
#
# Register Use:
# WIP
#

	.data
prompt:	.asciiz	"Enter an int (value is at least 1): "	# prompt user for a valid integer
post:	.asciiz	"SumInts of n is m"			# tells user the result of SumInts

	.text
	.globl	main

main:	la	$a0, prompt				# print prompt
	li	$v0, 4
	syscall

	li	$v0, 5
	syscall

	sw	$v0, ($sp)
	addiu	$sp, $sp, -4

	addiu	$sp, $sp, 4				# science WIP
	lw	$t0, ($sp)
	
	li	$v0, 10
	syscall