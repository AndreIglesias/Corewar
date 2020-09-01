/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 15:07:58 by ciglesia          #+#    #+#             */
/*   Updated: 2020/09/01 18:14:46 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	init_colors()
{
	start_color();
	init_color(COLOR_YELLOW, 180, 180, 180);
	init_color(COLOR_CYAN, 0, 850, 850);
	init_color(COLOR_BLUE, 400, 400, 1000);
	init_color(COLOR_GREEN, 0, 800, 0);
	init_color(COLOR_RED, 900, 0, 0);
	init_color(COLOR_BLACK, 0, 0, 0);
	init_pair(1, COLOR_YELLOW, COLOR_BLACK);
	init_pair(2, COLOR_CYAN, COLOR_BLACK);
	init_pair(3, COLOR_BLUE, COLOR_BLACK);
	init_pair(4, COLOR_RED, COLOR_BLACK);
	init_pair(5, COLOR_GREEN, COLOR_BLACK);
	init_pair(6, COLOR_BLACK, COLOR_YELLOW);
}

static t_matrix init_m()
{
	t_matrix m;

	m.row = 1;
	m.col = 1;
	m.i = 0;
	return (m);
}

void	resize_window(t_vm *vm)
{
	refresh();
	delwin(vm->mainWin);
	delwin(vm->sideWin);
	vm->mainWin = newwin(vm->height + 2, vm->width + 2, 0, 0);
	vm->sideWin = newwin(vm->height - vm->procHeight + 2, vm->sideWidth + 2, 0,
						 vm->width + 2);
	vm->processWin = newwin(vm->procHeight, vm->sideWidth + 2, vm->proc_y,
							vm->width + 2);
	fill_arena(vm->height, vm, init_m(), vm->mainWin);
	print_panel(vm->sideWin, vm->processes, vm);
	box(vm->mainWin, 0, 0);
	box(vm->sideWin, 0, 0);
	box(vm->processWin, 0, 0);
	wrefresh(vm->mainWin);
	wrefresh(vm->sideWin);
	wrefresh(vm->processWin);
}

int		print_arena(t_vm *vm)
{
	initscr();
	noecho();
	nodelay(stdscr, TRUE);
	keypad(stdscr, TRUE);
	vm->height = ft_sqrt(MEM_SIZE);
	vm->width = vm->height * 3;
	vm->sideWidth = 50;
	vm->proc_y = (5 * vm->nplayers) + 10;
	vm->procHeight = vm->height + 2 - vm->proc_y;
	init_colors();
	resize_window(vm);
	return (0);
}
