#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    cinnamon-rolls.s                                   :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/04 16:46:05 by ciglesia          #+#    #+#+#+#+#+#      #
#                                                                              #
#******************************************************************************#

.name "Cinnamon-rolls"
.comment "cannelle..."

main:
	sti r1, %:live, %1
live:
	live %0
	ld %:main, r3
	ld %64, r4
	sub r3, r4, r5
	sti r5, %:fork, %1
fork:
	lfork %:main
	#and r1, %0, r2
	#zjmp %:main
	#aff r1
