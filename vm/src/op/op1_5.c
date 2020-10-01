/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op1_5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 16:59:34 by ciglesia          #+#    #+#             */
/*   Updated: 2020/09/27 15:38:44 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** ACB Parameters:
**		0b1100
**		0b110000
**		0b11000000
**
** opcode: 0x01
*/

void							op_live(t_vm *vm, t_list *process)
{
	int live;

	((TP*)P->obj)->live_count++;
	vm->nlives++;
	live = reverse_bytes(vm, ((TP*)P->obj)->pc + 1, 4);
	player_alive(vm, live);
	((TP*)P->obj)->pc = mem_mod(((TP*)P->obj)->pc + 5);
	((TP*)P->obj)->live_since = -1;
}

/*
** opcode: 0x02
*/

void							op_ld(t_vm *vm, t_list *process)
{
	t_uchar	acb;
	int		move;
	int		reg;

	acb = in_mem(vm, ((TP*)P->obj)->pc + 1);
	reg = ((TP*)P->obj)->pc + 6 - ((acb & 0b01100000) >> 5);
	if (((p_acb(acb, 1) == DIR || p_acb(acb, 1) == IND) && p_acb(acb, 2) == REG)
		&& is_reg(vm, reg))
	{
		if (p_acb(acb, 1) == DIR)
			move = reverse_bytes(vm, ((TP*)P->obj)->pc + 2, 4);
		else
		{
			move = reverse_bytes(vm, ((TP*)P->obj)->pc + 2, 2) % IDX_MOD;
			move = reverse_bytes(vm, ((TP*)P->obj)->pc + move, 4);
		}
		((TP*)P->obj)->reg[in_mem(vm, reg) - 1] = move;
		((TP*)P->obj)->carry = (move) ? 0 : 1;
	}
	((TP*)P->obj)->pc = mem_mod(((TP*)P->obj)->pc + octal_shift(acb, 4, 2));
}

/*
** opcode: 0x03
*/

void							op_st(t_vm *vm, t_list *process)
{
	t_uchar			acb;
	unsigned int	reg;
	int				move;

	acb = in_mem(vm, ((TP*)P->obj)->pc + 1);
	if (p_acb(acb, 1) == REG && is_reg(vm, ((TP*)P->obj)->pc + 2))
	{
		reg = ((TP*)P->obj)->reg[in_mem(vm, ((TP*)P->obj)->pc + 2) - 1];
		if (p_acb(acb, 2) == REG && is_reg(vm, ((TP*)P->obj)->pc + 3))
			((TP*)P->obj)->reg[in_mem(vm, ((TP*)P->obj)->pc + 3) - 1] = reg;
		else if (p_acb(acb, 2) == IND)
		{
			move = reverse_bytes(vm, ((TP*)P->obj)->pc + 3, 2);
			store_at(vm, process, reg, ((TP*)P->obj)->pc
										+ (move % IDX_MOD) + 3);
		}
	}
	((TP*)P->obj)->pc = mem_mod(((TP*)P->obj)->pc + octal_shift(acb, 4, 2));
}

/*
** opcode: 0x04
*/

void							op_add(t_vm *vm, t_list *process)
{
	int		nb;
	t_uchar	acb;
	int		reg1;
	int		reg2;

	acb = in_mem(vm, ((TP*)P->obj)->pc + 1);
	if (is_argsize(3, acb, 3) && is_reg(vm, ((TP*)P->obj)->pc + 2) &&
		is_reg(vm, ((TP*)P->obj)->pc + 3) && is_reg(vm, ((TP*)P->obj)->pc + 4))
	{
		reg1 = ((TP*)P->obj)->reg[in_mem(vm, ((TP*)P->obj)->pc + 2) - 1];
		reg2 = ((TP*)P->obj)->reg[in_mem(vm, ((TP*)P->obj)->pc + 3) - 1];
		nb = reg1 + reg2;
		((TP*)P->obj)->carry = (nb) ? 0 : 1;
		((TP*)P->obj)->reg[in_mem(vm, ((TP*)P->obj)->pc + 4) - 1] = nb;
	}
	((TP*)P->obj)->pc = mem_mod(((TP*)P->obj)->pc + octal_shift(acb, 4, 3));
}

/*
** opcode: 0x05
*/

void							op_sub(t_vm *vm, t_list *process)
{
	int		nb;
	t_uchar	acb;
	int		reg1;
	int		reg2;

	acb = in_mem(vm, ((TP*)P->obj)->pc + 1);
	if (is_argsize(4, acb, 3) && is_reg(vm, ((TP*)P->obj)->pc + 2) &&
		is_reg(vm, ((TP*)P->obj)->pc + 3) && is_reg(vm, ((TP*)P->obj)->pc + 4))
	{
		reg1 = ((TP*)P->obj)->reg[in_mem(vm, ((TP*)P->obj)->pc + 2) - 1];
		reg2 = ((TP*)P->obj)->reg[in_mem(vm, ((TP*)P->obj)->pc + 3) - 1];
		nb = reg1 - reg2;
		((TP*)P->obj)->carry = (nb) ? 0 : 1;
		((TP*)P->obj)->reg[in_mem(vm, ((TP*)P->obj)->pc + 4) - 1] = nb;
	}
	((TP*)P->obj)->pc = mem_mod(((TP*)P->obj)->pc + octal_shift(acb, 4, 3));
}
