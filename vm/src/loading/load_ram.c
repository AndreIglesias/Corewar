/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_ram.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 18:30:54 by ciglesia          #+#    #+#             */
/*   Updated: 2020/09/12 21:23:40 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		load_champions(t_vm *vm)
{
	t_player	*champion;
	int			space;
	int			ad;
	int			n;
	int			last_alive;

	space = MEM_SIZE / vm->nplayers;
	champion = vm->player;
	ad = 0;
	n = 1;
	vm->last_alive = champion->nplayer;
	while (champion)
	{
		ft_memcpy(&(vm->ram.arena[ad]), champion->code, champion->prog_size);
		ft_memset(&(vm->ram.owner[ad]), n, champion->prog_size);
		champion->pc_address = ad;
		ad += space;
		last_alive = champion->nplayer;
		champion = champion->next;
		n++;
	}
	vm->last_alive = last_alive;
	return (EXIT_SUCCESS);
}

int		load_processes(t_vm *vm, t_player *champion, int i)
{
	t_process	p;

	while (i < vm->nplayers)
	{
		vm->nprocess++;
		vm->process_alive++;
		ft_lstadd(&vm->processes, ft_lstnew(&p, sizeof(t_process)));
		((t_process*)vm->processes->obj)->carry = 0;
		((t_process*)vm->processes->obj)->nprocess = vm->nprocess;
		((t_process*)vm->processes->obj)->pc = champion->pc_address;
		((t_process*)vm->processes->obj)->duration = 0;
		((t_process*)vm->processes->obj)->ir = -1;
		((t_process*)vm->processes->obj)->live_count = 0;
		((t_process*)vm->processes->obj)->live_since = 0;
		((t_process*)vm->processes->obj)->last_ir = -1;
		((t_process*)vm->processes->obj)->owner = i + 1;
		ft_memset(&((t_process*)vm->processes->obj)->reg, 0,
				REG_NUMBER * REG_SIZE);
		((t_process*)vm->processes->obj)->reg[0] = champion->nplayer;
		ft_printf("PLAYER %d %s, weight %d bytes\n", champion->nplayer,
					champion->name, champion->prog_size);
		champion = champion->next;
		i++;
	}
	return (EXIT_SUCCESS);
}

int		add_process(t_vm *vm, t_list *process, unsigned int pc)
{
	t_process p;

	vm->nprocess++;
	vm->process_alive++;
	ft_lstadd(&vm->processes, ft_lstnew(&p, sizeof(t_process)));
	((t_process*)vm->processes->obj)->carry = ((TP*)P->obj)->carry;
	((t_process*)vm->processes->obj)->nprocess = vm->nprocess;
	((t_process*)vm->processes->obj)->pc = pc;
	((t_process*)vm->processes->obj)->duration = 0;
	((t_process*)vm->processes->obj)->ir = -1;
	((t_process*)vm->processes->obj)->live_count = ((TP*)P->obj)->live_count;
	((t_process*)vm->processes->obj)->live_since = ((TP*)P->obj)->live_since
																			+ 1;
	((t_process*)vm->processes->obj)->last_ir = -1;
	((t_process*)vm->processes->obj)->optab = 0;
	((t_process*)vm->processes->obj)->owner = ((TP*)P->obj)->owner;
	ft_memcpy(&((t_process*)vm->processes->obj)->reg, &((TP*)P->obj)->reg,
			REG_NUMBER * REG_SIZE);
	return (EXIT_SUCCESS);
}
