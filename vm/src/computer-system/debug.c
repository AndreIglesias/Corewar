/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 14:44:58 by ciglesia          #+#    #+#             */
/*   Updated: 2020/08/28 14:28:29 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "vm.h"

void	print_ram(t_vm *vm)
{
	int i;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (vm->ram.owner[i] == 0)
			ft_printf(GRAY"%.2x"E0M, vm->ram.arena[i]);
		else if (vm->ram.owner[i] == 1)
			ft_printf(GREEN"%.2x"E0M, vm->ram.arena[i]);
		else if (vm->ram.owner[i] == 2)
			ft_printf(CYAN"%.2x"E0M, vm->ram.arena[i]);
		else if (vm->ram.owner[i] == 3)
			ft_printf(BLUE"%.2x"E0M, vm->ram.arena[i]);
		else
			ft_printf(YELLOW"%.2x"E0M, vm->ram.arena[i]);
		if (i != 1 && (i + 1) % 32 == 0)
			ft_printf("\n");
		i++;
	}
}
