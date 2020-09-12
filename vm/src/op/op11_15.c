/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op11_15.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 17:02:18 by ciglesia          #+#    #+#             */
/*   Updated: 2020/09/12 21:20:15 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** opcode: 0x0B
*/

void							op_sti(t_vm *vm, t_list *process)
{
	t_uchar	acb;
	int		args;
	t_uchar	type;
	t_uchar	mv;
	int		nb[3];

	args = 3;
	mv = 0;
	acb = in_mem(vm, ((TP*)P->obj)->pc + 1);
	if (is_argsize(10, acb, args))
	{
		while (args--)
		{
			type = (acb >> ((args + 1) * 2)) & 0b11;
			if (type == REG && !is_reg(vm, ((TP*)P->obj)->pc + 2 + mv))
				break ;
			nb[args] = (args == 2) ? in_mem(vm, ((TP*)P->obj)->pc + 2 + mv++)
				- 1 : get_arg(vm, process, &mv, type + 4);
			if (!args)
				store_at(vm, process, ((TP*)P->obj)->reg[nb[2]],
					((TP*)P->obj)->pc + ((nb[0] + nb[1]) % IDX_MOD) + 3);
		}
	}
	((TP*)P->obj)->pc = mem_mod(((TP*)P->obj)->pc + octal_shift(acb, 2, 3));
}

/*
** opcode: 0x0C
*/

void							op_fork(t_vm *vm, t_list *process)
{
	int move;

	move = reverse_bytes(vm, ((TP*)P->obj)->pc + 1, 2);
	add_process(vm, process, mem_mod(((TP*)P->obj)->pc + (move % IDX_MOD)));
	((TP*)P->obj)->pc = mem_mod(((TP*)P->obj)->pc + 3);
}

/*
** opcode: 0x0D
*/

void							op_lld(t_vm *vm, t_list *process)
{
	int		move;
	t_uchar	acb;
	int		reg;

	acb = in_mem(vm, ((TP*)P->obj)->pc + 1);
	if (is_argsize(12, acb, 2))
	{
		reg = ((TP*)P->obj)->pc + 6 - ((acb & 0b01100000) >> 5);
		if (is_reg(vm, reg))
		{
			if (p_acb(acb, 1) == DIR)
				move = reverse_bytes(vm, ((TP*)P->obj)->pc + 2, 4);
			else
			{
				move = reverse_bytes(vm, ((TP*)P->obj)->pc + 2, 2);
				move = reverse_bytes(vm, ((TP*)P->obj)->pc + move, 2);
			}
			((TP*)P->obj)->reg[in_mem(vm, reg) - 1] = move;
			((TP*)P->obj)->carry = (move) ? 0 : 1;
		}
	}
	((TP*)P->obj)->pc = mem_mod(((TP*)P->obj)->pc + octal_shift(acb, 4, 2));
}

/*
** opcode: 0x0E
*/

void							op_lldi(t_vm *vm, t_list *process)
{
	((TP*)P->obj)->optab = 13;
	disect_args(vm, process, 2, &lldi_op);
}

/*
** opcode: 0x0F
*/

void							op_lfork(t_vm *vm, t_list *process)
{
	int move;

	move = reverse_bytes(vm, ((TP*)P->obj)->pc + 1, 2);
	add_process(vm, process, mem_mod(((TP*)P->obj)->pc + move));
	((TP*)P->obj)->pc = mem_mod(((TP*)P->obj)->pc + 3);
}
