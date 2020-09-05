/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   byte_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 17:21:12 by ciglesia          #+#    #+#             */
/*   Updated: 2020/09/05 14:08:00 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		is_argsize(t_uchar ir, t_uchar acb, t_uchar narg)
{
	int m;
	int n;
	int i;

	m = 6;
	i = 0;
	while (narg)
	{
		n = 0;
		if ((acb >> m) & 0b11)
			n = 0b01 << (((acb >> m) & 0b11) - 1);
		if (!(n & op_tab[ir].args[i]))
			return (0);
		i++;
		narg--;
		m -= 2;
	}
	return (1);
}

int		octal_shift(t_uchar acb, t_uchar label_size, t_uchar narg)
{
	int shift;

	shift = 0b10;
	while (++narg <= 0b100)
		acb >>= 0b10;
	while (acb)
	{
		shift += ((acb & 0b11) == REG) ? 1 : 0;
		shift += ((acb & 0b11) == IND) ? 2 : 0;
		shift += ((acb & 0b11) == DIR) ? label_size : 0;
		acb >>= 0b10;
	}
	return (shift);
}

unsigned int	ft_ptr_to_uint(t_vm *vm, unsigned int pc, int size)
{
	int				i;
	unsigned int	result;

	i = 0;
	result = 0;
	pc = mem_mod(pc);
	while (i < size)
	{
		result = result * 0x100 + vm->ram.arena[pc];
		i++;
		pc = mem_mod(pc + 1);
	}
	return (result);
}

int				idx_mod(unsigned int val)
{
	int		flag;

	flag = 0;
	if (val > 2147483647)
		flag = 1;
	val = val % 65536;
	/*
	if (proc->loaded_op.opcode == 13 || proc->loaded_op.opcode == 14)
	{
		if (flag == 0)
			return (val % MEM_SIZE);
		return (-(-(val % MEM_SIZE) % IDX_MOD));
		}*/
	if (val > (65535 / 2) || flag == 1)
		return (-(-(val % MEM_SIZE) % IDX_MOD));
	return ((val % MEM_SIZE) % IDX_MOD);
}


int		reverse_bytes(t_vm *vm, unsigned int pc, int bytes)
{
	unsigned char bytes2[2];
	unsigned char bytes4[4];

	if (bytes == 4)
	{
		bytes4[0] = vm->ram.arena[mem_mod(pc + 3)];
		bytes4[1] = vm->ram.arena[mem_mod(pc + 2)];
		bytes4[2] = vm->ram.arena[mem_mod(pc + 1)];
		bytes4[3] = vm->ram.arena[mem_mod(pc)];
		return (*(int*)&bytes4[0]);
	}
	if (bytes == 2)
	{
		bytes2[0] = vm->ram.arena[mem_mod(pc + 1)];
		bytes2[1] = vm->ram.arena[mem_mod(pc)];
		return (*(short*)&bytes2[0]);
	}
	return (-1);
}

/*
** store at register by index
*/

void	store_at(t_vm *vm, t_list *process, unsigned int val, int address)
{
	char i;
	int mod;

	i = 4;
	while (i--)
	{
		mod = mem_mod(address);
		vm->ram.owner[mod] = TPROCES->owner;
		vm->ram.scrb[mod] = TPROCES->owner;
		vm->ram.arena[mod] = val & 0xFF;
		address--;
		address = mem_mod(address);
		val >>= 0b1000;
	}
}

int		get_arg(t_vm *vm, t_list *process, t_uchar *move, t_uchar type)
{
	int		ret;
	int 	value;
	t_uchar	label;

	label = (type >> 0b10) ? 0b10 : 0b100;
	if ((type & 0b11) == REG)
	{
		value = vm->ram.arena[mem_mod(TPROCES->pc + 2 + (*move)++)];
		ret = TPROCES->reg[value - 1];
	}
	else if ((type & 0b11) == DIR)
	{
		ret = reverse_bytes(vm, TPROCES->pc + 2 + *move, label);
		*move += label;
	}
	else
	{
		value = reverse_bytes(vm, TPROCES->pc + 2 + *move, 2) % IDX_MOD;
		ret = reverse_bytes(vm, TPROCES->pc + value, 4);
		*move += 2;
	}
	return (ret);
}
