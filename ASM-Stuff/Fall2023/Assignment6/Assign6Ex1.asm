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
# 

	.data
string:	.asciiz "ABCDEFG"
pre:	.asciiz	"Original string: "
post:	.asciiz	"Modified string: "
lf:	.asciiz	"\n"					# line feed

	.text
	.globl	main

main:	la	$a0, pre				# print preamble to original string
	li	$v0, 4
	syscall

	la	$a0, string				# print original string
	li	$v0, 4
	syscall

	la	$a0, lf					# print newline
	li	$v0, 4
	syscall

	la	$t0, string				# make pointer for string
loop:	lb	$t1, ($t0)				# load char at $t0 into $t1
	nop						# wait for it to pull up
	beqz	$t1, done				# break when $t0 points to '\0'
	nop
	addiu	$t1, $t1, 32				# b/c lowercase letters are 32 away from uppercase
	sb	$t1, ($t0)				# change char into new value
	addiu	$t0, $t0, 1				# increment pointer by sizeof(char) (1 byte)
	j	loop					# go again
	nop

done:	la	$a0, post				# print preamble to modified string
	li	$v0, 4
	syscall

	la	$a0, string				# print new string
	li	$v0, 4
	syscall

	li	$v0, 10
	syscall