/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_ram.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 18:30:54 by ciglesia          #+#    #+#             */
/*   Updated: 2020/09/12 19:38:05 by ciglesia         ###   ########.fr       */
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
		PROCESS->carry = 0;
		PROCESS->nprocess = vm->nprocess;
		PROCESS->pc = champion->pc_address;
		PROCESS->duration = 0;
		PROCESS->ir = -1;
		PROCESS->live_count = 0;
		PROCESS->live_since = 0;
		PROCESS->last_ir = -1;
		PROCESS->owner = i + 1;
		ft_memset(&PROCESS->reg, 0, REG_NUMBER * REG_SIZE);
		PROCESS->reg[0] = champion->nplayer;
		ft_printf("PLAYER %d %s, weight %d bytes\n", PROCESS->reg[0],
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
	PROCESS->carry = TPROCES->carry;
	PROCESS->nprocess = vm->nprocess;
	PROCESS->pc = pc;
	PROCESS->duration = 0;
	PROCESS->ir = -1;
	PROCESS->live_count = TPROCES->live_count;
	PROCESS->live_since = TPROCES->live_since + 1;
	PROCESS->last_ir = -1;
	PROCESS->optab = 0;
	PROCESS->owner = TPROCES->owner;
	ft_memcpy(&PROCESS->reg, &TPROCES->reg, REG_NUMBER * REG_SIZE);
	return (EXIT_SUCCESS);
}
