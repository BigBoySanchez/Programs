# 
# Assign7Ex1.asm
#
# Jacob Ativo
# Sorts an array of ints from user
# 
# Settings: Bare Machine OFF, Allow Pseudo Instructions ON, 
# 	    Load Exception File OFF, Delayed Branches ON, 
# 	    Delayed Loads ON, Mapped IO OFF
#

        .data
prompt:	.asciiz	"Enter an integer: "	# prompts user for integer
lf:	.asciiz	"\n"
arr:    .word	0			# space for 10 ints
	.space	36

	.text
	.globl	main

main:	la	$a0, prompt		# $a0 = address of prompt
	la	$a1, arr		# $a1 = address of arr
	addiu	$s0, $a1, 36		# $t0 = end of array

subL:	jal	read			# go into read subroutine
	nop
	sw	$v0, ($a1)
	addiu	$a1, $a1, 4
	ble	$a1, $s0, subL
	nop

	li	$a1, 36			# pass offset of last element in arr (length-1*sizeof(int))
	jal	sort			# sort arr from small to big
	nop
	jal	out			# print sorted arr
	nop
	li	$v0, 10			# exit
	syscall


	# prints array
out:	la	$t0, arr		# $t0 = pointer to arr
	addu	$t1, $t0, $a1		# $t1 = last element in arr

outL:	la	$a0, lf			# print newline
	li	$v0, 4
	syscall

	lw	$a0, ($t0)		# print int at pointer
	li	$v0, 1
	syscall

	addiu	$t0, $t0, 4		# increment pointer
	ble	$t0, $t1, outL		# break if pointer is outside arr
	nop

	jr	$ra			# leave subroutine


read:	li	$v0, 4			# print prompt
	syscall

	li	$v0, 5			# read int into $v0
	syscall

	jr	$ra			# return control to main
	nop
	
	# using bubble sort
sort:	li	$t0, 0			# num of sorted values*4

	
	# keeps track of sorted values
sortL:	bge	$t0, $a1, doneL		# break if sorted = 9
	nop
	li	$t4, 0			# swapped = false

	# moves largest unsorted int before previous sorted int
	li	$t1, 0			# second index
	subu	$a1, $a1, $t0		# $a1 = remaining unsorted
sortN:	bge	$t1, $a1, doneN		# break if sorted >= remaining unsorted
	nop

	# get value at index and value after
	lw	$t2, arr($t1)
	addiu	$t1, $t1, 4
	lw	$t3, arr($t1)
	nop

	ble	$t2, $t3, else		# swap iff element1 > element2
	nop
	sw	$t2, arr($t1)		# swap elements
	addiu	$t1, $t1, -4
	sw	$t3, arr($t1)
	li	$t4, 1			# set swapped to true

else:	j	sortN
	nop

doneN:	addu	$a1, $a1, $t0		# reset lastIndex to end of arr
	beqz	$t4, doneL		# break if nothing was swapped
	nop
	j	sortL
	nop

doneL:	jr	$ra
	nop