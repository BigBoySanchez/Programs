#
# Assign5Ex2.asm
#
# Jacob Ativo
# 11/14
# Finds the nth sum of
# the harmonic series
#
# Settings: Load delays ON; Branch delays ON, Pseudoinstructions ON   
#
# Register use:
# $f0 --- n
# $f1 --- 1
# $f2 --- denominator
# $f3 --- term
# $f12 -- answer
#
	.data
pr1:	.asciiz	"\nEnter the number of terms: "
bad:	.asciiz "Please try again.\n"
ans:	.asciiz "The sum is: "

	.text
	.globl	main

main:	la	$a0, pr1			# prints prompt for n
	li	$v0, 4
	syscall

	li	$v0, 5				# reads user's choice for n
	syscall
	bltz	$v0, badIn

badIn:	la	$a0, bad			# prints error text
	li	$v0, 4
	syscall
	j	main				# and tries again
	nop

	mtc1	$v0, $f0			# moves valid input to $f0
	li.s	$f1, 1				# loads 1 into $f1
	li.s	$f2, 1				# loads 1 into the denominator
	li.s	$f12, 0				# clears register holding answer

sum:	div.s	$f3, $f1, $f2			# term = 1 / denominator
	add.s	$f2, $f2, $f1			# denominator += 1.0
	add.s	$f12, $f12, $f3			# answer += term
	bleu	$f2, $f0, sum			# loops if denominator <= n
	nop

	la	$a0, ans			# printing answer text
	li	$v0, 4
	syscall

	li	$v0, 2				# prints sum
	syscall

	li	$v0, 10				# exit like a boss
	syscall

# End of file