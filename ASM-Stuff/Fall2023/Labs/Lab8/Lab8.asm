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
# source:	.asciiz	"t.\n"								# WIP smaller array for testing
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
	nop										## WIP change function call for testing

	la	$t0, display								# push currDisp							
	sw	$t0, ($sp)
	addiu	$sp, $sp, -4

mLoop:	jal	inP									# poll input
	nop

	li	$t0, 'q'								# load q for comparison
	beq	$t0, $v0, quit								# quit if 'q' was pressed
	nop
	
	jal	outP									# poll output
	nop
	beqz	$v0, skip								# keep currDisp if nothing printed
	nop

	addiu	$sp, $sp, 4								# pop currDisp
	lw	$t0, ($sp)								
	nop
	addiu	$t0, $t0, 1								# and increment to next char

	lb	$t1, ($t0)								# load char at currDisp
	nop

	bnez	$t1, newP								# store incremented pointer if not NUL
	nop

	addiu	$sp, $sp, 4								# pop base of disp
	lw	$t0, ($sp)
	addiu	$sp, $sp, -4								# "push" base of disp

newP:	sw	$t0, ($sp)								# push base of display/currDisp+1
	addiu	$sp, $sp, -4


skip:	jal	delay									# delay if too fast
	nop

	j	mLoop									# poll input and output again
	nop

quit:	addiu	$sp, $sp, 12								# pop entire stack
	li	$v0, 10
	syscall

	# WIP will not call another function
	# poll input and change display appropriately. returns key pressed
inP:	sw	$ra, ($sp)								# push return address
	addiu	$sp, $sp, -4

	addiu	$sp, $sp, 8								# pop to currDisp

	li	$t0, 0xffff0000								# base of memory-mapped IO area
	
	lw	$t1, ($t0)								# WIP load ???
	nop
	andi	$t1, $t1, 1								# $t1 = ready bit
	beqz	$t1, ret1								# skip load word if input is not ready
	
	li	$v0, 0									# default return value
	lb	$v0, 4($t0)								# return value if smth was read (WIP FOR SCIENCE)

	li	$t1, 'a'
	bne	$v0, $t1, case2								# display source normally
	jal	norm									
	nop

case2:	li	$t1, 't'								# toggle case
	bne	$v0, $t1, case3
	jal	tog
	nop

case3:	li	$t1, 's'								# sort display
	bne	$v0, $t1, case4
	jal	sort
	nop

	## HENRY DELETE COMMENTS
case4:	# li	$t1, 'r'
	# bne	$v0, $t1, ret1
	# jal	sort
	# nop

ret1:	addiu	$sp, $sp, -4								# push to ra
	lw	$ra, ($sp)								# get ra to main
	nop


	jr	$ra									# return to main
	nop

	# WIP WILL call another function
	# poll output, print, and return "output successful"
outP:	li	$t0, 0xffff0000								# base of memory-mapped IO area

	lw	$t1, 8($t0)								# WIP load ???
	nop
	andi	$v0, $t1, 1								# will return ready bit
	beqz	$v0, ret2								# skip load word if output is not ready
	nop

	lw	$t1, 4($sp)								# load currDisp
	nop
	lb	$t2, ($t1)								# load next character of string
	nop
	sw	$t2, 12($t0)								# write character to display

ret2:	jr	$ra									# return to main
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

	# display = case-toggled source
tog:	addiu	$sp, $sp, 4								# pop base of disp
	lw	$t0, ($sp)

	addiu	$sp, $sp, 4								# pop base of source
	lw	$t1, ($sp)
	nop

copyT:	lb	$t2, ($t1)								# get char at source
	nop
	xori	$t2, $t2, 32								# toggle case

	li	$t3, 'A'
	blt	$t2, $t3, inc

	li	$t3, 'Z'
	bgt	$t2, $t3, betwn

valid:	sb	$t2, ($t0)								# store toggled char in disp

inc:	addiu	$t0, $t0, 1								# increment pointers
	addiu	$t1, $t1, 1

	xori	$t2, $t2, 32								# return to original value
	bnez	$t2, copyT								# get another char until NUL is stored
	nop

	j	ret3
	nop

betwn:	li	$t3, 'a'
	blt	$t2, $t3, inc

	li	$t3, 'z'
	ble	$t2, $t3, valid
	nop

ret3:	addiu	$sp, $sp, -8								# move $sp back to original spot
	jr	$ra									# return to caller
	nop

# Sort function
# Find length
# Find position of newl
# Sort based off length - 1 (-1 is to get rid of new line)
# Save length so we can add newl later
# Basic bubble sorting routine
# Store sorted string back into display
# Jump register ($ra)
# Done. 

## always do lb and sb when checking chars (chars = 1 byte)
## stack pointer is working fine
## he wants us to load the bases from the stack but idk if he cares

sort:

	li	$t0, 0				# Loading 0 for pointer / counter in $t0.
	li	$t3, 0				# $t3 will hold the the size of length. 
	la	$a0, source			# Load address into $a0.

	# find length by traversing until newline
	
checkIt:
	lb	$t2, source($t3)		# checkIt will determine where the newline is, so we can sort the string seperate from the newline.
	nop
	addiu	$t3, $t3, 1
	beq	$t2, 10, pivot
	nop
	j	checkIt				# We save the length to add the newline back at the appropriate index.
	nop
	
pivot:	move	$t4, $t3			# Copy the position of newline to $t4.
	addiu	$t3, $t3, -1			# Decrement $t3 by 1 to get length of string.
	

outerL:
	bge	$t0, $t3, doneO			# Basic bubble sort routine, sorts string based off ascii values and stores into display label.
	nop

	li	$t5, 0				#  swap flag
	li	$t1, 0				#  pointer

	subu	$t3, $t3, $t0

inner:
	bge	$t3, $t0, doneI
	nop

	lb	$t2, source($t0)		# Current char
	nop
	addiu	$t0, $t0, 1			# Increment

	lb	$t6, source($t0)		# Next char
	nop

	bge	$t2, $t6, nextIt		# If in correct order already, continue to the next iteration.
	nop

	sb	$t2, display($t0)		# Store lower ascii value.
	nop

	addiu	$t0, $t0, -1			# Decrement

	sb	$t6, display($t0)		# Store greater ascii value.
	nop
	
	li	$t5, 1				# Flag = true.

doneO:
	addu	$t3, $t3, $t0
	beqz	$t5, doneI			# If flag = false, exit
	nop

	j	outer				# Jump to outer loop.
	nop
nextIt:
	j	inner				# Jump to inner loop.
	nop

doneI:
	li	$t9, '\n'			# Add back newline to sorted array
	sb	$t9, display($t4)		# $t4 contains position of last character.
	nop

	jr	$ra				# Back to caller
	nop

# delay polls if needed
delay:	li	$t0, -9
dLoop:	addiu	$t0, $t0, -1
	bgez	$t0, dLoop
	nop

	jr	$ra									# return
	nop