/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 17:03:30 by ciglesia          #+#    #+#             */
/*   Updated: 2020/08/31 18:03:44 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** opcode: 0x10
*/

void							op_aff(t_vm *vm, t_list *process)
{
	int acb;

	acb = in_mem(vm, TPROCES->pc + 1);
	if (ACB1 == REG && is_reg(vm, TPROCES->pc + 2))
	{
		ft_printf("AFF: %d\n", (t_uchar)TPROCES->reg[in_mem(vm, TPROCES->pc + 2) - 1]);
	}
	TPROCES->pc = mem_mod(TPROCES->pc + octal_shift(acb, 4, 1));
}
