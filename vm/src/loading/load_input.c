/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 19:39:22 by ciglesia          #+#    #+#             */
/*   Updated: 2020/10/01 11:45:59 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		load_player(t_vm *vm, char *file, int nplayer)
{
	int			fd;
	int			size;
	t_player	*new;

	if ((fd = open(file, O_RDONLY)) < 0)
	{
		ft_printf_fd(2, ERROR": %s: Couldn't open file."E0M, file);
		return (EXIT_FAILURE);
	}
	new = new_player();
	read(fd, &new->exec_magic, sizeof(int));
	read(fd, &new->name, PROG_NAME_LENGTH);
	lseek(fd, 8, SEEK_CUR);
	read(fd, &new->comment, COMMENT_LENGTH);
	lseek(fd, 4, SEEK_CUR);
	size = read(fd, &new->code, CHAMP_MAX_SIZE);
	new->nplayer = (nplayer > 0) ? nplayer : -vm->nplayers - 1;
	new->prog_size = size;
	new->nblive = 0;
	new->last_live_cycle = 0;
	close(fd);
	add_player(vm, new);
	return (EXIT_SUCCESS);
}

int		load_input(t_vm *vm, int ac, char **av)
{
	int i;
	int nb;

	i = 1;
	vm->ncurses = is_ncurses(i, ac, av);
	i += vm->ncurses;
	if ((i < ac) && ft_strcmp(av[i], "-dump") == 0)
	{
		vm->dump_param = ft_atoi(av[i + 1]);
		i += 2;
	}
	vm->verbosity = ((i < ac) && ft_strcmp(av[i], "-v") == 0);
	i += vm->verbosity;
	while (i < ac)
	{
		nb = -1;
		if (ft_strcmp(av[i], "-n") == 0)
		{
			nb = ft_atoi(av[i + 1]);
			i += 2;
		}
		load_player(vm, av[i++], nb);
	}
	return (EXIT_SUCCESS);
}
