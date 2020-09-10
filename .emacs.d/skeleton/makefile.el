;******************************************************************************;
;                                                                              ;
;                                                         :::      ::::::::    ;
;    skeleton.el                                        :+:      :+:    :+:    ;
;                                                     +:+ +:+         +:+      ;
;    By: ppeltier <ppeltier@student.42.fr>          +#+  +:+       +#+         ;
;                                                 +#+#+#+#+#+   +#+            ;
;    Created: 2014/11/09 14:52:26 by ppeltier          #+#    #+#              ;
;    Updated: 2014/12/11 15:50:27 by ppeltier         ###   ########.fr        ;
;                                                                              ;
;******************************************************************************;

;; Makefiles's Skeleton
(define-skeleton create-makefile
  "Create a Makefile."
  ""
"\n"
"NAME		=	# Binary name\n"
"DIRSRC		=	. # ./path/to/sources/directorie/\n"
"DIROBJ		=	. # ./path/to/object/directorie/\n"
"INCLUDE		=	. # ./path/to/include/directorie/\n"
"SUB_MAKE	=	# ./path/to/sub/makefile/directorie/ (Put nothing if isn't)\n"
"INC_LIB		=	# -L./path/to/lib/directorie -lname\n"
"SRC			=	# Put your sources name\n"
"\n"
"OBJ			=	$(SRC:.c=.o)\n"
"OBJS		=	$(OBJ:%=$(DIROBJ)%)\n"
"\n"
"ifdef FLAGS\n"
"	ifeq ($(FLAGS), no)\n"
"CFLAGS		=\n"
"	endif\n"
"	ifeq ($(FLAGS), debug)\n"
"CFLAGS		=	-Wall -Wextra -Werror -ansi -pedantic -g\n"
"	endif\n"
"else\n"
"CFLAGS		=	-Wall -Wextra -Werror\n"
"endif\n"
"\n"
"CC			=	/usr/bin/gcc\n"
"RM			=	/bin/rm -f\n"
"ECHO		=	/bin/echo -e\n"
"\n"
"\n"
"$(NAME)	:		$(OBJ)\n"
"ifdef SUB_MAKE\n"
"				@(cd $(SUB_MAKE) && $(MAKE))\n"
"endif\n"
"				$(CC) $(INCLUDE) $(INC_LIB) $(CFLAGS) -o $(NAME) $(OBJS)\n"
"				@$(ECHO) '> Compiled'\n"
"\n"
"clean	:\n"
"				@(cd $(DIROBJ) && $(RM) $(OBJ))\n"
"ifdef SUB_MAKE\n"
"				@(cd $(SUB_MAKE) && $(MAKE) clean)\n"
"endif\n"
"				@$(ECHO) '> Directory cleaned'\n"
"\n"
"all		:		$(NAME)\n"
"\n"
"fclean	:		clean\n"
"ifdef SUB_MAKE\n"
"				@(cd $(SUB_MAKE) && $(MAKE) fclean)\n"
"endif\n"
"				-@$(RM) $(NAME)\n"
"				@$(ECHO) '> Remove executable'\n"
"\n"
"re		:		fclean all\n"
"\n"
".PHONY	:		all clean re\n"
"\n"
"%.o		:		$(DIRSRC)/%.c\n"
"				$(CC) $(INCLUDE) $(CFLAGS) -o $(DIROBJ)/$@ -c $<\n")
