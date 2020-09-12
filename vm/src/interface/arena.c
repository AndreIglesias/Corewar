/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 20:41:28 by ciglesia          #+#    #+#             */
/*   Updated: 2020/09/12 21:11:28 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		fill_arena(int height, t_vm *vm, t_matrix m, WINDOW *win)
{
	int ow;

	while (m.i < MEM_SIZE)
	{
		wattron(win, COLOR_PAIR((vm->ram.owner[m.i] == 0 && is_pc(vm->processes,
								m.i)) ? 6 : vm->ram.owner[m.i] + 1));
		if (vm->ram.scrb[m.i] != 0)
			wattron(win, A_BOLD);
		if (vm->ram.owner[m.i] != 0 && (ow = is_ir(vm->processes, m.i)))
			wattron(win, A_STANDOUT | COLOR_PAIR(ow + 1));
		mvwprintw(win, m.row, m.col, "%.2x ", vm->ram.arena[m.i]);
		if (vm->ram.scrb[m.i] != 0)
			wattroff(win, A_BOLD);
		if (vm->ram.owner[m.i] != 0 && is_ir(vm->processes, m.i))
			wattroff(win, A_STANDOUT | COLOR_PAIR(ow + 1));
		wattroff(win, COLOR_PAIR(vm->ram.owner[m.i] + 1));
		m.col += 3;
		if (m.i != 1 && (m.i + 1) % (height) == 0)
		{
			mvwprintw(win, m.row, m.col, "\n");
			m.row++;
			m.col = 1;
		}
		m.i++;
	}
}

void		print_processes(WINDOW *window, t_list *process, t_vm *vm, int i)
{
	int n;
	int ir;

	n = 1;
	wattron(window, A_BOLD);
	mvwprintw(window, ++i, 0, " __________________PROCESSES_(%d)_______________\
____", vm->process_alive);
	wattroff(window, A_BOLD);
	i++;
	while (process)
	{
		wattron(window, COLOR_PAIR(((TP*)P->obj)->owner + 1));
		mvwprintw(window, i + 1, 1, "Process %d PC:", n++);
		wattroff(window, COLOR_PAIR(((TP*)P->obj)->owner + 1));
		mvwprintw(window, i + 1, 15, "%d", ((TP*)P->obj)->pc);
		ir = ((TP*)P->obj)->last_ir;
		wattron(window, COLOR_PAIR(((TP*)P->obj)->owner + 1));
		mvwprintw(window, i + 1, 25, "OP: ");
		wattron(window, COLOR_PAIR(5) | A_BOLD);
		mvwprintw(window, i + 1, 30, "%s", (0 < ir && ir <= 15) ?
					g_op_tab[ir - 1].name : "(null)");
		i++;
		wattroff(window, COLOR_PAIR(5) | A_BOLD);
		process = process->next;
	}
}

void		print_header(WINDOW *win, t_vm *vm)
{
	wattron(win, A_BOLD);
	mvwprintw(win, 1, 1, "CYCLES\t\t%d", vm->cycles);
	mvwprintw(win, 1, 35, (vm->pause) ? "** PAUSED **" : "** RUNNING **");
	mvwprintw(win, 2, 1, "CYCLE_TO_DIE\t%d", vm->cycle_to_die);
	mvwprintw(win, 2, 35, "Speed: %d", 50000 - vm->speed);
	mvwprintw(win, 3, 1, "CYCLE_DELTA\t%d", CYCLE_DELTA);
	mvwprintw(win, 4, 1, "MAX CHECKS\t%d", MAX_CHECKS);
	mvwprintw(win, 5, 1, "CHECK\t\t%d\n", vm->nchecks);
	mvwprintw(win, 6, 1, "__________________________________________________");
	wattroff(win, A_BOLD);
}

void		print_panel(WINDOW *win, t_list *process, t_vm *vm)
{
	int			i;
	t_player	*champion;

	print_header(win, vm);
	champion = vm->player;
	i = 8;
	while (champion)
	{
		wattron(win, A_BOLD);
		mvwprintw(win, i, 1, "PLAYER %d", champion->nplayer);
		wattroff(win, A_BOLD);
		wattron(win, COLOR_PAIR((i - 8) / 5 + 2));
		mvwprintw(win, i + 1, 1, "\t\t(%s)", champion->name);
		wattroff(win, COLOR_PAIR((i - 8) / 5 + 2));
		mvwprintw(win, i + 2, 1, "Last live: \t\t\t%d",
													champion->last_live_cycle);
		mvwprintw(win, i + 3, 1, "Lives in current period: \t%d",
															champion->nblive);
		champion = champion->next;
		i += 5;
	}
	print_processes(vm->p_win, process, vm, 0);
}
