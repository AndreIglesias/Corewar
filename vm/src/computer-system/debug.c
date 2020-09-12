/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 14:44:58 by ciglesia          #+#    #+#             */
/*   Updated: 2020/09/12 21:24:47 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		is_ir(t_list *process, int i)
{
	while (process)
	{
		if (i == ((TP*)P->obj)->pc && (((TP*)P->obj)->ir > 0 &&
										((TP*)P->obj)->ir <= 15))
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

int		print_ram(t_vm *vm)
{
	int i;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (vm->ram.owner[i] == 0)
			ft_printf(GRAY"%.2x"E0M, vm->ram.arena[i]);
		else if (vm->ram.owner[i] == 1)
			ft_printf(GREEN"%.2x"E0M, vm->ram.arena[i]);
		else if (vm->ram.owner[i] == 2)
			ft_printf(CYAN"%.2x"E0M, vm->ram.arena[i]);
		else if (vm->ram.owner[i] == 3)
			ft_printf(BLUE"%.2x"E0M, vm->ram.arena[i]);
		else
			ft_printf(YELLOW"%.2x"E0M, vm->ram.arena[i]);
		if (i != 1 && (i + 1) % 32 == 0)
			ft_printf("\n");
		i++;
	}
	return (0);
}
