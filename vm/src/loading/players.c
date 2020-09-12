/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   players.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 17:09:58 by ciglesia          #+#    #+#             */
/*   Updated: 2020/09/12 14:43:15 by ciglesia         ###   ########.fr       */
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

void		kill_players(t_vm *vm)
{
	t_player *champion;
	t_player *aux;

	champion = vm->player;
	while (champion)
	{
		ft_printf("killing: %s\n", champion->name);
		aux = champion;
		champion = champion->next;
		free(aux);
	}
	vm->player = NULL;
}
