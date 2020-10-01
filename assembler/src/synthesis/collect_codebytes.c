/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_codebytes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarault <fgarault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 16:45:01 by fgarault          #+#    #+#             */
/*   Updated: 2020/09/29 17:17:49 by fgarault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static char		get_acb(t_instruction *instruction)
{
	t_args	*argument;
	int		i;
	int		acb;

	argument = instruction->args;
	i = 7;
	acb = 0;
	while (argument)
	{
		if (argument->reg && i--)
			acb += ft_power(2, i);
		else if (argument->dir && i--)
			acb += ft_power(2, i + 1);
		else if (argument->ind && i--)
			acb += ft_power(2, i + 1) + ft_power(2, i);
		i--;
		argument = argument->next;
	}
	return (acb);
}

static int		is_bigger_arg(t_instruction *instr)
{
	char *op;

	op = g_op_tab[instr->opcode - 1].name;
	if (!ft_strcmp("and", op) || !ft_strcmp("or", op) || !ft_strcmp("xor", op)
		|| !ft_strcmp("live", op) || !ft_strcmp("ld", op))
		return (1);
	return (0);
}

static int		get_sizeof(t_instruction *instruction)
{
	t_args	*argument;
	int		total;

	argument = instruction->args;
	total = 0;
	while (argument)
	{
		if (argument->reg)
			argument->size = 1;
		else if (argument->ind)
			argument->size = 2;
		else if (argument->dir)
		{
			if (is_bigger_arg(instruction))
				argument->size = 4;
			else
				argument->size = 2;
		}
		total += argument->size;
		argument = argument->next;
	}
	return (total);
}

void			collecting_codebytes(t_file *file)
{
	t_code			*tab;
	t_instruction	*ins;

	tab = file->code_tab;
	while (tab)
	{
		tab->mem_pos = file->prog_size;
		ins = tab->instr;
		while (ins)
		{
			ins->mem_pos = file->prog_size;
			if (ins->nargs > 1)
				ins->acb = get_acb(ins);
			if (ins->acb)
				file->prog_size += get_sizeof(ins) + 2;
			else
				file->prog_size += get_sizeof(ins) + 1;
			ins = ins->next;
		}
		tab = tab->next;
	}
	get_addr(file->code_tab);
	writing_exec(file);
}
