#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    cinnamon-blackhole.s                               :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/04 16:46:05 by ciglesia          #+#    #+#+#+#+#+#      #
#                                                                              #
#******************************************************************************#

.name "cinnamon blackhole"
.comment "cannelle..."

	# r2 i
	# r3 "for" steps

	# r5 diff used for the condition
	# r6 temporary storage to change carry -------------
	# r7 how far to write (+)
	# r8 steps for writing lower
	# r9 how far to write (-)
	# r10 steps for writing upper

	# constants
		# r4 number of iterations
		# r12 live_attack(IDX_MOD)
		# r13 upper_wall(IDX_MOD)
		# r14 four
		# r15 zero
		# r16 number to enable condition to exit

main:
	ld %57675775, r15
								# init loops & lives (erased with upper_wall)
	sti r1, %:loop, %1				# 7 bytes (0b 68 01 00 73 00 01)
	sti r1, %:upper_wall, %1		# 14 bytes
	sti r1, %:live_attack, %1		# 21 bytes
	sti r1, %:middle_live, %1		# 28 bytes
	sti r1, %:jumps, %1				# 35 bytes

	sti r15, %:main, %0				# erase
	sti r15, %:main, %7				# erase
	sti r15, %:main, %14			# erase
	sti r15, %:main, %21			# erase
	sti r15, %:main, %28			# erase

								# starting point lower wall
	ld %:live_attack, r2
	ld %:main, r7
	sub r7, r2, r7				# position to start painting (end - live_attack)
	ld %2, r2
	sub r7, r2, r7				# sub 2 bytes

								# starting point upper wall
	ld %:upper_wall, r2
	ld %:main, r9
	sub r9, r2, r9				# position to start painting (main - upper_wall)
	ld %28, r2
	add r9, r2, r9				# add 28 bytes of loaders

	# init variables and constants
	ld %1, r3					# 1 unit steps "for"
	#ld %500, r4					# for 255 iterations
	ld %170, r13				# 330 for 83 iterations upper_wall
	ld %-2, r10					# positions(painting) upper_wall
	ld %4, r14					# constant

	ld %512, r16				# 0b100000000
	and r1, %0, r6
	zjmp %:loop

live_attack:						# r7 = (end - live_attack)
	live %0
	ldi %7, %0, r15
	st r15, -256
	st r15, -256
	st r15, -256
	st r15, -256
	st r15, -256
	st r15, -256
	st r15, -256
	st r15, -256
	st r15, -256
	st r15, -256
	st r15, -256
	st r15, -256
	st r15, -256
	st r15, -256
	st r15, -256
	st r15, -256
	st r15, -256

jumps:
	live %0
	ld %655010, r11
	st r11, -345
	st r10, -344
	lfork %-850
	and r1, %0, r6
	lfork %-400
	zjmp %:jumps

loop:
	live %0
		add r2, r3, r2				# r1++
		fork %:attack
		fork %:live_attack
		fork %:upper_wall
		fork %:middle_live
		#sub r16, r4, r5				# diff = 512(0b1000000000) - 25
		#add r5, r2, r5				# diff += i
		#and r5, r16, r6				# when (diff & 0b100000000) -> carry = 0
		and r1, %0, r6
		zjmp %:loop
	#and r1, %0, r6
	#zjmp %:live_attack

upper_wall:						# r9 = (main - upper_wall)
	live %0
		sti r15, r9, r10			# line 1 (-2)
		sub r10, r14, r10			# r10 -= 4
		sub r16, r13, r5			# diff = 512(0b1000000000) - 330
		sub r5, r10, r5				# diff += i
		and r5, r16, r6				# when (diff & 0b100000000) -> carry = 0
		fork %:middle_live
	zjmp %:upper_wall
	ld %-2, r10					# positions(painting) upper_wall
	and r1, %0, r6
	fork %:middle_live
	zjmp %:upper_wall

middle_live:
	live %0
	zjmp %:middle_live

attack:
	ldi %7, %0, r2
	st r2, 256
	st r2, 256
	st r2, 256
	st r2, 256
	st r2, 256
	st r2, 256
	st r2, 256
	st r2, 256
	st r2, 256
	st r2, 256
	st r2, 256
	st r2, 256
	st r2, 256
	st r2, 256
	st r2, 256
	st r2, 256
	st r2, 256
	st r2, 256
	st r2, 256
	st r2, 256
	st r2, 256
	st r2, 256
	st r2, 256
	st r2, 256
	st r2, 256
	st r2, 256
	st r2, 256
	st r2, 256
	st r2, 256
	st r2, 256
	st r2, 256
	st r2, 256
	st r2, 256
	st r2, 256
	st r2, 256
	st r2, 256
	st r2, 256
	st r2, 256
	st r2, 256
	st r2, 256
	st r2, 256
	st r2, 256
	st r2, 256
	st r2, 256
	st r2, 256
	st r2, 256
	st r2, 256
	st r2, 256
	st r2, 256
	st r2, 256
	st r2, 256

end:
