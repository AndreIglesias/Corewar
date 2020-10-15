	.name "loop"

main:
	ld %0, r1			# i
	ld %1, r2			# 1 unit steps
	ld %255, r3			# for 255 iterations

	ld %256, r16		# 100000000
loop:
	live %0
	add r1, r2, r1		# r1++
	aff r1
	sub r16, r3, r4		# diff
	add r4, r1, r4		# diff += i
	and r4, r16, r5		# diff & 100000000 -> 0 except 100000000
	zjmp %:loop
