#
# Assign6Ex6.asm
#
# Jacob Ativo
# 11/27
# Reverses an array of integers and
# prints that reversed array
# 
# Settings: Bare Machine OFF, Allow Pseudo Instructions ON, 
# 	    Load Exception File OFF, Delayed Branches ON, 
# 	    Delayed Loads ON, Mapped IO OFF
#
# Register Use:
# WIP
#

	.data
arr:	.space	40							# set space for 10 ints
prompt:	.asciiz	"Enter 10 integers (press enter after each input): "	# prompts user for integers
tab:	.asciiz "	"						# tab
lf:	.asciiz	"\n"							# linefeed

	.text
	.globl	main

main:	la	$a0, prompt						# print prompt
	li	$v0, 4
	syscall

	la	$t0, arr						# load pointer for arr into $t0
	addiu	$t1, $t0, 36						# $t1 holds address of the last slot in arr (add (10-1) * sizeof(int))

	# stores user's ints into arr
read:	li	$v0, 5							# read integer into $v0
	syscall

	move	$t2, $v0						# temporarily store user's int in $t2 (can't store v register)
	sw	$t2, ($t0)						# store user's int into address at pointer
	addiu	$t0, $t0, 4						# increment pointer to next int
	ble	$t0, $t1, read						# read in another int if pointer is in arr
	nop

	la	$t0, arr						# move pointer back to start of arr
	la	$a0, lf							# print newline
	li	$v0, 4
	syscall
	
	# prints user's ints in order
outN:	lw	$a0, ($t0)						# print int at pointer
	li	$v0, 1
	syscall

	addiu	$t0, $t0, 4						# increment pointer to next int
	bgt	$t0, $t1, done1						# break if last int of arr has been printed
	la	$a0, tab						# print tab otherwise
	li	$v0, 4
	syscall

	j	outN							# print next int in arr
	nop

done1:	la	$t0, arr						# move pointer back to the beginning


revrs:	lw	$t2, ($t0)
	lw	$t3, ($t1)
	sw	$t2, ($t1)
	sw	$t3, ($t0)

	addiu	$t1, $t1, -4
	addiu	$t0, $t0, 4
	blt	$t0, $t1, revrs
	nop

	la	$t0, arr
	addiu	$t1, $t0, 36
	la	$a0, lf							# print newline
	li	$v0, 4
	syscall
	
	# prints user's reversed ints
outR:	lw	$a0, ($t0)						# print int at pointer
	li	$v0, 1
	syscall

	addiu	$t0, $t0, 4						# increment pointer to next int
	bgt	$t0, $t1, done2						# break if last int of arr has been printed
	la	$a0, tab						# print tab otherwise
	li	$v0, 4
	syscall

	j	outR							# print next int in arr
	nop

done2:	la	$a0, lf							# print newline
	li	$v0, 4
	syscall

	li	$v0, 10							# exit
	syscall