/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 15:07:58 by ciglesia          #+#    #+#             */
/*   Updated: 2020/09/12 20:01:39 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		init_colors(void)
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

static t_matrix	init_m(void)
{
	t_matrix m;

	m.row = 1;
	m.col = 1;
	m.i = 0;
	return (m);
}

int				ncupdate(t_vm *vm, int input)
{
	if (input == 'q')
		return (1);
	if (input == ' ')
	{
		nodelay(stdscr, vm->pause);
		vm->pause = ft_mod(vm->pause + 1, 2);
	}
	if (input == KEY_RESIZE || input == ' ')
		resize_window(vm);
	if (vm->pause)
		return (2);
	else
		resize_window(vm);
	if (input == KEY_UP && vm->speed > MAX_SPEED)
		vm->speed -= 500;
	if (input == KEY_DOWN && vm->speed < MIN_SPEED)
		vm->speed += 500;
	if (input != KEY_RESIZE)
		usleep(vm->speed);
	return (0);
}

void			resize_window(t_vm *vm)
{
	refresh();
	delwin(vm->m_win);
	delwin(vm->s_win);
	delwin(vm->p_win);
	vm->m_win = newwin(vm->height + 2, vm->width + 2, 0, 0);
	vm->s_win = newwin(vm->height - vm->p_height + 2, vm->s_width + 2, 0,
						vm->width + 2);
	vm->p_win = newwin(vm->p_height, vm->s_width + 2, vm->proc_y,
							vm->width + 2);
	fill_arena(vm->height, vm, init_m(), vm->m_win);
	print_panel(vm->s_win, vm->processes, vm);
	box(vm->m_win, 0, 0);
	box(vm->s_win, 0, 0);
	box(vm->p_win, 0, 0);
	wrefresh(vm->m_win);
	wrefresh(vm->s_win);
	wrefresh(vm->p_win);
}

int				print_arena(t_vm *vm)
{
	initscr();
	noecho();
	keypad(stdscr, TRUE);
	vm->height = ft_sqrt(MEM_SIZE);
	vm->width = vm->height * 3;
	vm->s_width = 50;
	vm->proc_y = (5 * vm->nplayers) + 10;
	vm->p_height = vm->height + 2 - vm->proc_y;
	init_colors();
	resize_window(vm);
	return (0);
}
