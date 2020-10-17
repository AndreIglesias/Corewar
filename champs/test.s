.name "name"
.comment "comment"
label:
	live %0
	ld %10, r2
	ld %:label, r2
	st r2, r3
	st r2, 23
	add r1, r2, r4
	sub r1, r2, r4
	and r1, r2, r4
	and 32, :label, r4
	and %344, %:label, r4
	or r1, r2, r4
	or 32, :label, r4
	or %23, %:label, r4
	xor r1, r2, r4
	xor 32, :label, r4
	xor %32, %:label, r4
	zjmp %23
	ldi r2, %:label, r4
	ldi :label, %3, r4
	ldi %324, r5, r4
	sti r3, r4, %33
	sti r3, 24, %:label
	sti r3, %:label, r4
	fork %:label
	lld 16532, r4
	lld %:label, r4
	lldi r2, %14, r5
	lldi 324, r4, r5
	lldi %:label, %:label, r5
	lfork %231
	aff r2
