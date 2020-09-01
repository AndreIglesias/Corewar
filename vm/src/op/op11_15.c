/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op11_15.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 17:02:18 by ciglesia          #+#    #+#             */
/*   Updated: 2020/08/31 22:20:42 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** opcode: 0x0B
*/

void							op_sti(t_vm *vm, t_list *process)
{
	t_uchar acb;
	int args;
	t_uchar type;
	t_uchar mv;
	int	nb[3];

	args = 3;
	mv = 0;
	acb = in_mem(vm, TPROCES->pc + 1);
	if (is_argsize(10, acb, args))
	{
		while (args--)
		{
			type = (acb >> ((args + 1) * 2)) & 0b11;
			if (type == REG && !is_reg(vm, TPROCES->pc + 2 + mv))
				break ;
			nb[args] = (args == 2) ? in_mem(vm, TPROCES->pc + 2 + mv++) - 1 :
				get_arg(vm, process, &mv, type + 4);
			if (!args)
				store_at(vm, process, TPROCES->reg[nb[2]], TPROCES->pc +
						 ((nb[0] + nb[1]) % IDX_MOD) + 3);
		}
	}
	TPROCES->pc = mem_mod(TPROCES->pc + octal_shift(acb, 2, 3));
}

/*
** opcode: 0x0C
*/

void							op_fork(t_vm *vm, t_list *process)
{
	t_uchar move;

	move = reverse_bytes(vm, TPROCES->pc + 1, 2);
	add_process(vm, process, mem_mod(TPROCES->pc + (move % IDX_MOD)));
	TPROCES->pc = mem_mod(TPROCES->pc + 3);
}

/*
** opcode: 0x0D
*/

void							op_lld(t_vm *vm, t_list *process)
{
	t_uchar move;
	t_uchar acb;
	int reg;

	acb = in_mem(vm, TPROCES->pc + 1);
	if (is_argsize(12, acb, 2))
	{
		reg = TPROCES->pc + 6 - ((acb & 0b01100000) >> 5);
		if (is_reg(vm, reg))
		{
			if (ACB1 == DIR)
				move = reverse_bytes(vm, TPROCES->pc + 2, 4);
			else
			{
				move = reverse_bytes(vm, TPROCES->pc + 2, 2);
				move = reverse_bytes(vm, TPROCES->pc + move, 2);
			}
			TPROCES->reg[in_mem(vm, reg) - 1] = move;
			TPROCES->carry = (move) ? 0 : 1;
		}
	}
	TPROCES->pc = mem_mod(TPROCES->pc + octal_shift(acb, 4, 2));
}

/*
** opcode: 0x0E
*/

void							op_lldi(t_vm *vm, t_list *process)
{
	t_uchar acb;
	int args;
	t_uchar type;
	t_uchar mv;
	int	nb[3];

	args = 3;
	mv = 0;
	acb = in_mem(vm, TPROCES->pc + 1);
	if (is_argsize(13, acb, args))
	{
		while (args)
		{
			type = (acb >> ((args--) * 2)) & 0b11;
			if (type == REG && !is_reg(vm, TPROCES->pc + 2 + mv))
				break ;
			if (args)
				nb[args] = get_arg(vm, process, &mv, type + 4);
			if (args)
				continue ;
			nb[args] = in_mem(vm, TPROCES->pc + 2 + mv) - 1;
			TPROCES->reg[nb[0]] = reverse_bytes(vm, TPROCES->pc + nb[1] + nb[2], 4);
			TPROCES->carry = (TPROCES->reg[nb[0]]) ? 0 : 1;
		}
	}
	TPROCES->pc = mem_mod(TPROCES->pc + octal_shift(acb, 2, 3));
}

/*
** opcode: 0x0F
*/

void							op_lfork(t_vm *vm, t_list *process)
{
	t_uchar move;

	move = reverse_bytes(vm, TPROCES->pc + 1, 2);
	add_process(vm, process, mem_mod(TPROCES->pc + move));
	TPROCES->pc = mem_mod(TPROCES->pc + 3);
}
