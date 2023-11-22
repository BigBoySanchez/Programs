#
# Assign6Ex2.asm
#
# Jacob Ativo
# 11/21
# Takes string with spaces and letters
# and capitalizes the first letter in each word
# 
# Settings: Bare Machine OFF, Allow Pseudo Instructions ON, 
# 	    Load Exception File OFF, Delayed Branches ON, 
# 	    Delayed Loads ON, Mapped IO OFF
# 

	.data
pre:	.asciiz	"Original string: "
post:	.asciiz "\nModified string: "
string: .asciiz "in a  hole in the    ground there lived a hobbit"

	.text
	.globl	main

main:	la	$a0, pre						# print pre text
	li	$v0, 4
	syscall

	la	$a0, string						# print unmodified string
	li	$v0, 4
	syscall

	la	$t0, string						# make pointer to string
	lb	$t1, ($t0)						# to hold current char, say c
	nop

loop:	beqz	$t1, done						# exit if c is NUL
	nop
	addiu	$t0, $t0, 1						# increment pointer
	lb	$t2, string						# load char after c


