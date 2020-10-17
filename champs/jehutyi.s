.name "jehutyi"

	# r1 i
	# r2 "for" steps
	# r3 number of iterations
	# r4 diff used for the condition
	# r5 temporary storage to change carry
	# r16 number to enable condition to exit

main:

loader1:	sti r1, %:loop, %1
loader2:	sti r1, %:back_wall, %1
loader3:	sti r1, %:wall, %1
	sti r2, %:loader1, %0
	sti r2, %:loader2, %0
	sti r2, %:loader3, %0

	ld %0, r1			# i
	ld %1, r2			# 1 unit steps
	ld %255, r3			# for 255 iterations
	ld %14, r8
	ld %256, r16		# 0b100000000
loop:
	live %0
	add r1, r2, r1		# r1++
	aff r1
	fork %:wall
	fork %:back_wall
	sub r16, r3, r4		# diff
	add r4, r1, r4		# diff += i
	and r4, r16, r5		# diff & 0b100000000 -> 0 except 0b100000000
	zjmp %:loop
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
	st	r2, -465
	st	r2, -472
	st	r2, -478
	st	r2, -482
	st	r2, -492
	and r1, %0, r6
	zjmp	%:wall
back_wall:
	aff r1
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
	st	r8,402
	st	r8,406
	st	r8,410
	st	r8,414
	st	r8,420
	st	r8,422
	st	r8,426
	st	r8,430
	st	r8,434
	st	r8,438
	st	r8,442
	st	r8,446
	st	r8,450
	st	r8,454
	st	r8,458
	st	r8,462
	st	r8,466
	st	r8,470
	st	r8,474
	st	r8,478
	st	r8,482
	st	r8,486
	st	r8,490
	st	r8,494
	st	r8,498
	ld	%0,r15
	and r1, %0, r6
	zjmp %:back_wall
