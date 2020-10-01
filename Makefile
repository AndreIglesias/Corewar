#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/20 22:37:03 by ciglesia          #+#    #+#              #
#    Updated: 2020/09/27 17:14:26 by ciglesia         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

DEPENDENCIES = Makefile libft/Makefile vm/Makefile assembler/Makefile disassembler/Makefile

ECHO		=	/bin/echo -e

.SUFFIXES:

all:	$(DEPENDENCIES)
		@$(MAKE) -C libft/
		@$(MAKE) -C vm/
		@$(MAKE) -C assembler/
		@$(MAKE) -C disassembler/

clean:
		@$(MAKE) -C libft/ clean
		@$(MAKE) -C vm/ clean
		@$(MAKE) -C assembler/ clean
		@$(MAKE) -C disassembler/ clean

fclean:	clean
		@$(MAKE) -C libft/ fclean
		@$(MAKE) -C vm/ fclean
		@$(MAKE) -C assembler/ fclean
		@$(MAKE) -C disassembler/ fclean

re:
		@echo "Recompiling"
		@$(MAKE) fclean
		@$(MAKE) all

.PHONY: clean fclean all re
