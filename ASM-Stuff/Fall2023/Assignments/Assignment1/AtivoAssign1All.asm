	.text
	.globl	main

main:	ori	$t0, $zero, 0x01	# put one into $t0
	sll	$t1, $t0, 0x02 
	or	$t1, $t1, $t0		# or with $t1 to make alternating pattern
	sll	$t2, $t1, 0x04		# shift left by (num bits in $t1)+1 & store in $t2
	or	$t2, $t2, $t1		# or to keep alternating pattern
	sll	$t1, $t2, 0x08		# repeat shift & or til num leading 0's is 1
	or	$t1, $t1, $t2
	sll	$t2, $t1, 0x10
	or	$t2, $t2, $t1
	sll	$t1, $t2, 0x01		# gets rid of leading 0
	ori	$t0, $zero, 1		# put one into $t0
	sll	$t1, $t0, 3
	or	$t1, $t1, $t0		# make a "0x9"
	sll	$t1, $t1, 2
	or	$t1, $t1, $t0
	sll	$t1, $t1, 1
	or	$t1, $t1, $t0
	sll	$t1, $t1, 1		# add a "0x6" to the end of the "0x9"
	sll	$t2, $t1, 8
	or	$t1, $t1, $t2		# duplicate "0x96" to make "0x9696"
	sll	$t2, $t1, 16
	or	$t1, $t1, $t2		# duplicate "0x9696" to make "0x96969696"
	ori	$t0, $zero, 1		# put one into $t0
	nor	$t1, $t0, $t0		# makes all ones EXCEPT last digit
	or	$t1, $t1, $t0		# puts 1 into the last digit

##
