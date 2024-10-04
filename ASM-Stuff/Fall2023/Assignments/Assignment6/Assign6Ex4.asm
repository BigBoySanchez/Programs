#
# Assign6Ex4.asm
#
# Jacob Ativo
# 11/25
# Toggles the case of letters
# in a string
#
# Settings: Bare Machine OFF, Allow Pseudo Instructions ON, 
# 	    Load Exception File OFF, Delayed Branches ON, 
# 	    Delayed Loads ON, Mapped IO OFF
#
# Register Use:
# $t0 --- '\n'
# $t1 --- string pointer
# $t2 --- holds chars from string
#

	.data
prompt:	.asciiz	"\nEnter a string (letters & spaces only): "	# asks user for string
buf:	.space	999						# space to hold the string

	.text
	.globl	main

main:	la	$a0, prompt					# print prompt
	li	$v0, 4
	syscall

	la	$a0, buf					# load buffer address
	li	$a1, 998						# set length of buffer
	li	$v0, 8						# get string
	syscall

	la	$t1, buf					# $t1 is pointer for string
	li	$t0, '\n'					# store newline in $t0

	# loop that goes thru string, toggling case of each char
tog:	lb	$t2, ($t1)					# load char at pointer into $t2
	nop							# wait for it to pull up
	beq	$t2, $t0, done					# break if char at pointer is newline
	xori	$t2, $t2, 32					# toggles 2^5 bit, which determines case.
	beqz	$t2, next					# if $t2 = 32 (value of space) turns into 0 after xori
	nop							# wait for branch result
	sb	$t2, ($t1)					# store modified char (doesnt happen on space)
next:	addiu	$t1, $t1, 1					# move pointer to next char
	j	tog						# do same thing to next char
	nop							# wait for jump

done:	lb	$zero, ($t1)					# changes newline in string to NUL

	la	$a0, buf					# print modified string
	li	$v0, 4
	syscall

	li	$v0, 10						# exit
	syscall