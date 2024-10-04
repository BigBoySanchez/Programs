#
# Assign6Ex3.asm
#
# Jacob Ativo
# 11/22
# Takes string with spaces and letters
# and capitalizes the first letter in each word
# 
# Settings: Bare Machine OFF, Allow Pseudo Instructions ON, 
# 	    Load Exception File OFF, Delayed Branches ON, 
# 	    Delayed Loads ON, Mapped IO OFF
# 
# Register Use:
# $t0 --- string pointer
# $t1 --- holds char in string
# $t2 --- previous char is space
# $t3 --- holds 'A' or 'Z' for comparisons
#

	.data
pre:	.asciiz	"Original string: "
post:	.asciiz "\nModified string: "
string: .asciiz "george Bush   Doesn t care about  Black   people"

	.text
	.globl	main

main:	la	$a0, pre						# print pre text
	li	$v0, 4
	syscall

	la	$a0, string						# print unmodified string
	li	$v0, 4
	syscall

	la	$t0, string						# make pointer to string
	li	$t2, 1							# flag is set whenever previous char is space
	
	# loop that does main function of program
loop:	lb	$t1, ($t0)						# hold the current char, say c
	nop
	addiu	$t1, $t1, -32						# if c is a space or NUL, $t1 <= 0. else if c is a letter, $t1 > 0
	blez	$t1, notL						# branch if c not a letter
	nop
	beqz	$t2, next						# ignore letter if $t2 is not set
        li	$t2, 0							# since this char is a letter and flag isn't used until next loop
        li      $t3, 'A'                                                # load 'A'
        blt     $t1, $t3, next                                          # ignore numbers smaller than 'A'
        li      $t3, 'Z'                                                # load 'Z'
        bgt     $t1, $t3, next                                          # ignore numbers bigger than 'Z'
        nop
	sb	$t1, ($t0)						# store modified letter

next:	addiu	$t0, $t0, 1						# increment pointer
	j	loop							# loop again
	nop

	# happens when c is not a letter
notL:	addiu	$t1, $t1, 32						# returns c to its original value
	beqz	$t1, done						# breaks when c is NUL
	li	$t2, 1							# sets space flag
	j	next							# increment and loop
	nop

done:	la	$a0, post						# print preamble to modified string
	li	$v0, 4
	syscall

	la	$a0, string						# print modified string
	li	$v0, 4
	syscall

	li	$v0, 10
	syscall