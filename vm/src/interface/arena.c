/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 20:41:28 by ciglesia          #+#    #+#             */
/*   Updated: 2020/08/31 20:01:15 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "vm.h"

static int is_ir(t_list *process, int i)
{
	while (process)
	{
		if (i == TPROCES->pc && (TPROCES->ir > 0 && TPROCES->ir <= 15))
			return (TPROCES->owner);
		process = process->next;
	}
	return (0);
}

static int is_pc(t_list *process, int i)
{
	while (process)
	{
		if (i == TPROCES->pc)
			return (1);
		process = process->next;
	}
	return (0);
}

void	fill_arena(int height, t_vm *vm, t_matrix m, WINDOW *mainWin)
{
	int ow;

	while (m.i < MEM_SIZE)
	{
		if (vm->ram.owner[m.i] == 0 && is_pc(vm->processes, m.i))
			wattron(mainWin, COLOR_PAIR(6));
		else
			wattron(mainWin, COLOR_PAIR(vm->ram.owner[m.i] + 1));
		if (vm->ram.scrb[m.i] != 0)
			wattron(mainWin, A_BOLD);
		if (vm->ram.owner[m.i] != 0 && (ow = is_ir(vm->processes, m.i)))
			wattron(mainWin, A_STANDOUT | COLOR_PAIR(ow + 1));
		mvwprintw(mainWin, m.row, m.col, "%.2x ", vm->ram.arena[m.i]);
		if (vm->ram.scrb[m.i] != 0)
			wattroff(mainWin, A_BOLD);
		if (vm->ram.owner[m.i] != 0 && is_ir(vm->processes, m.i))
			wattroff(mainWin, A_STANDOUT | COLOR_PAIR(ow + 1));
		wattroff(mainWin, COLOR_PAIR(vm->ram.owner[m.i] + 1));
		m.col += 3;
		if (m.i != 1 && (m.i + 1) % (height) == 0)
		{
			mvwprintw(mainWin, m.row, m.col, "\n");
			m.row++;
			m.col = 1;
		}
		m.i++;
	}
}

void	print_panel(WINDOW *sideWin, t_list *process, t_vm *vm)
{
	int i;
	int n;
	int ir;
	t_player *champion;

	wattron(sideWin, A_BOLD);
	mvwprintw(sideWin, 1, 1, "CYCLES\t\t%d", vm->cycles);
	mvwprintw(sideWin, 2, 1, "CYCLE_TO_DIE\t%d", vm->cycle_to_die);
	mvwprintw(sideWin, 3, 1, "CYCLE_DELTA\t%d", CYCLE_DELTA);
	mvwprintw(sideWin, 4, 1, "MAX CHECKS\t%d", MAX_CHECKS);
	mvwprintw(sideWin, 5, 1, "CHECK\t\t%d\n", vm->nchecks);
	mvwprintw(sideWin, 6, 1, "----------------------------------------");
	wattroff(sideWin, A_BOLD);
	champion = vm->player;
	i = 2;
	while (champion)
	{
		mvwprintw(sideWin, i * 4, 1, "PLAYER %d", champion->nplayer);
		wattron(sideWin, COLOR_PAIR(i));
		mvwprintw(sideWin, i * 4 + 1, 1, "\t\t(%s)", champion->name);
		wattroff(sideWin, COLOR_PAIR(i));
		mvwprintw(sideWin, i * 4 + 2, 1, "Last live: \t\t\t%d", champion->last_live_cycle);
		mvwprintw(sideWin, i * 4 + 3, 1, "Lives in current period: \t%d", champion->nblive);
		champion = champion->next;
		i++;
	}
	wattron(sideWin, A_BOLD);
	mvwprintw(sideWin, i*4, 1, "----------------------------------------");
	wattroff(sideWin, A_BOLD);
	n = 1;
	while (process)
	{
		wattron(sideWin, COLOR_PAIR(TPROCES->owner + 1));
		mvwprintw(sideWin, i * 4 + 2, 1, "Process %d PC:\t%d", n++, TPROCES->pc);
		ir = TPROCES->last_ir;
		mvwprintw(sideWin, i * 4 + 3, 1, "\t\tOP:%s", (0 < ir && ir <= 15) ?
				  op_tab[ir - 1].name : "(null)");
		i++;
		wattroff(sideWin, COLOR_PAIR(TPROCES->owner + 1));
		process = process->next;
	}
}
