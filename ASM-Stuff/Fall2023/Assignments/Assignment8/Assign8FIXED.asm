#
# Assign8.asm
#
# Jacob Ativo
# Using an Exception handler to to Lab8
#
# Settings: Bare Machine OFF, Allow Pseudo Instructions ON, 
# 	    Load Exception File OFF, Delayed Branches OFF, 
# 	    Delayed Loads OFF, Mapped IO ON
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

	lw	$t0, currD								# push currDisp							
	sw	$t0, ($sp)
	addiu	$sp, $sp, -4
	
	# is reciever ready?
	mfc0	$t0, $13								# move cause register into $t0
	andi	$t0, $t0, 0x800								# mask reciever ready bit
	beqz	$t0, skipR								# skip reciever code if not ready

	# get user's character change display appropriately. saves key pressed in userK
	addiu	$sp, $sp, 4								# pop to currDisp

	li	$t0, 0xffff0000								# base of memory-mapped IO area
	
	lw	$t1, ($t0)
	
	li	$t2, 0
	lb	$t2, 4($t0)								# return value if smth was read
	sw	$t2, userK								# store last char pressed into userK

	li	$t1, 'a'
	bne	$t2, $t1, case2								# display source normally
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
	bne	$t2, $t1, fall
	jal	reverse
	nop

fall:	addiu	$sp, $sp, 8								# move sp back to og spot
	j	skipT

	# did transmitter interrupt?
skipR:	mfc0	$t0, $13								# move cause register into $t0
	andi	$t0, $t0, 0x400								# mask transmitter ready bit
	beqz	$t0, skipT								# skip transmitter code if not ready

	# print char
	li	$t0, 0xffff0000								# base of memory-mapped IO area

	lw	$t1, 4($sp)								# load currDisp
	lb	$t2, ($t1)								# load next character of string
	sw	$t2, 12($t0)								# write character to display

	# change currDisp appropriately
	addiu	$sp, $sp, 4								# pop currDisp
	lw	$t0, ($sp)								
	addiu	$t0, $t0, 1								# and increment to next char

	lb	$t1, ($t0)								# load char at currDisp

	addiu	$sp, $sp, 0								# move pointer back to og position
	bnez	$t1, newP								# store incremented pointer if not NUL

	addiu	$sp, $sp, 4								# pop base of disp
	lw	$t0, ($sp)
	addiu	$sp, $sp, -4								# "push" base of disp

newP:	sw	$t0, currD								# store base of display/currDisp+1
	sw	$t0, ($sp)
	addiu	$sp, $sp, 8								# move pointer back to og position

	j	skipT

	# display = source
norm:	addiu	$sp, $sp, -8
	sw	$ra, ($sp)								# push $ra
	addiu	$sp, $sp, -4

	sw	$fp, ($sp)								# push $fp
	addiu	$sp, $sp, -4

	move	$fp, $sp								# initialize fp

	addiu	$sp, $sp, 20								# pop base of disp
	lw	$t0, ($sp)

	addiu	$sp, $sp, 4								# pop base of source
	lw	$t1, ($sp)

copyM:	lb	$t2, ($t1)								# get char at source
	sb	$t2, ($t0)								# and store it in disp

	addiu	$t0, $t0, 1								# increment pointers
	addiu	$t1, $t1, 1

	bnez	$t2, copyM								# get another char until NUL is stored

	addiu	$sp, $fp, 4								# move $sp back to top
	lw	$fp, ($sp)								# pop fp

	addiu	$sp, $sp, 4								# pop ra
	lw	$ra, ($sp)

	addiu	$sp, $sp, 8
	
	jr	$ra									# return to caller

	# toggle case in display
tog:	addiu	$sp, $sp, -8
	sw	$ra, ($sp)								# push $ra
	addiu	$sp, $sp, -4

	sw	$fp, ($sp)								# push $fp
	addiu	$sp, $sp, -4

	move	$fp, $sp								# initialize
											
	lw	$t0, 20($fp)								# get base of disp

copyT:	lb	$t1, ($t0)								# get char at disp

	li	$t2, 'A'
	blt	$t1, $t2, inc								# char is too small

	li	$t2, 'Z'
	bgt	$t1, $t2, betwn								# check if char is between upper and lowercase chars

valid:	xori	$t1, $t1, 32								# return to original value
	sb	$t1, ($t0)								# store toggled char in disp

inc:	addiu	$t0, $t0, 1								# increment pointer
	
	bnez	$t1, copyT								# get another char until NUL is stored

	addiu	$sp, $sp, 4								# pop fp
	lw	$fp, ($sp)

	addiu	$sp, $sp, 4								# pop sp
	lw	$ra, ($sp)

	addiu	$sp, $sp, 8								# move sp back to original spot

	jr	$ra									# return to caller

betwn:	li	$t2, 'a'
	blt	$t1, $t2, inc								# char invalid, between upper and lowercase chars
	nop

	li	$t2, 'z'
	bgt	$t1, $t2, inc								# char too big
	nop
	
	j	valid									# char is good
	nop

	# sort function
sort:
	li	$t0, 0
	
checkSize:
	lb	$t1, display($t0)							# Find newl, work with string length - newline char
	nop
	beq	$t1, 10, pivot								# newline will be added back later. this is to ensure newl doesnt get sorted
	nop
	addiu	$t0, $t0, 1
	j	checkSize
	nop
pivot:
	move	$t9, $t0
	addiu	$t2, $t0, -1								# $t9 = pos of newl, $t2 = characters we are working with
	li	$t0, 0
	
outerL:
	beq	$t0, $t2, done2								# if outer loop = length, jump to done2
	li	$t3, 0									# init inner loop
	

innerL:
	bge	$t3, $t2, continue							# continue to outer loop if the inner loop reaches length

	lb	$t5, display($t3)							# load current char into $t5
	addiu	$t3, $t3, 1								# go to next char

	lb	$t6, display($t3)							# $t6 = next char

	ble	$t5, $t6, nswap								# if sorted, do not swap
	
	sb	$t5, display($t3)							# else, swap
	addiu	$t3, $t3, -1
	sb	$t6, display($t3)
	
nswap:
	addiu	$t4, $t4, 1								# continue to next iteration of inner
	j	innerL

continue:
	addiu	$t0, $t0, 1								# iterate the outer loop, jump to outer.
	j	outerL

done2:
	li	$t8, '\n'								# $t8 = newl
	sb	$t8, display($t9)							# store newl back into string using $t9 as a pointer
	
	jr	$ra									# return to caller

	# reverses anything in display (shoutout zoheb)
reverse:	
	li	$t0, 0
checkSizeR:
	lb	$t1, display($t0)							# Find newl, work with string length - newline char
	beq	$t1, 10, pivotR								# newline will be added back later. this is to ensure newl doesnt get sorted
	addiu	$t0, $t0, 1
	j	checkSizeR
	
pivotR:
	move	$t9, $t0
	addiu	$t2, $t0, -1
	li	$t0, 0
loopRR:
	lb	$t3, display($t0)							# start
	lb	$t4, display($t2)							# end
	sb	$t4, display($t0)
	sb	$t3, display($t2)
	addiu	$t0, $t0, 1
	addiu	$t2, $t2, -1
	
	bge	$t0, $t2, nextSteps
	j	loopRR

nextSteps:
	li	$t5, '\n'
	sb	$t5, display($t9)

	jr	$ra

skipT:	

	# pop registers that were be used by handler
	addiu	$sp, $sp, 4
	lw	$t9, ($sp)
	addiu	$sp, $sp, 4
	lw	$t8, ($sp)
	addiu	$sp, $sp, 4
	lw	$t6, ($sp)
	addiu	$sp, $sp, 4
	lw	$t5, ($sp)
	addiu	$sp, $sp, 4
	lw	$t4, ($sp)
	addiu	$sp, $sp, 4
	lw	$t3, ($sp)
	addiu	$sp, $sp, 4
	lw	$t2, ($sp)
	addiu	$sp, $sp, 4
	lw	$t1, ($sp)
	addiu	$sp, $sp, 4
	lw	$t0, ($sp)

	# get $at back
	lw	$k1, tempAt								# load saved at into k1
	.set	noat									# allow use of at
	move	$at, $k1								# move it back into at
	.set	at									# allow use of at from pseudoinstructions

	eret										# return to main program

	.data
userK:	.word	0
source:	.asciiz	"F1fteen {}utsid3, b4by, | was actin' like a da/\/\ n thug I wanted to be just l!ke my brother\n"
display:.space	99									# bigger than source just in case
currD:	.word	0									# current char to be displayed

	.text
	.globl	main
main:	la	$t0, source								# make pointer to source
	sw	$t0, ($sp)								# push pointer as parameter
	addiu	$sp, $sp, -4

	la	$t0, display								# do the same for display
	sw	$t0, ($sp)
	addiu	$sp, $sp, -4

	sw	$t0, currD								# initialize currD

	jal	norma									# copy source to display
	nop

	mfc0	$t0, $12								# get bit pattern in status
	ori	$t0, $t0, 0xc01								# turn on global enable bit, transmitter, reciever
	mtc0	$t0, $12								# put int modified bit pattern

	li	$t0, 0xffff0000								# load reciever control register
	lw	$t1, ($t0)
	ori	$t1, $t1, 2								# turn on enable bit
	sw	$t1, ($t0)								# put new bit pattern in register

	# do the same for transmitter
	li	$t0, 0xffff0008
	lw	$t1, ($t0)
	ori	$t1, $t1, 2
	sw	$t1, ($t0)

	# check if 'q' was pressed
mLoop:	lw	$t0, userK
	li	$t1, 'q'

	bne	$t0, $t1, mLoop								# loop while 'q' isn't pressed

	addiu	$sp, $sp, 8								# move sp to og spot
	
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