/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destructors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 11:07:25 by ciglesia          #+#    #+#             */
/*   Updated: 2020/09/24 11:42:54 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void			free_args(t_args *args)
{
	t_args *aux;

	while (args)
	{
		if (args->dir)
			free(args->dir);
		if (args->ind)
			free(args->ind);
		aux = args->next;
		free(args);
		args = aux;
	}
}

void			free_instructions(t_instruction *instr)
{
	t_instruction *aux;

	while (instr)
	{
		free_args(instr->args);
		aux = instr->next;
		free(instr);
		instr = aux;
	}
}

int				file_destructor(t_file *file)
{
	t_code	*table;
	t_code	*tabaux;

	if (file->name)
		free(file->name);
	if (file->code_tab)
	{
		table = file->code_tab;
		while (table)
		{
			if (table->instr)
				free_instructions(table->instr);
			if (table->label)
				free(table->label);
			tabaux = table->next;
			free(table);
			table = tabaux;
		}
	}
	return (0);
}
