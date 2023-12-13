#
# Assign8.asm
#
# Jacob Ativo
# [function]
#
# Settings: Bare Machine OFF, Allow Pseudo Instructions ON, 
# 	    Load Exception File OFF, Delayed Branches OFF, 
# 	    Delayed Loads OFF, Mapped IO OFF
#

# Exception handler WIP
	.kdata
tempAt:	.word	0	# space for $at from main

	.ktext	0x80000180


	eret


	.data
source:	.asciiz	"t.\n"								# WIP smaller array for testing
# source:	.asciiz	"Fifteen outside, baby, I was actin' like a damn thug I wanted to be just like my brother\n"
display:.space	99									# bigger than source just in case
userK:	.byte	0

	.text
	.globl	main
main:	la	$t0, source								# make pointer to source
	sw	$t0, ($sp)								# push pointer as parameter
	addiu	$sp, $sp, -4

	la	$t0, display								# do the same for display
	sw	$t0, ($sp)
	addiu	$sp, $sp, -4

	jal	norm									# copy source to display
	nop

	# display = source
	# using real-world linkage
norm:	sw	$ra, ($sp)								# push return address
	addiu	$sp, $sp, -4

	sw	$fp, ($sp)								# push frame pointer
	addiu	$sp, $sp, -4

	move	$fp, $sp								# initialize fp

	addiu	$sp, $sp, 12								# pop base of disp
	lw	$t0, ($sp)

	addiu	$sp, $sp, 4								# pop base of source
	lw	$t1, ($sp)
	nop

copyN:	lb	$t2, ($t1)								# get char at source
	nop
	sb	$t2, ($t0)								# and store it in disp

	addiu	$t0, $t0, 1								# increment pointers
	addiu	$t1, $t1, 1

	bnez	$t2, copyN								# get another char until NUL is stored
	nop

	addiu	$sp, $sp, -12								# "push" sp to fp in stack
	lw	$fp, ($sp)								# pop fp

	addiu	$sp, $sp, 4								# pop ra
	lw	$ra, ($sp)

	jr	$ra									# return to caller
	nop

# PSEUDOCODE:


# main:
## copy source to disp
## enable interrupts
### ori $12, $12, 110000000001
### ori reciever control (0xFFFF0000) with 1?

## LOOP:
### load is q
### break if set
## END LOOP:

