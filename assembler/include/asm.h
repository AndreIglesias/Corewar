/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:18:22 by ciglesia          #+#    #+#             */
/*   Updated: 2020/09/13 20:56:56 by ciglesia         ###   ########.fr       */
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
	char			*labels[CHAMP_MAX_SIZE];
}					t_file;

typedef struct		s_code
{
	int				opcode;
	int				acb;
	int				reg;
	char			*dir;
	char			*ind;
	struct s_code	*next;
}					t_code;

void				file_init(t_file *file);

int					valid_input(char *filename, t_file *file);
int					valid_reg(char **cmd, int i);
int					valid_dir(char **cmd, int i);
int					valid_ind(char **cmd, int i);
int					lexicon_error(char **cmd, int i, char *err, int ret);

int					verify_code(t_file *file, char *line, int l, int s);
int					is_head(char **cmd, char *str);
int					is_label(char **cmd);
int					is_opcode(char **cmd, int i, int line);

#endif
