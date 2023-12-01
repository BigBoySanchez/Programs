#
# Jacob Ativo
# Sorts an array of ints from user
# 
# Settings: Bare Machine OFF, Allow Pseudo Instructions ON, 
# 	    Load Exception File OFF, Delayed Branches ON, 
# 	    Delayed Loads ON, Mapped IO OFF
#
# Register Use:
# WIP
#

        .data
prompt:	.asciiz	"Enter an integer: "	# prompts user for integer
arr:    .word	0			# space for 10 ints
	.space	36

	.text
	.globl	main

main:	la	$a0, prompt		# $a0 = address of prompt
	la	$a1, arr		# $a1 = address of arr
	addiu	$t0, $a1, 36		# $t0 = end of array

subL:	jal	read			# go into read subroutine
	nop
	sw	$v0, ($a1)
	addiu	$a1, $a1, 4
	ble	$a1, $t0, subL
	nop

	la	$a0, arr		# pass the address of arr as an argument
	jal	sort
	nop


read:	li	$v0, 4			# print prompt
	syscall

	li	$v0, 5			# read int into $v0
	syscall

	jr	$ra			# return control to main
	nop

sort:	addiu	$a0, $a0, 4		# move pointer
	
sortL:	move	$s0, $a0
	
sortN:	blez	$s0, Ndone
	nop
	lw	$s2, ($s0)
	addiu	$s1, $s0, -4
	lw	$s3, ($s1)
	nop
	ble	$s3, $s2, Ndone
	nop
	sw	$s3, ($s0)
	sw	$s2, ($s1)

Ndone:	j	sortL
	nop