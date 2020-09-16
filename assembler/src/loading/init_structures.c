/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 20:49:08 by ciglesia          #+#    #+#             */
/*   Updated: 2020/09/15 19:10:05 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void			file_init(t_file *file)
{
	file->fd = -1;
	file->line = 0;
	file->quotes = 0;
	file->name = NULL;
	file->code_tab = NULL;
	ft_memset(file->comment, 0, COMMENT_LENGTH);
	ft_memset(file->playername, 0, PROG_NAME_LENGTH);
	ft_memset(file->code, 0, CHAMP_MAX_SIZE);
}

t_code			*new_label(void)
{
	t_code *new;

	if (!(new = (t_code*)malloc(sizeof(t_code))))
		return (NULL);
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
	new->opcode = 0;
	new->acb = 0;
	new->reg = 0;
	new->dir = NULL;
	new->ind = NULL;
	new->next = NULL;
	return (new);
}
