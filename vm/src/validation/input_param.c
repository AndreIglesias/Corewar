/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_param.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 18:53:16 by ciglesia          #+#    #+#             */
/*   Updated: 2020/10/01 11:44:18 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int	print_usage(void)
{
	char *str;

	str = ft_itoa(CHAMP_MAX_SIZE);
	ft_putstr_fd(E0M, 2);
	ft_puterr(BOLD"USAGE"E0M": ./corewar [-n | -dump nbr_cycles] [-v] \
[[-n number] champion.cor] ...\n", 0);
	ft_puterr(BOLD"-n"E0M" :\t\t\t Ncurses display\n", 0);
	ft_puterr(BOLD"-dump"E0M" nbr_cycles:\t After nbr_cycles \
dump the memory and quit the game", 0);
	ft_puterr("\t\t\t must be dumped in hexadecimal format with 32 octets \
per line.\n", 0);
	ft_puterr(BOLD"-v"E0M" :\t\t\t Verbosity\n", 0);
	ft_puterr(BOLD"-n"E0M" number:\t\t The number of the player \
"ITALIC"(positive int)"E0M, 0);
	ft_puterr("\t\t\t if non-existent, the player's number will be generated \
automatically.\n", 0);
	ft_puterr("\t\t\t The last player will have the first process in order of \
execution.\n", 0);
	ft_printf_fd(2, ITALIC"The champions (max: %d) cannot go over CHAMP_MAX_\
SIZE (%s), otherwise it is an "BLINK"ERROR\n\n"E0M, MAX_PLAYERS, str);
	free(str);
	return (EXIT_FAILURE);
}

static int	valid_format(int ac, char **av, int *np)
{
	int		i;
	int		eparam;
	int		nplayers;

	i = 1;
	i += is_ncurses(i, ac, av);
	if ((eparam = is_dump(i, ac, av)) < 0)
		return (EXIT_FAILURE);
	i += eparam;
	i += ((i < ac) && ft_strcmp(av[i], "-v") == 0);
	nplayers = 0;
	while (i < ac)
	{
		if ((av[i][0] == '-' && ft_strcmp(av[i], "-n") != 0) ||
			((eparam = is_champion(i, ac, av, np)) < 0))
			return (EXIT_FAILURE);
		if (nplayers >= MAX_PLAYERS)
			return (ft_puterr(ERROR": Too many champions", EXIT_FAILURE));
		nplayers += (eparam > i) ? 1 : 0;
		i = (eparam > i) ? eparam : i;
	}
	return ((nplayers) ? EXIT_SUCCESS : ft_puterr(ERROR": Need at least 1 \
player", EXIT_FAILURE));
}

int			valid_input(int ac, char **av)
{
	int	np[MAX_PLAYERS];

	ft_memset(np, 0, MAX_PLAYERS);
	ft_putstr_fd(RED, 2);
	if (ac < 2 || valid_format(ac, av, np) == EXIT_FAILURE)
		return (print_usage());
	ft_putstr_fd(E0M, 2);
	return (EXIT_SUCCESS);
}
