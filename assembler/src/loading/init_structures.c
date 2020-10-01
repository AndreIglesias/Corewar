/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 20:49:08 by ciglesia          #+#    #+#             */
/*   Updated: 2020/09/30 21:05:18 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void			file_init(t_file *file, char *name)
{
	file->fd = -1;
	file->line = 0;
	file->quotes = 0;
	file->prog_size = 0;
	file->exec_magic = 0;
	file->type = 0;
	file->name = NULL;
	file->code_tab = NULL;
	file->name = ft_strdup(name);
	ft_memset(file->comment, 0, COMMENT_LENGTH);
	ft_memset(file->playername, 0, PROG_NAME_LENGTH);
	ft_memset(file->code, 0, CHAMP_MAX_SIZE);
}

t_code			*new_label(void)
{
	t_code *new;

	if (!(new = (t_code*)malloc(sizeof(t_code))))
		return (NULL);
	new->mem_pos = 0;
	new->label = NULL;
	new->instr = NULL;
	new->next = NULL;
	return (new);
}

t_instruction	*new_instruction(void)
{
	t_instruction	*new;

	if (!(new = (t_instruction*)malloc(sizeof(t_instruction))))
		return (NULL);
	new->mem_pos = 0;
	new->opcode = 0;
	new->nargs = 0;
	new->size = 0;
	new->line = 0;
	new->acb = 0;
	new->args = NULL;
	new->next = NULL;
	return (new);
}

t_args			*new_args(void)
{
	t_args *new;

	if (!(new = (t_args*)malloc(sizeof(t_args))))
		return (NULL);
	ft_memset(new->hex, 0, MAX_ARG_SIZE);
	new->size = 0;
	new->reg = 0;
	new->dir = NULL;
	new->ind = NULL;
	new->next = NULL;
	return (new);
}
