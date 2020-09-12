/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_cmpi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 17:59:40 by ciglesia          #+#    #+#             */
/*   Updated: 2020/09/12 21:13:10 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	and_op(t_list *process, int *nb, t_vm *vm)
{
	(void)vm;
	save_cmp(process, nb[0], nb[1] & nb[2]);
}

void	or_op(t_list *process, int *nb, t_vm *vm)
{
	(void)vm;
	save_cmp(process, nb[0], nb[1] | nb[2]);
}

void	xor_op(t_list *process, int *nb, t_vm *vm)
{
	(void)vm;
	save_cmp(process, nb[0], nb[1] ^ nb[2]);
}

void	ldi_op(t_list *process, int *nb, t_vm *vm)
{
	int id;
	int n1;
	int n2;

	id = nb[0];
	n1 = nb[1];
	n2 = nb[2];
	((TP*)P->obj)->reg[id] = reverse_bytes(vm, ((TP*)P->obj)->pc +
											(n1 + n2) % IDX_MOD, 4);
}

void	lldi_op(t_list *process, int *nb, t_vm *vm)
{
	int id;
	int n1;
	int n2;

	id = nb[0];
	n1 = nb[1];
	n2 = nb[2];
	((TP*)P->obj)->reg[id] = reverse_bytes(vm, ((TP*)P->obj)->pc + n1 + n2, 4);
	((TP*)P->obj)->carry = (((TP*)P->obj)->reg[id]) ? 0 : 1;
}
