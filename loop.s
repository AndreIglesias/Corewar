	.name "loop"

	# r1 i
	# r2 "for" steps
	# r3 number of iterations
	# r4 diff used for the condition
	# r5 temporary storage to change carry
	# r16 number to enable condition to exit

main:
	ld %0, r1			# i
	ld %1, r2			# 1 unit steps
	ld %255, r3			# for 255 iterations

	ld %256, r16		# 0b100000000
loop:
	live %0
	add r1, r2, r1		# r1++
	aff r1
	sub r16, r3, r4		# diff
	add r4, r1, r4		# diff += i
	and r4, r16, r5		# diff & 0b100000000 -> 0 except 0b100000000
	zjmp %:loop
