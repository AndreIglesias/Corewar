#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/20 22:37:03 by ciglesia          #+#    #+#              #
#    Updated: 2020/09/05 15:14:18 by ciglesia         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

SUB_MAKEL	=	./libft/
SUB_MAKEVM	=	./vm/
SUB_MAKEC	=	./compiler/

ECHO		=	/bin/echo -e

clean	:
				@($(MAKE) clean -C $(SUB_MAKEL))
				@($(MAKE) clean -C $(SUB_MAKEVM))
				@$(ECHO) '> Directory cleaned'

all		:
				@($(MAKE) -C $(SUB_MAKEL))
				@($(MAKE) -C $(SUB_MAKEVM))

fclean	:		clean
				@($(MAKE) fclean -C $(SUB_MAKEL))
				@($(MAKE) fclean -C $(SUB_MAKEVM))
				@$(ECHO) '> Remove executable'

re		:		fclean all

.PHONY	:		all clean re
