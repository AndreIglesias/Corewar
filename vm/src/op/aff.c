/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 17:03:30 by ciglesia          #+#    #+#             */
/*   Updated: 2020/09/12 21:21:29 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** opcode: 0x10
*/

void							op_aff(t_vm *vm, t_list *process)
{
	t_uchar	acb;

	acb = in_mem(vm, ((TP*)P->obj)->pc + 1);
	if (p_acb(acb, 1) == REG && is_reg(vm, ((TP*)P->obj)->pc + 2))
	{
		ft_printf("AFF: %d\n",
			((TP*)P->obj)->reg[in_mem(vm, ((TP*)P->obj)->pc + 2) - 1]);
	}
	((TP*)P->obj)->pc = mem_mod(((TP*)P->obj)->pc + octal_shift(acb, 4, 1));
}
