/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 19:12:29 by ciglesia          #+#    #+#             */
/*   Updated: 2020/10/05 13:14:44 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	print_multi_hex(t_uchar *hex, int size)
{
	int		i;

	i = 0;
	while (i < size)
	{
		ft_printf("%.2x ", hex[i]);
		i++;
	}
}

void	print_hex(t_instruction *instr)
{
	t_args	*args;

	args = instr->args;
	ft_printf(GREEN"%.2x "E0M, instr->opcode);
	instr->acb ? ft_printf(RED"%.2x "E0M, instr->acb) : 0;
	while (args)
	{
		print_multi_hex(args->hex, args->size);
		args = args->next;
	}
	ft_printf("\n");
}

void	print_instr(t_instruction *instr)
{
	t_args	*args;

	while (instr)
	{
		ft_printf(GREEN"\t%s "E0M, g_op_tab[instr->opcode - 1].name);
		args = instr->args;
		ft_printf(GREEN"["E0M);
		while (args)
		{
			if (args->reg)
				ft_printf(CYAN"r%d "E0M, args->reg);
			if (args->dir)
				ft_printf(CYAN"%s "E0M, args->dir);
			if (args->ind)
				ft_printf(CYAN"%s "E0M, args->ind);
			args = args->next;
		}
		ft_printf(GREEN"]\t\t"E0M);
		print_hex(instr);
		instr = instr->next;
	}
}

int		translate(t_file *file, int verbosity)
{
	t_code	*table;

	table = file->code_tab;
	collecting_codebytes(file);
	if (verbosity)
	{
		ft_printf(CYAN".name \"%s\"\n"E0M, file->playername);
		ft_printf(CYAN".comment \"%s\"\n"E0M, file->comment);
		while (table)
		{
			ft_printf(BLUE"%s:\n"E0M, table->label);
			print_instr(table->instr);
			table = table->next;
		}
	}
	return (0);
}
