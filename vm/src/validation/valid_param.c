/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_param.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 18:31:41 by ciglesia          #+#    #+#             */
/*   Updated: 2020/08/27 01:19:50 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		is_dump(int i, int ac, char **av)
{
	if (ft_strcmp(av[i], "-dump") == 0)
	{
		if (((i + 1 >= ac) || !ft_isint(av[i + 1])) || ft_atoi(av[i + 1]) <= 0)
			return (-1 + ft_puterr(ERROR": Improper -dump input", 0));
	}
	else
		return (0);
	return (2);
}

int		cor_file(char *file)
{
	int i;

	i = 0;
	if (ft_strlen(file) < 4)
	{
		ft_printf_fd(2, ERROR": %s: Not a .cor file\n", file);
		return (0);
	}
	while (file[i+4])
		i++;
	if (ft_strcmp(&file[i], ".cor") != 0)
	{
		ft_printf_fd(2, ERROR": %s: Not a .cor file\n", file);
		return (0);
	}
	return (1);
}

int		is_champion(int i, int ac, char **av, int *np)
{
	int fd;
	int npi;

	if (ft_strcmp(av[i], "-n") == 0)
	{
		npi = 0;
		if ((i + 1 >= ac || !ft_isint(av[i + 1])) || ft_atoi(av[i + 1]) <= 0)
			return (-1 + ft_puterr(ERROR": Improper -n input", 0));
		while (np[npi])
			if (ft_atoi(av[i + 1]) == np[npi++])
				return (-1 + ft_puterr(ERROR": Repeated -n input", 0));
		np[npi] = ft_atoi(av[i + 1]);
		i += 2;
	}
	if (i < ac && !cor_file(av[i]))
		return (-1);
	if ((i >= ac || (fd = open(av[i], O_RDONLY)) < 0) || read(fd, NULL, 0))
	{
		ft_printf_fd(2, ERROR": %s: Missing file .cor\n",
					(ac > i) ? av[i] : "(null)");
		return (-1);
	}
	if (valid_header(fd, av[i]) == EXIT_SUCCESS)
		return (i + 1);
	return (-1);
}
