/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 18:59:54 by ciglesia          #+#    #+#             */
/*   Updated: 2020/09/25 17:54:16 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	add_label(t_file *file, char *label)
{
	unsigned int	i;
	t_code			*new;
	t_code			*aux;

	i = 0;
	while (label[i] && label[i] != ':')
		i++;
	new = new_label();
	new->label = ft_strndup(label, i);
	aux = file->code_tab;
	if (!aux)
		file->code_tab = new;
	else
	{
		while (aux->next)
			aux = aux->next;
		aux->next = new;
	}
}

void	add_instruction(t_file *file, char **cmd, int i)
{
	t_instruction	*new;
	t_code			*aux;
	t_instruction	*iaux;

	new = new_instruction();
	load_op(cmd, i, new);
	new->line = file->line;
	if (!file->code_tab)
		add_label(file, "MAIN_LABEL");
	aux = file->code_tab;
	while (aux->next)
		aux = aux->next;
	iaux = aux->instr;
	if (!iaux)
		aux->instr = new;
	else
	{
		while (iaux->next)
			iaux = iaux->next;
		iaux->next = new;
	}
}

void	add_arg(t_instruction *instr, int reg, char *dir, char *ind)
{
	t_args	*new;
	t_args	*aux;

	new = new_args();
	if (reg)
		new->reg = reg;
	if (dir)
		new->dir = dir;
	if (ind)
		new->ind = ind;
	if (!instr->args)
	{
		instr->args = new;
		return ;
	}
	aux = instr->args;
	while (aux->next)
		aux = aux->next;
	aux->next = new;
}
