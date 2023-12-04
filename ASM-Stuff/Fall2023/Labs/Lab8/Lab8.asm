#
# Lab8.asm
# 
# Jacob Ativo
# [function]
#
# Settings: Bare Machine OFF, Allow Pseudo Instructions ON, 
# 	    Load Exception File OFF, Delayed Branches ON, 
# 	    Delayed Loads ON, Mapped IO ON
#
# NOTES:
# do NOT use syscall
# source is a string (min len 60)
# size display > source
# set up display completely b4 printing
# can u exit from a subroutine?
# 
# PSEUDOCODE:

# MAIN:
## load addr of source and disp
## push both onto stack as parameters

## WHILE:
### call inPol
### break if retVal = quitVal
### push inPol retVal
### call outPol
### pop inPol retVal
## END WHILE:

## bring $sp back to beginning ("pop")
## exit
# END MAIN:



# SUBS:
## default
### set pointer into source
### set pointer into disp
### load *sourP
### store *dispP
### copy NUL too
### stop after
### return to main

## sorted

## toggle

## reverse

## INPOL (get input)
### li	$a3, 0xffff0000		# base of memory-mapped IO area
### load 0 into return
### load read control (offset 0)
### check if ready

### IF it is:
#### extract character otherwise (offset 4)
#### put byte into return
### END IF:

### return to caller
## END INPOL:


## outPol (call proper function and print char)
### go to char parameter
### load char parameter
### call respective function
### print char
### return "printed \n"
## END OUTPOL:

## delay?

	.data
source:	.asciiz	"Fifteen outside, baby, I was actin' like a damn thug I wanted to be just like my brother\n"
display:.space	99									# bigger than source just in case

	.text
	.globl	main
main:	la	$t0, source								# make pointer to source
	sw	$t0, ($sp)								# push pointer as parameter
	addiu	$sp, $sp, -4

	la	$t0, display								# do the same for display
	sw	$t0, ($sp)
	addiu	$sp, $sp, -4

	jal	norm									# get default display
	nop

	la	$t0, display								# push currDisp							
	sw	$t0, ($sp)
	addiu	$sp, $sp, -4

mLoop:	jal	inP									# poll input
	nop

	li	$t0, 'q'								# load q for comparison
	beq	$t0, $v0, quit								# quit if 'q' was pressed
	nop

	sw	$v0, ($sp)								# push input otherwise
	addiu	$sp, $sp, -4
	
	jal	outP									# poll output
	nop
	beqz	$v0, skip								# WIP
	addiu	$sp, $sp, 4								# pop to currDisp

	addiu	$sp, $sp, 8								# pop to base of disp
	lw	$t0, ($sp) 
	addiu	$sp, $sp, -4
	sw	$t0, ($sp)								# push base of display
	addiu	$sp, $sp, -4


skip:	jal	delay									# WIP
	nop

	j	mLoop									# poll input and output again
	nop

quit:	addiu	$sp, $sp, 12								# pop entire stack
	li	$v0, 10
	syscall

	# will not call another function
inP:	li	$t0, 0xffff0000								# base of memory-mapped IO area
	
	lw	$t1, ($t0)								# load ???
	nop
	andi	$t1, $t1, 1								# $t1 = ready bit
	beqz	$t1, ret1								# skip load word if input is not ready
	
	li	$v0, 0									# default return value
	lb	$v0, 4($t0)								# return value if smth was read (WIP FOR SCIENCE)

ret1:	jr	$ra									# return to main
	nop

	# WILL call another function
	# parameters: bases, currDisp, input
outP:	sw	$ra, ($sp)								# push return address
	addiu	$sp, $sp, -4

	sw	$fp, ($sp)
	addiu	$sp, $sp, -4								# push frame pointer (WIP might change later)

	addiu	$sp, $sp, 12								# load input
	lw	$t0, ($sp)
	addiu	$sp, $sp, 4								# pass bases as parameter

	li	$t1, 'a'
	bne	$t0, $t1, prin								# skip if not 'a'
	jal	norm									# display source normally
	nop										# WIP sp at currDisp

prin:	li	$t0, 0xffff0000								# base of memory-mapped IO area

	lw	$t1, 8($t0)								# load ???
	nop
	andi	$t1, $t1, 1								# $t1 = ready bit
	beqz	$t1, ret2								# skip load word if input is not ready
	li	$v0, 0									# assumes '\n' didn't print

	lw	$t1, ($sp)								# load currDisp
	nop
	lb	$t2, ($t1)								# load next character of string

	addiu	$t1, $t1, 1								# increment currDisp
	sw	$t1, ($sp)

	li	$t1, '\n'
	seq	$v0, $t1, $t2								# return "printed '\n'"
	sw	$t2, 12($t0)								# write character to display

ret2:	addiu	$sp, $sp, -12							
	lw	$fp, ($sp)								# pop fp
	
	addiu	$sp, $sp, 4
	lw	$ra, ($sp)								# pop ra
	nop

	jr	$ra									# return to main
	nop

	# display = source
norm:	addiu	$sp, $sp, 4								# pop base of disp
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

	addiu	$sp, $sp, -8								# move $sp back to original spot
	jr	$ra									# return to caller
	nop

delay:	li	$t0, 99
	nop
dLoop:	addiu	$t0, $t0, -1
	nop
	bgez	$t0, dLoop
	nop
	nop
	nop
	nop
	nop
	nop
	nop

	jr	$ra									# return
	nop