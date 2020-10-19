/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 14:44:58 by ciglesia          #+#    #+#             */
/*   Updated: 2020/10/19 13:20:10 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		is_ir(t_list *process, int i)
{
	while (process)
	{
		if (i == ((TP*)P->obj)->pc && (((TP*)P->obj)->ir <= 15))
			return (((TP*)P->obj)->owner);
		process = process->next;
	}
	return (0);
}

int		is_pc(t_list *process, int i)
{
	while (process)
	{
		if (i == ((TP*)P->obj)->pc)
			return (1);
		process = process->next;
	}
	return (0);
}

void	dump_bytes(t_vm *vm, int i)
{
	if (vm->verbosity)
	{
		if (vm->ram.owner[i] == 0)
			ft_printf(GRAY"%.2x "E0M, vm->ram.arena[i]);
		else if (vm->ram.owner[i] == 1)
			ft_printf(GREEN"%.2x "E0M, vm->ram.arena[i]);
		else if (vm->ram.owner[i] == 2)
			ft_printf(CYAN"%.2x "E0M, vm->ram.arena[i]);
		else if (vm->ram.owner[i] == 3)
			ft_printf(BLUE"%.2x "E0M, vm->ram.arena[i]);
		else
			ft_printf(YELLOW"%.2x "E0M, vm->ram.arena[i]);
	}
	else
		ft_printf("%.2x", vm->ram.arena[i]);
}

int		print_ram(t_vm *vm)
{
	int i;
	int line;

	i = 0;
	line = 0;
	(vm->verbosity) ? ft_printf("0x%#.4x | ", line) : 0;
	while (i < MEM_SIZE)
	{
		dump_bytes(vm, i);
		if (i != 1 && (i + 1) % 32 == 0)
		{
			line += 32;
			ft_printf("\n");
			if (vm->verbosity && i + 1 < MEM_SIZE)
				ft_printf("%0#.4x | ", line);
		}
		i++;
	}
	return (0);
}
