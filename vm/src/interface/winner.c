/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   winner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 19:31:11 by ciglesia          #+#    #+#             */
/*   Updated: 2020/10/01 19:52:56 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	champion_won(WINDOW *win, t_vm *vm, t_player *champion, int color)
{
	refresh();
	delwin(win);
	win = newwin(vm->p_height, vm->s_width + 2, vm->proc_y, vm->width + 2);
	wattron(win, A_BOLD);
	mvwprintw(win, 1, 0, " _____________PROCESSES_(000 / %03d)__________\
_______", vm->nprocess);
	wattroff(win, A_BOLD);
	wattron(win, COLOR_PAIR(color));
	mvwprintw(win, vm->p_height / 2 - 3, 2, "WINNER!");
	mvwprintw(win, vm->p_height / 2 - 1, 5, "PLAYER: %d", vm->last_alive);
	mvwprintw(win, vm->p_height / 2, 5, "%s", champion->name);
	wattroff(win, COLOR_PAIR(color));
	box(win, 0, 0);
	wrefresh(win);
}
