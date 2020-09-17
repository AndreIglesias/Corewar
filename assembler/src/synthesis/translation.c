/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 19:12:29 by ciglesia          #+#    #+#             */
/*   Updated: 2020/09/16 12:29:44 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	print_instr(t_instruction *instr)
{
	while (instr)
	{
		ft_printf(GREEN"\t%s "E0M, g_op_tab[instr->opcode - 1].name);
		ft_printf(CYAN"[r%d, %s, %s]\n"E0M, instr->reg, instr->dir, instr->ind);
		instr = instr->next;
	}
}

int		translate(t_file *file, int verbosity)
{
	t_code	*table;

	table = file->code_tab;
	while (table)
	{
		if (verbosity)
		{
			ft_printf(BLUE"%s:\n"E0M, table->label);
			print_instr(table->instr);
			//print intrinsic instructions (table->instr)
		}
		table = table->next;
	}
	return (0);
}
