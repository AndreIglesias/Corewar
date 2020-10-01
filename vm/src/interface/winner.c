/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   winner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 19:31:11 by ciglesia          #+#    #+#             */
/*   Updated: 2020/09/30 20:07:42 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	champion_won(WINDOW *win, t_vm *vm, t_player *champion, int color)
{
	wattron(win, COLOR_PAIR(color));
	mvwprintw(win, vm->p_height / 2 - 3, 2,"WINNER!");
	mvwprintw(win, vm->p_height / 2 - 1, 5, "PLAYER: %d", vm->last_alive);
	mvwprintw(win, vm->p_height / 2, 5, "%s", champion->name);
	wattroff(win, COLOR_PAIR(color));
	wrefresh(win);
}
