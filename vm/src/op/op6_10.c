/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op6_10.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 17:01:05 by ciglesia          #+#    #+#             */
/*   Updated: 2020/09/12 19:50:24 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** 0b00 absent
** 0b01 registry
** 0b10 direct
** 0b11 index
*/

/*
** opcode: 0x06
** S(RG/ID/D4) S(RG/ID/D4) D(RG)
*/

void							op_and(t_vm *vm, t_list *process)
{
	TPROCES->optab = 5;
	disect_args(vm, process, 0, &and_op);
}

/*
** opcode: 0x07
*/

void							op_or(t_vm *vm, t_list *process)
{
	TPROCES->optab = 6;
	disect_args(vm, process, 0, &or_op);
}

/*
** opcode: 0x08
*/

void							op_xor(t_vm *vm, t_list *process)
{
	TPROCES->optab = 7;
	disect_args(vm, process, 0, &xor_op);
}

/*
** opcode: 0x09
*/

void							op_zjmp(t_vm *vm, t_list *process)
{
	int move;

	move = reverse_bytes(vm, TPROCES->pc + 1, 2) % IDX_MOD;
	TPROCES->pc = mem_mod(TPROCES->pc + ((TPROCES->carry) ? move : 3));
}

/*
** opcode: 0x0A
*/

void							op_ldi(t_vm *vm, t_list *process)
{
	TPROCES->optab = 9;
	disect_args(vm, process, 2, &ldi_op);
}
