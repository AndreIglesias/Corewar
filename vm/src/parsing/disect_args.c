/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disect_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 17:18:40 by ciglesia          #+#    #+#             */
/*   Updated: 2020/09/12 21:32:23 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_process	*f_proc(t_vm *vm)
{
	return ((t_process*)vm->processes->obj);
}

int			p_acb(t_uchar acb, int p_number)
{
	if (p_number == 1)
		return ((acb & 0b11000000) >> 6);
	if (p_number == 2)
		return ((acb & 0b110000) >> 4);
	if (p_number == 3)
		return ((acb & 0b1100) >> 2);
	return (EXIT_FAILURE);
}

/*
** param l: if 2 -> is load function
** if 0 -> compare function
*/

void		disect_args(t_vm *vm, t_list *process, int l,
					void (*f)(t_list *process, int *nb, t_vm *vm))
{
	t_uchar	acb;
	int		args;
	t_uchar	type;
	t_uchar	move;
	int		nb[3];

	args = 3;
	move = 0;
	acb = in_mem(vm, ((TP*)P->obj)->pc + 1);
	if (is_argsize(((TP*)P->obj)->optab, acb, args))
	{
		while (args)
		{
			type = (acb >> ((args--) * 2)) & 0b11;
			if (type == REG && !is_reg(vm, ((TP*)P->obj)->pc + 2 + move))
				break ;
			if (args)
				nb[args] = get_arg(vm, process, &move, type + (l * 2));
			if (args)
				continue ;
			nb[args] = in_mem(vm, ((TP*)P->obj)->pc + 2 + move) - 1;
			(*f)(process, nb, vm);
		}
	}
	((TP*)P->obj)->pc = mem_mod(((TP*)P->obj)->pc + octal_shift(acb, 4 - l, 3));
}
