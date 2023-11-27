#
# Assign6Ex5.asm
#
# Jacob Ativo
# 11/26
# Takes an array of ints from user 
# finds largest and smallest values
#  
# Settings: Bare Machine OFF, Allow Pseudo Instructions ON, 
# 	    Load Exception File OFF, Delayed Branches ON, 
# 	    Delayed Loads ON, Mapped IO OFF
# 
# Register Use:
# WIP
#

	.data
prompt:	.asciiz	"\nEnter 10 integers (press enter after each input): "	# promting the user for int values
big:	.asciiz	"\nBiggest: "						# goes before biggest int
small:	.asciiz	"\nSmallest: "						# goes before smallest int
arr:	.word	0, 0, 0, 0, 0, 0, 0, 0, 0, 0				# space for 10 ints

	.text
	.globl	main

main:	la	$a0, prompt						# print prompt
	li	$v0, 4
	syscall

	la	$t0, arr						# load pointer for arr into $t0
	li	$t1, 10							# $t1 holds num of remaining inputs

	# put ints into arr using loop
read:	li	$v0, 5							# read user int
	syscall

	sw	$v0, ($t0)						# move int into arr
	addiu	$t0, $t0, 4						# increment pointer to next int
	addiu	$t1, $t1, -1						# one less input is needed
	bnez	$t1, read						# read more if more inputs are needed
	nop

	li	$v0, 10							# exit
	syscall