#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/20 19:19:55 by ciglesia          #+#    #+#              #
#    Updated: 2020/09/08 15:48:40 by ciglesia         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME		=	asm

INC			=	./include/
INC2		=	../libft/include/
INC3		=	../include/
INC4		=	../vm/include/
INCLUDE		=	-I $(INC) -I $(INC2) -I $(INC3) -I $(INC4)
INC_LIB		=	-L../libft/ -lft -lncurses

DIRSRC		=	./src/
DIRAN		=	./src/analysis/
DIRSYN		=	./src/synthesis/
DIROP		=	./src/op/
DIRVALID	=	./src/validation/

SRC			=	asm_main.c
ANALYSIS	=	file_init.c
SYNTHESIS	=
OP			=	op.c
VALIDATION	=	valid_file.c valid_syntax.c instruction_lexicon.c

DIROBJ		=	./depo/

OAUX		=	$(SRC:%=$(DIROBJ)%) $(ANALYSIS:%=$(DIROBJ)%) $(SYNTHESIS:%=$(DIROBJ)%) $(OP:%=$(DIROBJ)%) $(VALIDATION:%=$(DIROBJ)%)
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

%.o		:		../$(DIRAN)/%.c
				$(CC) $(CFLAGS) $(INCLUDE) -MMD -o $@ -c $<

%.o		:		../$(DIRSYN)/%.c
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