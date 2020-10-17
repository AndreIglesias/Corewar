.name "jehutyi"

	# r1 i
	# r2 "for" steps
	# r3 number of iterations
	# r4 diff used for the condition
	# r5 temporary storage to change carry
	# r16 number to enable condition to exit

main:
	sti r1, %:loop, %1
	sti r1, %:wall, %1
	ld %0, r1			# i
	ld %1, r2			# 1 unit steps
	ld %255, r3			# for 255 iterations
	ld %14, r8
	ld %256, r16		# 0b100000000
loop:
	live %0
	add r1, r2, r1		# r1++
	aff r1
	sub r16, r3, r4		# diff
	add r4, r1, r4		# diff += i
	and r4, r16, r5		# diff & 0b100000000 -> 0 except 0b100000000
	zjmp %:back_wall
wall:
	live	%0
	st	r2, -37
	st	r2, -46
	st	r2, -55
	st	r2, -64
	st	r2, -73
	st	r2, -82
	st	r2, -91
	st	r2, -100
	st	r2, -109
	st	r2, -118
	st	r2, -127
	st	r2, -136
	st	r2, -145
	st	r2, -154
	st	r2, -163
	st	r2, -172
	st	r2, -181
	st	r2, -190
	st	r2, -199
	st	r2, -208
	st	r2, -217
	st	r2, -226
	st	r2, -235
	st	r2, -244
	st	r2, -253
	st	r2, -262
	st	r2, -271
	st	r2, -280
	st	r2, -289
	st	r2, -298
	st	r2, -307
	st	r2, -316
	st	r2, -325
	st	r2, -334
	st	r2, -343
	st	r2, -352
	st	r2, -361
	st	r2, -370
	st	r2, -379
	st	r2, -388
	st	r2, -397
	st	r2, -406
	st	r2, -415
	st	r2, -424
	st	r2, -433
	st	r2, -442
	st	r2, -451
	st	r2, -460
	st	r2, -478
	st	r2, -487
	st	r2, -496
	st	r2, -505
	st	r2, -511
	fork	%:main
	zjmp	%:wall
back_wall:
	live	%0
	st	r8,400
	st	r8,404
	st	r8,408
	st	r8,412
	st	r8,416
	st	r8,420
	st	r8,424
	st	r8,428
	st	r8,432
	st	r8,436
	st	r8,440
	st	r8,444
	st	r8,448
	st	r8,452
	st	r8,456
	st	r8,460
	st	r8,464
	st	r8,468
	st	r8,472
	st	r8,476
	st	r8,480
	st	r8,484
	st	r8,488
	st	r8,492
	st	r8,496
	st	r8,500
	st	r8,504
	st	r8,508
	st	r8,512
	st	r8,516
	st	r8,520
	st	r8,524
	st	r8,528
	st	r8,532
	st	r8,536
	st	r8,540
	st	r8,544
	st	r8,518
	st	r8,522
	st	r8,526
	st	r8,530
	st	r8,534
	st	r8,538
	st	r8,542
	st	r8,546
	st	r8,550
	st	r8,554
	st	r8,558
	st	r8,562
	ld	%0,r15
	fork	%:wall
	zjmp	%:back_wall
