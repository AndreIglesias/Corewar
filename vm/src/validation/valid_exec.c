/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 19:42:06 by ciglesia          #+#    #+#             */
/*   Updated: 2020/09/12 19:02:46 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		valid_magic(char *file)
{
	unsigned char	exec_magic[4];
	int				fd;

	if ((fd = open(file, O_RDONLY)) < 0)
	{
		close(fd);
		ft_printf_fd(2, ERROR": %s: Couldn't open file.\n", file);
		return (EXIT_FAILURE);
	}
	read(fd, &exec_magic[3], 1);
	read(fd, &exec_magic[2], 1);
	read(fd, &exec_magic[1], 1);
	read(fd, &exec_magic[0], 1);
	if (*(unsigned int*)exec_magic != COREWAR_EXEC_MAGIC)
	{
		ft_printf_fd(2, ERROR": %s: Improper exec_magic\n", file);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int		valid_header(int fd, char *file)
{
	if (lseek(fd, 0, SEEK_END) - sizeof(t_header) > CHAMP_MAX_SIZE)
	{
		close(fd);
		ft_printf_fd(2, ERROR": %s: Improper champion's size\n", file);
		return (EXIT_FAILURE);
	}
	close(fd);
	if (valid_magic(file) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
