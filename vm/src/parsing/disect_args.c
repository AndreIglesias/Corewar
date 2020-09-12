/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disect_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 17:18:40 by ciglesia          #+#    #+#             */
/*   Updated: 2020/09/12 19:46:45 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** isld if 2 -> is load function
** if 0 -> compare function
*/

void	disect_args(t_vm *vm, t_list *process, int isld,
					void (*f)(t_list *process, int *nb, t_vm *vm))
{
	t_uchar	acb;
	int		args;
	t_uchar	type;
	t_uchar	move;
	int		nb[3];

	args = 3;
	move = 0;
	acb = in_mem(vm, TPROCES->pc + 1);
	if (is_argsize(TPROCES->optab, acb, args))
	{
		while (args)
		{
			type = (acb >> ((args--) * 2)) & 0b11;
			if (type == REG && !is_reg(vm, TPROCES->pc + 2 + move))
				break ;
			if (args)
				nb[args] = get_arg(vm, process, &move, type + (isld * 2));
			if (args)
				continue ;
			nb[args] = in_mem(vm, TPROCES->pc + 2 + move) - 1;
			(*f)(process, nb, vm);
		}
	}
	TPROCES->pc = mem_mod(TPROCES->pc + octal_shift(acb, 4 - isld, 3));
}
