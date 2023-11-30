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
prompt:	.asciiz	"Enter an integers: "	# prompts user for integer
arr:    .space	40			# space for 10 ints

	.text
	.globl	main

main:	li	$t0, 10			# store remaining number of ints
	la	$t1, prompt		# load address of prompt into $t1

subL:	sw	$t0, ($sp)		# push $t0 (for use later)
	addiu	$sp, $sp, -4		
	sw	$t1, ($sp)		# pass address of prompt as an argument
	addiu	$sp, $sp, -4
	