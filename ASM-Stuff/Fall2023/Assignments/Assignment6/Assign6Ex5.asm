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
	addiu	$t1, $t0, 36						# $t1 holds address of the end of arr (add (10-1) * sizeof(int))

	# put ints into arr using loop
read:	bgt	$t0, $t1, set						# break if $t0 is outside arr
	li	$v0, 5							# read user int
	syscall

	sw	$v0, ($t0)						# move int into arr
	addiu	$t0, $t0, 4						# increment pointer to next int
	j	read							# try reading another int
	nop

set:	la	$t0, arr						# move pointer back to beginning of arr
	lw	$t2, ($t0)						# will hold biggest int. default is first int in arr
	lw	$t3, ($t0)						# will hold smallest int. default is first int in arr

	# look for smallest and largest int in the array
find:	beq	$t0, $t1, done						# break if pointer is at last int in arr
	addiu	$t0, $t0, 4						# increment pointer to next int
	lw	$t4, ($t0)						# load int at the pointer temporarily in $t4
	nop
	bgt	$t4, $t2, newB						# change biggest int if pointer points to bigger int
	nop
	blt	$t4, $t3, newL						# change smallest int if pointer points to smaller int
	nop
	j	find							# loop again
	nop

newB:	move	$t2, $t4						# change biggest int into temp int
	j	find							# and check next int
	nop

newL:	move	$t3, $t4						# change smallest int into temp int
	j	find							# and check next int
	nop

	#print results
done:	la	$a0, small						# print small text
	li	$v0, 4
	syscall

	move	$a0, $t3						# print smallest int
	li	$v0, 1
	syscall

	la	$a0, big						# print big text
	li	$v0, 4
	syscall

	move	$a0, $t2						# print biggest int
	li	$v0, 1
	syscall

	li	$v0, 10							# exit
	syscall