#
# Assign6Ex1.asm
#
# Jacob Ativo
# 11/21
# Takes in an all uppercase
# string with only letters
# and prints string in lowercase
#
# Settings: Bare Machine OFF, Allow Pseudo Instructions ON, 
# 	    Load Exception File OFF, Delayed Branches ON, 
#	    Delayed Loads ON, Mapped IO OFF
#
# Register Use:
# $t0 --- string ptr
# $t1 --- char from str
# $t2 --- '\n'
# 

	.data
pr1:	.asciiz	"\nEnter all uppercase string: "	# Asks user for string
echo:	.asciiz	"You typed: "				# goes before echo
lower:	.asciiz "Your new string is: "			# goes before lowercase string
lf:	.asciiz	"\n"					# line feed
str:	.space	128					# holds string before and after modification

	.text
	.globl	main

main:	la	$a0, pr1				# print prompt
	li	$v0, 4
	syscall

	la	$a0, str				# read string
	li	$a1, 127				# TODO: figure out what this does
	li	$v0, 8
	syscall

	la	$a0, echo				# print echo text
	li	$v0, 4
	syscall

	la	$a0, str				# echo user's string
	li	$v0, 4
	syscall

	la	$a0, lf					# print newline
	li	$v0, 4
	syscall

	la	$t0, str				# make pointer for string
	li	$t2, '\n'				# holds newline for comparison later
loop:	lb	$t1, ($t0)				# load char at $t0 into $t1
	nop						# wait for it to pull up
	beq	$t1, $t2, done				# break when $t0 points to '\n'
	nop
	addiu	$t1, $t1, 32				# b/c lowercase letters are 32 away from uppercase
	sb	$t1, ($t0)				# change char into new value
	addiu	$t0, $t0, 1				# increment pointer by sizeof(char) (1 byte)
	j	loop					# go again
	nop

done:	sb	$zero, ($t0)				# changes the newline in str to a NUL
	la	$a0, lower				# print lowercase text
	li	$v0, 4
	syscall

	la	$a0, str				# print new string
	li	$v0, 4
	syscall

	li	$v0, 10
	syscall