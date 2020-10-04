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
	and r1, %0, r2
fork:
	fork %-494
	ld %121345, r3
	sti r3, %:live, %1
	fork %494
	zjmp %:main



live:
