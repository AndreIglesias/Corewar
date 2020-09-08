/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:18:22 by ciglesia          #+#    #+#             */
/*   Updated: 2020/09/08 14:49:01 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "libft.h"
# include "op.h"

typedef struct		s_file
{
	int				fd;
	char			*name;
	char			*comment;
	char			*playername;
	unsigned char	code[CHAMP_MAX_SIZE];
}					t_file;

int					valid_input(char *filename, t_file *file);
int					correct_syntax(t_file *file, char *line, int l, int s);
void				file_init(t_file *file);
int					is_head(char ** cmd, char *str);
int					is_label(char **cmd);
int					is_opcode(char **cmd, int i);

#endif
