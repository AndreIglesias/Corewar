/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_addr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarault <fgarault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 15:43:14 by fgarault          #+#    #+#             */
/*   Updated: 2020/09/29 18:24:42 by fgarault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		get_label(t_code *code_tab, char *label)
{
	t_code *tab;

	tab = code_tab;
	while (tab)
	{
		if (!ft_strcmp(label, tab->label))
			return (tab->mem_pos);
		tab = tab->next;
	}
	return (-1);
}

void	put_addr(t_args *arg, t_code *tab, int cur_pos)
{
	if (arg->reg)
		itob(arg->hex, arg->reg, arg->size);
	else if (arg->ind)
	{
		if (arg->ind[0] == LABEL_CHAR)
			itob(arg->hex, (get_label(tab, &arg->ind[1]) - cur_pos),
			arg->size);
		else
			itob(arg->hex, ft_atoi(arg->ind), arg->size);
	}
	else if (arg->dir)
	{
		if (arg->dir[1] == LABEL_CHAR)
			itob(arg->hex, (get_label(tab, &arg->dir[2]) - cur_pos),
			arg->size);
		else
			itob(arg->hex, ft_atoi(&arg->dir[1]), arg->size);
	}
}

void	get_addr(t_code *code_tab)
{
	t_code			*tab;
	t_instruction	*instr;
	t_args			*arg;

	tab = code_tab;
	while (tab)
	{
		instr = tab->instr;
		while (instr)
		{
			arg = instr->args;
			while (arg)
			{
				put_addr(arg, code_tab, instr->mem_pos);
				arg = arg->next;
			}
			instr = instr->next;
		}
		tab = tab->next;
	}
}
