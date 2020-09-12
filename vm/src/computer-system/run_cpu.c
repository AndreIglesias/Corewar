/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cpu.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 22:17:31 by ciglesia          #+#    #+#             */
/*   Updated: 2020/09/12 21:26:53 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	kill_zombies(t_vm *vm, t_list *process)
{
	t_list *prev;

	if ((vm->processes && vm->cycles) && !(vm->cycles % vm->cycle_to_die))
	{
		prev = NULL;
		while (process)
		{
			if (!((TP*)P->obj)->live_count || vm->cycle_to_die < 0)
			{
				if (process == vm->processes)
					vm->processes = process->next;
				else
					prev->next = process->next;
				free(process->obj);
				free(process);
				process = (prev == NULL) ? vm->processes : prev->next;
				vm->process_alive--;
				continue ;
			}
			((TP*)P->obj)->live_count = 0;
			prev = process;
			process = process->next;
		}
	}
}

void	find_ir(t_vm *vm, t_list *process)
{
	int ir;

	ir = vm->ram.arena[((TP*)P->obj)->pc % MEM_SIZE];
	if (0 < ir && ir <= 15)
	{
		((TP*)P->obj)->ir = ir - 1;
		((TP*)P->obj)->last_ir = ir;
		((TP*)P->obj)->duration = g_op_tab[((TP*)P->obj)->ir].cycle - 1;
		return ;
	}
	((TP*)P->obj)->ir = -1;
	((TP*)P->obj)->pc++;
	((TP*)P->obj)->pc %= MEM_SIZE;
}

void	process_operations(t_vm *vm, t_list *process)
{
	int ir;

	if (vm->processes)
	{
		if (vm->cycles % 200 == 0)
			ft_memset(vm->ram.scrb, 0, sizeof(unsigned char) * MEM_SIZE);
		while (process)
		{
			ir = ((TP*)P->obj)->ir;
			if (ir < 0 || 15 < ir)
				find_ir(vm, process);
			if (!((TP*)P->obj)->duration && (0 <= ir && ir <= 15))
			{
				g_op_tab[((TP*)P->obj)->ir].f(vm, process);
				((TP*)P->obj)->ir = -1;
			}
			else
				((TP*)P->obj)->duration--;
			((TP*)P->obj)->live_since++;
			process = process->next;
		}
	}
}

void	update_cycles(t_vm *vm)
{
	int			reduce_cycles;
	t_player	*champion;

	reduce_cycles = 0;
	if (vm->cycles && vm->cycles % vm->cycle_to_die == 0)
	{
		if (vm->nlives >= NBR_LIVE)
			reduce_cycles = 1;
		vm->nchecks = (reduce_cycles) ? 0 : vm->nchecks + 1;
		if (vm->nchecks >= MAX_CHECKS)
			reduce_cycles = 1;
		vm->nlives = 0;
		champion = vm->player;
		while (champion)
		{
			champion->nblive = 0;
			champion = champion->next;
		}
	}
	vm->cycle_to_die -= (reduce_cycles) ? CYCLE_DELTA : 0;
	vm->cycles++;
}

int		run_processes(t_vm *vm)
{
	int			control;
	t_player	*champion;

	while (vm->processes != NULL && vm->cycle_to_die > 0)
	{
		if (vm->ncurses && (control = ncupdate(vm, getch())) && control == 1)
			break ;
		if (vm->ncurses && control == 2)
			continue ;
		if (vm->cycles == vm->dump_param)
			return (EXIT_SUCCESS + print_ram(vm));
		update_cycles(vm);
		process_operations(vm, vm->processes);
		kill_zombies(vm, vm->processes);
	}
	(!vm->ncurses) ? print_ram(vm) : 0;
	champion = vm->player;
	while (champion)
	{
		if (vm->last_alive == champion->nplayer)
			ft_printf("Player %d (%s) won\n", vm->last_alive, champion->name);
		champion = champion->next;
	}
	return (EXIT_SUCCESS);
}
