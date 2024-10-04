#
# AtivoAssign1Ex3.asm
#
# Jacob Ativo
# 09/17/23
# puts all 1's into $t1
#

	.text
	.globl	main

main:	ori	$t0, $zero, 1	# put one into $t0
	nor	$t1, $t0, $t0	# makes all ones EXCEPT last bit
	or	$t1, $t1, $t0	# puts 1 into the last bit

## End of file