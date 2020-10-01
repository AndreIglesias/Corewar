/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   players.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 17:09:58 by ciglesia          #+#    #+#             */
/*   Updated: 2020/09/30 20:05:48 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_player	*new_player(void)
{
	t_player *new;

	new = NULL;
	if (!(new = (t_player*)malloc(sizeof(t_player))))
		return (NULL);
	ft_memset(new->name, 0, PROG_NAME_LENGTH);
	ft_memset(new->comment, 0, COMMENT_LENGTH);
	ft_memset(new->code, 0, CHAMP_MAX_SIZE);
	new->nplayer = -1;
	new->prog_size = 0;
	new->exec_magic = 0;
	new->pc_address = 0;
	new->nblive = 0;
	new->last_live_cycle = 0;
	new->next = NULL;
	return (new);
}

void		add_player(t_vm *vm, t_player *new)
{
	new->next = vm->player;
	vm->player = new;
	vm->nplayers++;
}

void		player_won(t_vm *vm, t_player *champion, int ncurses)
{
	int color;

	color = 1;
	while (champion)
	{
		color++;
		if (vm->last_alive == champion->nplayer)
		{
			if (ncurses)
			{
				champion_won(vm->p_win, vm, champion, color);
				while (getch() != 'q')
				{
					resize_window(vm);
					champion_won(vm->p_win, vm, champion, color);
				}
				endwin();
				return ;
			}
			ft_printf("Player %d (%s) won\n", vm->last_alive, champion->name);
			return ;
		}
		champion = champion->next;
	}
	(ncurses) ? endwin() : 0;
}

void		kill_players(t_vm *vm)
{
	t_player *champion;
	t_player *aux;

	champion = vm->player;
	while (champion)
	{
		(vm->verbosity) ? ft_printf(CYAN"Killing: %s\n"E0M, champion->name) : 0;
		aux = champion;
		champion = champion->next;
		free(aux);
	}
	vm->player = NULL;
}
