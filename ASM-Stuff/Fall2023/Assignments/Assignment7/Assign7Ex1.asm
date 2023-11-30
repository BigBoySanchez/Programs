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
arr:    .word	40			# space for 10 ints

	.text
	.globl	main

main:	la	$a0, prompt		# $a0 = address of prompt
	la	$a1, arr		# $a1 = address of arr
	addiu	$t0, $a1, 36		# $t0 = end of array

subL:	jal	read			# go into read subroutine
	nop
	addiu	$a1, $a1, 4
	ble	$a1, $t0, subL
	nop

	li	$v0, 10
	syscall	


read:	li	$v0, 4			# print prompt
	syscall

	li	$v0, 5			# read int into $v0
	syscall

	sw	$v0, ($a1)
	jr	$ra			# return control to main
	nop