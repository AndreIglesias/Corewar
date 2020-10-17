/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 17:03:30 by ciglesia          #+#    #+#             */
/*   Updated: 2020/10/16 15:00:22 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** opcode: 0x10
*/

void				aff_verb(t_uchar value, int val, t_list *process)
{
	if (((TP*)P->obj)->owner == 0)
		ft_printf(GRAY"0x%.2x : %.3d(%.3d) :\t%c\n", value, value, val, value);
	else if (((TP*)P->obj)->owner == 1)
		ft_printf(GREEN"0x%.2x : %.3d(%.3d) :\t%c\n", value, value, val, value);
	else if (((TP*)P->obj)->owner == 2)
		ft_printf(CYAN"0x%.2x : %.3d(%.3d) :\t%c\n", value, value, val, value);
	else if (((TP*)P->obj)->owner == 3)
		ft_printf(BLUE"0x%.2x : %.3d(%.3d) :\t%c\n", value, value, val, value);
	else
		ft_printf(YELLOW"0x%.2x : %.3d(%.3d) :\t%c\n", value, value, val, value);
	ft_printf(E0M);
}

void				op_aff(t_vm *vm, t_list *process)
{
	t_uchar	acb;
	t_uchar	value;
	int		valint;

	acb = in_mem(vm, ((TP*)P->obj)->pc + 1);
	if (p_acb(acb, 1) == REG && is_reg(vm, ((TP*)P->obj)->pc + 2))
	{
		value = ((TP*)P->obj)->reg[in_mem(vm, ((TP*)P->obj)->pc + 2) - 1];
		valint = ((TP*)P->obj)->reg[in_mem(vm, ((TP*)P->obj)->pc + 2) - 1];
		if (!vm->ncurses)
		{
			if (vm->verbosity)
				aff_verb(value, valint, process);
			else
				ft_printf("%c\n", value);
		}
	}
	((TP*)P->obj)->pc = mem_mod(((TP*)P->obj)->pc + octal_shift(acb, 4, 1));
}
