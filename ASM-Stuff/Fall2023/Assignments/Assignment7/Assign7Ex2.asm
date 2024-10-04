#
# Assign7Ex2.asm
#
# Jacob Ativo
# Gives n! using recursion with real-world linkage convention
# 
# Settings: Bare Machine OFF, Allow Pseudo Instructions ON, 
# 	    Load Exception File OFF, Delayed Branches ON, 
# 	    Delayed Loads ON, Mapped IO OFF
#

	.data
prompt:	.asciiz	"\n\nEnter an int >= 0 (< 0 to quit): "
post:	.asciiz	"! is: "				# reasonable descriptive text

	.text
	.globl	main

main:	la	$a0, prompt				# print prompt for n
	li	$v0, 4
	syscall

	li	$v0, 5					# read n into $v0
	syscall

	bltz	$v0, done				# break if user wants to quit

	# caller prolog for main
	sw	$v0, ($sp)				# push n for use as argument
	addiu	$sp, $sp, -4
	jal	fact					# go into subroutine
	nop
	addiu	$sp, $sp, 4
	lw	$a0, ($sp)				# pop n for printing
	move	$t0, $v0				# make space for syscall codes

	li	$v0, 1					# print n
	syscall

	la	$a0, post
	li	$v0, 4
	syscall

	move	$a0, $t0				# print fact(n)
	li	$v0, 1
	syscall

	j	main

done:	li	$v0, 10
	syscall

	# sub prolog
fact:	sw	$ra, ($sp)				# push return address
	addiu	$sp, $sp, -4
	sw	$fp, ($sp)				# push frame pointer
	addiu	$sp, $sp, -4
	addiu	$fp, $sp, -4				# initialize $fp w/ space for local n-1
	move	$sp, $fp				# initialize $sp

	# doing factorial thru recursion
	addiu	$sp, $sp, 16				# access argument n in stack
	lw	$t0, ($sp)				# and keep in $t0
	li	$t1, 1
	ble	$t0, $t1, epi				# return 1 iff n <= 1
	li	$v0, 1
	addiu	$t0, $t0, -1				# make argument for recursive call (n-1)

	# caller prolog for fact
	addiu	$sp, $sp, -12				# move to space for variables
	sw	$t0, ($sp)				# push n-1 for use as argument
	addiu	$sp, $sp, -4
	jal	fact					# recursively call fact
	nop

	# get return value and restore argument
	addiu	$sp, $sp, 4				# pop n-1 back into $t0
	lw	$t0, ($sp)
	move	$t1, $v0				# i = fact(n-1)
	addiu	$t0, $t0, 1				# makes original n

	# create return value
	mult	$t0, $t1				# return i * n into $v0
	mflo	$v0

	# sub epilog
epi:	addiu	$sp, $fp, 4				# move sp before local variables
	addiu	$sp, $sp, 4				# pop $fp
	lw	$fp, ($sp)
	addiu	$sp, $sp, 4				# pop $ra
	lw	$ra, ($sp)
	nop
	jr	$ra					# return control to caller
	nop