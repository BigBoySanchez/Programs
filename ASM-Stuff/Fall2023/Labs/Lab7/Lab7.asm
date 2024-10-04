#
# Lab7.asm
# 
# Jacob Ativo
# Takes an int from the user, n (n >= 1) and 
# adds the squares of all ints from 1 to n
# 
# Settings: Bare Machine OFF, Allow Pseudo Instructions ON, 
# 	    Load Exception File OFF, Delayed Branches ON, 
# 	    Delayed Loads ON, Mapped IO OFF
#

	.data
prompt:	.asciiz	"\n\nEnter int >=1 (<1 to quit): "
post1:	.asciiz	"SumInts of "				# reasonable descriptive text
post2:	.asciiz	" is "

	.text
	.globl	main
main:	la	$a0, prompt				# prompt for n
	li	$v0, 4
	syscall

	li	$v0, 5					# read int
	syscall

	blez	$v0, quit				# quit when n < 1
	nop

	# caller prolog for main
	sw	$v0, ($sp)				# push n (parameter for subroutine)
	addiu	$sp, $sp, -4
	
	jal	sum					# go into subroutine
	nop

	addiu	$sp, $sp, 4				# pop n into $t0
	sw	$t0, ($sp)
	move	$t1, $v0				# make way for syscall codes

	la	$a0, post1				# print first part of output
	li	$v0, 4
	syscall

	move	$a0, $t0				# print n
	li	$v0, 1
	syscall

	la	$a0, post2				# print next part of output
	li	$v0, 4
	syscall

	move	$a0, $t1				# print m
	li	$v0, 1
	syscall

	j	main
	nop

quit:	li	$v0, 10
	syscall

	# takes sum of squares from 1 to n
	# sub prolog
sum:	sw	$ra, ($sp)				# push return address
	addiu	$sp, $sp, -4

	sw	$fp, ($sp)				# push frame pointer
	addiu	$sp, $sp, -4

	addiu	$fp, $sp, -4				# need space for n-1
	move	$sp, $fp				# initialize $sp

	# add n^2 to sum(n-1)
	# sub body
	addiu	$sp, $sp, 16				# move sp to n in stack
	lw	$t0, ($sp)				# load n from stack
	li	$t1, 1
	ble	$t0, $t1, epi				# do another call if n > 1
	li	$v0, 1					# assume sum returns 1

	addiu	$t0, $t0, -1				# $t0 = n - 1

	# caller prolog for sub
	addiu	$sp, $fp, 4				# move sp to parameter spot
	sw	$t0, ($sp)				# push parameter
	addiu	$sp, $sp, -4

	jal	sum					# recursively call sum
	nop

	addiu	$sp, $sp, 4				# pop n-1 into $t0
	lw	$t0, ($sp)
	nop

	addiu	$t0, $t0, 1				# $t0 = n
	mult	$t0, $t0				# lo = n^2
	mflo	$t1					# $t1 = n^2
	addu	$v0, $v0, $t1				# $v0 = return value + n^2

	# sub epilog
epi:	addiu	$sp, $fp, 8				# pop old frame pointer
	lw	$fp, ($sp)

	addiu	$sp, $sp, 4				# pop return address
	lw	$ra, ($sp)
	nop

	jr	$ra					# go back to caller
	nop

# NOTES:
# real world
# DO NOT USE $ax FOR ARGS
# ignore overflow
#
# PSEUDOCODE:
# MAIN
## prompt for n
## store n
## call sumSq
## print "SumInts of n is m"
## jump to main while needed
## exit when done
# END MAIN
#
# SUMSQ
## load n from stack
## load a = 1
## IF n<=1
### jump to return
## END IF
## make n-1
## call sumSq(n-1)
## load n-1
## make n
## make n^2
## make a = n^2 + sumSq
## return a
# END SUMSQ