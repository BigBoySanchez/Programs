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
	lb	$v0, 4($t0)								# return value if smth was read

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

case4:	li	$t1, 'r'								# reverse display
	bne	$v0, $t1, ret1
	jal	reverse
	nop

ret1:	addiu	$sp, $sp, -4								# push to ra
	lw	$ra, ($sp)								# get ra to main
	nop

	jr	$ra									# return to main
	nop

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
	nop

copyN:	lb	$t2, ($t1)								# get char at source
	nop
	sb	$t2, ($t0)								# and store it in disp

	addiu	$t0, $t0, 1								# increment pointers
	addiu	$t1, $t1, 1

	bnez	$t2, copyN								# get another char until NUL is stored
	nop

	addiu	$sp, $fp, 4								# move $sp back to top
	lw	$fp, ($sp)								# pop fp

	addiu	$sp, $sp, 4								# pop ra
	lw	$ra, ($sp)

	addiu	$sp, $sp, 8
	
	jr	$ra									# return to caller
	nop

	# toggle case in display
tog:	addiu	$sp, $sp, -8
	sw	$ra, ($sp)								# push $ra
	addiu	$sp, $sp, -4

	sw	$fp, ($sp)								# push $fp
	addiu	$sp, $sp, -4

	move	$fp, $sp								# initialize
											
	lw	$t0, 20($fp)								# get base of disp
	nop

copyT:	lb	$t1, ($t0)								# get char at disp

	li	$t2, 'A'
	blt	$t1, $t2, inc								# char is too small
	nop

	li	$t2, 'Z'
	bgt	$t1, $t2, betwn								# check if char is between upper and lowercase chars
	nop

valid:	xori	$t1, $t1, 32								# return to original value
	sb	$t1, ($t0)								# store toggled char in disp

inc:	addiu	$t0, $t0, 1								# increment pointer
	
	bnez	$t1, copyT								# get another char until NUL is stored
	nop

	addiu	$sp, $sp, 4								# pop fp
	lw	$fp, ($sp)

	addiu	$sp, $sp, 4								# pop sp
	lw	$ra, ($sp)

	addiu	$sp, $sp, 8								# move sp back to original spot

	jr	$ra									# return to caller
	nop

betwn:	li	$t2, 'a'
	blt	$t1, $t2, inc								# char invalid, between upper and lowercase chars
	nop

	li	$t2, 'z'
	bgt	$t1, $t2, inc								# char too big
	nop
	
	j	valid									# char is good
	nop

# Sort function (shoutout zoheb)
sort:
	li	$t0, 0
	
checkSize:
	lb	$t1, display($t0)		# Find newl, work with string length - newline char
	nop
	beq	$t1, 10, pivot			# newline will be added back later. this is to ensure newl doesnt get sorted
	nop
	addiu	$t0, $t0, 1
	j	checkSize
	nop
pivot:
	move	$t9, $t0
	addiu	$t2, $t0, -1			# $t9 = pos of newl, $t2 = characters we are working with
	li	$t0, 0
	
outerL:
	beq	$t0, $t2, done2			# if outer loop = length, jump to done2
	nop
	li	$t3, 0				# init inner loop
	

innerL:
	bge	$t3, $t2, continue		# continue to outer loop if the inner loop reaches length
	nop

	lb	$t5, display($t3)		# load current char into $t5
	nop
	addiu	$t3, $t3, 1			# go to next char

	lb	$t6, display($t3)		# $t6 = next char
	nop

	ble	$t5, $t6, nswap			# if sorted, do not swap
	nop
	
	sb	$t5, display($t3)		# else, swap
	nop
	addiu	$t3, $t3, -1
	sb	$t6, display($t3)
	nop
	
nswap:
	addiu	$t4, $t4, 1			#continue to next iteration of inner
	j	innerL
	nop
continue:
	addiu	$t0, $t0, 1			# iterate the outer loop, jump to outer.
	j	outerL
	nop
done2:
	li	$t8, '\n'			# $t8 = newl
	sb	$t8, display($t9)		# store newl back into string using $t9 as a pointer
	nop
	
	jr	$ra				# return to caller
	nop


	# reverses anything in display (shoutout zoheb)
reverse:	
	li	$t0, 0
checkSizeR:
	lb	$t1, display($t0)		# Find newl, work with string length - newline char
	nop
	beq	$t1, 10, pivotR			# newline will be added back later. this is to ensure newl doesnt get sorted
	nop
	addiu	$t0, $t0, 1
	j	checkSizeR
	nop	
pivotR:
	move	$t9, $t0
	addiu	$t2, $t0, -1
	li	$t0, 0
loopRR:
	lb	$t3, display($t0)		# start
	nop
	lb	$t4, display($t2)		# end
	nop
	sb	$t4, display($t0)
	nop
	sb	$t3, display($t2)
	nop
	addiu	$t0, $t0, 1
	addiu	$t2, $t2, -1
	
	bge	$t0, $t2, nextSteps
	nop
	j	loopRR
	nop
nextSteps:
	li	$t5, '\n'
	sb	$t5, display($t9)
	nop

	jr	$ra
	nop

# delay polls if needed
delay:	li	$t0, -9
dLoop:	addiu	$t0, $t0, -1
	bgez	$t0, dLoop
	nop

	jr	$ra									# return
	nop