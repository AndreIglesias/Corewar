/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 19:42:06 by ciglesia          #+#    #+#             */
/*   Updated: 2020/09/27 17:51:54 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disasm.h"

int		valid_magic(char *file)
{
	unsigned char	exec_magic[4];
	int				fd;

	if ((fd = open(file, O_RDONLY)) < 0)
	{
		close(fd);
		ft_printf_fd(2, ERROR": %s: Couldn't open file.\n"E0M, file);
		return (EXIT_FAILURE);
	}
	read(fd, &exec_magic[3], 1);
	read(fd, &exec_magic[2], 1);
	read(fd, &exec_magic[1], 1);
	read(fd, &exec_magic[0], 1);
	if (*(unsigned int*)exec_magic != COREWAR_EXEC_MAGIC)
	{
		ft_printf_fd(2, ERROR": %s: Improper exec_magic\n"E0M, file);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int		valid_header(t_file *file)
{
	if (!file_name(file->name, ".cor"))
	{
		ft_printf(E0M);
		return (EXIT_FAILURE);
	}
	if ((file->fd = open(file->name, O_RDONLY)) < 0 || read(file->fd, NULL, 0))
	{
		ft_printf_fd(2, ERROR": %s: Couldn't open file.\n"E0M, file->name);
		return (EXIT_FAILURE);
	}
	if (lseek(file->fd, 0, SEEK_END) - sizeof(t_header) > CHAMP_MAX_SIZE)
	{
		close(file->fd);
		ft_printf_fd(2, ERROR": %s: Improper champion's size\n"E0M, file->name);
		return (EXIT_FAILURE);
	}
	close(file->fd);
	if (valid_magic(file->name) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
