#
# AtivoAssign1Ex1.asm
#
# Jacob Ativo
# 09/12/23
# puts 1010... into $t1
#

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

## End of file