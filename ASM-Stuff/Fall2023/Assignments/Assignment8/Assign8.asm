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
tempAt:	.word	0									# space for $at from main

	.ktext	0x80000180

	# store $at ASAP
	.set	noat									# get access to $at
	move	$k1, $at								# move it out
	.set	at									# allow use of $at by pseudo
	sw	$k1, tempAt								# save it for later

	# save registers that'll be used by handler
	sw	$t0, ($sp)
	addiu	$sp, $sp, -4
	sw	$t1, ($sp)
	addiu	$sp, $sp, -4
	sw	$t2, ($sp)
	addiu	$sp, $sp, -4
	sw	$t3, ($sp)
	addiu	$sp, $sp, -4
	sw	$t4, ($sp)
	addiu	$sp, $sp, -4
	sw	$t5, ($sp)
	addiu	$sp, $sp, -4
	sw	$t6, ($sp)
	addiu	$sp, $sp, -4
	sw	$t8, ($sp)
	addiu	$sp, $sp, -4
	sw	$t9, ($sp)
	addiu	$sp, $sp, -4

	# push bases of strings as parameters
	la	$t0, source								# make pointer to source
	sw	$t0, ($sp)								# push pointer as parameter
	addiu	$sp, $sp, -4

	la	$t0, display								# do the same for display
	sw	$t0, ($sp)
	addiu	$sp, $sp, -4

	la	$t0, display								# push currDisp							
	sw	$t0, ($sp)
	addiu	$sp, $sp, -4
	
	
	# is reciever ready?
	mfc0	$t0, $13								# move cause register into $t0
	andi	$t0, $t0, 0x800								# mask reciever ready bit
	beqz	$t0, skipR								# skip reciever code if not ready

	# get user's character change display appropriately. returns key pressed
	addiu	$sp, $sp, 4								# pop to currDisp

	li	$t0, 0xffff0000								# base of memory-mapped IO area
	
	lw	$t1, ($t0)								# WIP load ???
	
	li	$t2, 0									# default return value
	lb	$t2, 4($t0)								# return value if smth was read

	li	$t1, 'a'
	bne	$v0, $t1, case2								# display source normally
	jal	norm									
	nop

case2:	li	$t1, 't'								# toggle case
	bne	$t2, $t1, case3
	jal	tog
	nop

case3:	li	$t1, 's'								# sort display
	bne	$t2, $t1, case4
	jal	sort
	nop

case4:	li	$t1, 'r'								# reverse display
	bne	$t2, $t1, ret1
	jal	reverse
	nop

	addiu	$sp, $sp, -4								# move sp back to og spot

	# did reciever interrupt?
skipR:	mfc0	$t0, $13								# move cause register into $t0
	andi	$t0, $t0, 0x400								# mask transmitter ready bit
	beqz	$t0, skipT								# skip transmitter code if not ready

	


	eret


	.data
userK:	.byte	0
source:	.asciiz	"t.\n"									# WIP smaller array for testing
# source:	.asciiz	"Fifteen outside, baby, I was actin' like a damn thug I wanted to be just like my brother\n"
display:.space	99									# bigger than source just in case

	.text
	.globl	main
main:	la	$t0, source								# make pointer to source
	sw	$t0, ($sp)								# push pointer as parameter
	addiu	$sp, $sp, -4

	la	$t0, display								# do the same for display
	sw	$t0, ($sp)
	addiu	$sp, $sp, -4

	jal	norma									# copy source to display
	nop

	mfc0	$t0, $12								# get bit pattern in status
	ori	$t0, $t0, 0xC01								# turn on enable bit, transmitter, reciever
	mtc0	$t0, $12								# put int modified bit pattern

	# check if 'q' was pressed
mLoop:	lb	$t0, userK
	li	$t1, 'q'

	bne	$t0, $t1, mLoop								# loop while 'q' isn't pressed

	li	$v0, 10									# exit swag style
	syscall

	# display = source
	# using real-world linkage
norma:	sw	$ra, ($sp)								# push return address
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

