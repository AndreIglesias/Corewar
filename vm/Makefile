#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/20 19:19:55 by ciglesia          #+#    #+#              #
#    Updated: 2020/09/12 18:08:51 by ciglesia         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME		=	../corewar

INC			=	./include/
INC2		=	../libft/include/
INC3		=	../include/
INCLUDE		=	-I $(INC) -I $(INC2) -I $(INC3)
INC_LIB		=	-L../libft/ -lft -lncurses

DIRSRC		=	./src/
DIRCOMP		=	./src/computer-system/
DIRINTF		=	./src/interface/
DIRLOAD		=	./src/loading/
DIRPARSE	=	./src/parsing/
DIROP		=	./src/op/
DIRVALID	=	./src/validation/

SRC			=	vm_main.c
COMPUTER_S	=	vm_init.c debug.c run_cpu.c
INTERFACE	=	ncurses_init.c arena.c
LOADING		=	load.c load_input.c players.c load_ram.c
PARSING		=	byte_management.c logical_management.c disect_args.c
OP			=	op.c op1_5.c op6_10.c op11_15.c aff.c op_cmpi.c
VALIDATION	=	input_param.c valid_param.c valid_exec.c

DIROBJ		=	./depo/

OAUX		=	$(SRC:%=$(DIROBJ)%) $(COMPUTER_S:%=$(DIROBJ)%) $(INTERFACE:%=$(DIROBJ)%) $(LOADING:%=$(DIROBJ)%) $(PARSING:%=$(DIROBJ)%) $(OP:%=$(DIROBJ)%) $(VALIDATION:%=$(DIROBJ)%)
DEPS		=	$(OAUX:.c=.d)
OBJS		=	$(OAUX:.c=.o)

ifdef FLAGS
	ifeq ($(FLAGS), no)
CFLAGS		=
	endif
	ifeq ($(FLAGS), debug)
CFLAGS		=	-Wall -Wextra -Werror -ansi -pedantic -g
	endif
else
CFLAGS		=	-Wall -Wextra -Werror
endif

CC			=	/usr/bin/gcc
RM			=	/bin/rm -f
ECHO		=	/bin/echo -e

%.o		:		../$(DIRSRC)/%.c
				$(CC) $(CFLAGS) $(INCLUDE) -MMD -o $@ -c $<

%.o		:		../$(DIRCOMP)/%.c
				$(CC) $(CFLAGS) $(INCLUDE) -MMD -o $@ -c $<

%.o		:		../$(DIRINTF)/%.c
				$(CC) $(CFLAGS) $(INCLUDE) -MMD -o $@ -c $<

%.o		:		../$(DIRLOAD)/%.c
				$(CC) $(CFLAGS) $(INCLUDE) -MMD -o $@ -c $<

%.o		:		../$(DIRPARSE)/%.c
				$(CC) $(CFLAGS) $(INCLUDE) -MMD -o $@ -c $<

%.o		:		../$(DIROP)/%.c
				$(CC) $(CFLAGS) $(INCLUDE) -MMD -o $@ -c $<

%.o		:		../$(DIRVALID)/%.c
				$(CC) $(CFLAGS) $(INCLUDE) -MMD -o $@ -c $<


$(NAME)	:		$(OBJS)
				@$(CC) $(INCLUDE) $(CFLAGS) -o $(NAME) $(OBJS) $(INC_LIB)
				@$(ECHO) '> Compiled'

clean	:
				@($(RM) $(OBJS))
				@($(RM) $(DEPS))
				@$(ECHO) '> Directory cleaned'

all		:		$(NAME)

fclean	:		clean
				@$(RM) $(NAME)
				@$(ECHO) '> Remove executable'

re		:		fclean all

.PHONY	:		all clean re

-include $(DEPS)
