#
# AtivoAssign1Ex2.asm
#
# Jacob Ativo
# 09/17/23
# puts 10010110... into $t1
#

	.text
	.globl	main

main:	ori	$t0, $zero, 1	# put one into $t0
	sll	$t1, $t0, 3
	or	$t1, $t1, $t0	# make a "0x9"
	sll	$t1, $t1, 2
	or	$t1, $t1, $t0
	sll	$t1, $t1, 1
	or	$t1, $t1, $t0
	sll	$t1, $t1, 1	# add a "0x6" to the end of the "0x9"
	sll	$t2, $t1, 8
	or	$t1, $t1, $t2	# duplicate "0x96" to make "0x9696"
	sll	$t2, $t1, 16
	or	$t1, $t1, $t2	# duplicate "0x9696" to make "0x96969696"

## End of file