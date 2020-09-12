/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op6_10.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 17:01:05 by ciglesia          #+#    #+#             */
/*   Updated: 2020/09/12 21:22:27 by ciglesia         ###   ########.fr       */
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
	((TP*)P->obj)->optab = 5;
	disect_args(vm, process, 0, &and_op);
}

/*
** opcode: 0x07
*/

void							op_or(t_vm *vm, t_list *process)
{
	((TP*)P->obj)->optab = 6;
	disect_args(vm, process, 0, &or_op);
}

/*
** opcode: 0x08
*/

void							op_xor(t_vm *vm, t_list *process)
{
	((TP*)P->obj)->optab = 7;
	disect_args(vm, process, 0, &xor_op);
}

/*
** opcode: 0x09
*/

void							op_zjmp(t_vm *vm, t_list *process)
{
	int move;

	move = reverse_bytes(vm, ((TP*)P->obj)->pc + 1, 2) % IDX_MOD;
	((TP*)P->obj)->pc = mem_mod(((TP*)P->obj)->pc +
						((((TP*)P->obj)->carry) ? move : 3));
}

/*
** opcode: 0x0A
*/

void							op_ldi(t_vm *vm, t_list *process)
{
	((TP*)P->obj)->optab = 9;
	disect_args(vm, process, 2, &ldi_op);
}
