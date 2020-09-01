/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op6_10.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 17:01:05 by ciglesia          #+#    #+#             */
/*   Updated: 2020/09/01 21:55:44 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "vm.h"

/*
** 0b00 absent
** 0b01 registry
** 0b10 direct
** 0b11 index
*/

/*
** opcode: 0x06
**
** S(RG/ID/D4) S(RG/ID/D4) D(RG)
**
*/

void							op_and(t_vm *vm, t_list *process)
{
	t_uchar acb;
	int args;
	t_uchar type;
	t_uchar move;
	int	nb[3];

	args = 3;
	move = 0;
	acb = in_mem(vm, TPROCES->pc + 1);
	if (is_argsize(5, acb, args))
	{
		while (args)
		{
			type = (acb >> ((args--) * 2)) & 0b11;
			if (type == REG && !is_reg(vm, TPROCES->pc + 2 + move))
				break;
			if (args)
				nb[args] = get_arg(vm, process, &move, type);
			if (args)
				continue ;
			nb[args] = in_mem(vm, TPROCES->pc + 2 + move) - 1;
			save_cmp(process, nb[0], nb[1] & nb[2]);
		}
	}
	TPROCES->pc = mem_mod(TPROCES->pc + octal_shift(acb, 4, 3));
}

/*
** opcode: 0x07
*/

void							op_or(t_vm *vm, t_list *process)
{
	t_uchar acb;
	int args;
	t_uchar type;
	t_uchar move;
	int	nb[3];

	args = 3;
	move = 0;
	acb = in_mem(vm, TPROCES->pc + 1);
	if (is_argsize(6, acb, args))
	{
		while (args)
		{
			type = (acb >> ((args--) * 2)) & 0b11;
			if (type == REG && !is_reg(vm, TPROCES->pc + 2 + move))
				break;
			if (args)
				nb[args] = get_arg(vm, process, &move, type);
			if (args)
				continue ;
			nb[args] = in_mem(vm, TPROCES->pc + 2 + move) - 1;
			save_cmp(process, nb[0], nb[1] | nb[2]);
		}
	}
	TPROCES->pc = mem_mod(TPROCES->pc + octal_shift(acb, 4, 3));
}

/*
** opcode: 0x08
*/

void							op_xor(t_vm *vm, t_list *process)
{
	t_uchar acb;
	int args;
	t_uchar type;
	t_uchar move;
	int	nb[3];

	args = 3;
	move = 0;
	acb = in_mem(vm, TPROCES->pc + 1);
	if (is_argsize(7, acb, args))
	{
		while (args)
		{
			type = (acb >> ((args--) * 2)) & 0b11;
			if (type == REG && !is_reg(vm, TPROCES->pc + 2 + move))
				break;
			if (args)
				nb[args] = get_arg(vm, process, &move, type);
			if (args)
				continue ;
			nb[args] = in_mem(vm, TPROCES->pc + 2 + move) - 1;
			save_cmp(process, nb[0], nb[1] ^ nb[2]);
		}
	}
	TPROCES->pc = mem_mod(TPROCES->pc + octal_shift(acb, 4, 3));
}

/*
** opcode: 0x09
*/

void							op_zjmp(t_vm *vm, t_list *process)
{
	int pos;

	pos = reverse_bytes(vm, TPROCES->pc + 1, 2) % IDX_MOD;
	TPROCES->pc = mem_mod(TPROCES->pc + ((TPROCES->carry) ? pos : 3));
}

/*
** opcode: 0x0A
*/

void							op_ldi(t_vm *vm, t_list *process)
{
	t_uchar acb;
	int args;
	t_uchar type;
	t_uchar move;
	int	nb[3];

	args = 3;
	move = 0;
	acb = in_mem(vm, TPROCES->pc + 1);
	if (is_argsize(9, acb, args))
	{
		while (args)
		{
			type = (acb >> ((args--) * 2)) & 0b11;
			if (type == REG && !is_reg(vm, TPROCES->pc + 2 + move))
				break;
			if (args)
				nb[args] = get_arg(vm, process, &move, type + 4);
			if (args)
				continue ;
			nb[args] = in_mem(vm, TPROCES->pc + 2 + move) - 1;
			TPROCES->reg[nb[0]] = reverse_bytes(vm, TPROCES->pc +
									(nb[1] + nb[2]) % IDX_MOD, 4);
		}
	}
	TPROCES->pc = mem_mod(TPROCES->pc + octal_shift(acb, 2, 3));
}
