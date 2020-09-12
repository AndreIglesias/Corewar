/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logical_management.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 17:36:04 by ciglesia          #+#    #+#             */
/*   Updated: 2020/09/12 21:32:50 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			player_alive(t_vm *vm, int live)
{
	t_player *champion;

	champion = vm->player;
	while (champion)
	{
		if (champion->nplayer == live)
		{
			if (!vm->ncurses)
				ft_printf("A process shows that player %d (%s) is alive\n",
						champion->nplayer, champion->name);
			champion->nblive++;
			champion->last_live_cycle = vm->cycles;
			vm->last_alive = champion->nplayer;
			break ;
		}
		champion = champion->next;
	}
}

int				is_reg(t_vm *vm, int nb)
{
	int comp;

	comp = in_mem(vm, nb);
	return (1 <= comp && comp <= 16);
}

void			save_cmp(t_list *process, int id, int comp)
{
	((TP*)P->obj)->reg[id] = comp;
	((TP*)P->obj)->carry = (((TP*)P->obj)->reg[id]) ? 0 : 1;
}

unsigned int	mem_mod(int x)
{
	int ret;

	ret = (unsigned int)(x % MEM_SIZE);
	if (ret < 0)
		return (ret + MEM_SIZE);
	return (ret);
}

int				in_mem(t_vm *vm, int pc)
{
	return (vm->ram.arena[mem_mod(pc)]);
}
