/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 19:42:06 by ciglesia          #+#    #+#             */
/*   Updated: 2020/10/13 21:00:41 by ciglesia         ###   ########.fr       */
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

int		diff_size(char *file, long size)
{
	int		fd;
	t_uchar	prog_size[8];

	ft_memset(prog_size, 0, 8);
	if ((fd = open(file, O_RDONLY)) < 0)
	{
		close(fd);
		ft_printf_fd(2, ERROR": %s: Couldn't open file.\n", file);
		return (EXIT_FAILURE);
	}
	lseek(fd, sizeof(int) + PROG_NAME_LENGTH, SEEK_CUR);
	read(fd, &prog_size[7], 1);
	read(fd, &prog_size[6], 1);
	read(fd, &prog_size[5], 1);
	read(fd, &prog_size[4], 1);
	read(fd, &prog_size[3], 1);
	read(fd, &prog_size[2], 1);
	read(fd, &prog_size[1], 1);
	read(fd, &prog_size[0], 1);
	close(fd);
	if (*(long*)&prog_size[0] == size)
		return (EXIT_SUCCESS);
	ft_printf_fd(2, ERROR": %s: Header(%ld) and actual(%ld) program size \
differs\n", file, *(long*)&prog_size[0], size);
	return (EXIT_FAILURE);
}

int		valid_header(int fd, char *file)
{
	int		size;

	size = lseek(fd, 0, SEEK_END) - sizeof(t_header);
	if (size > CHAMP_MAX_SIZE)
	{
		close(fd);
		ft_printf_fd(2, ERROR": %s: Improper champion's size\n", file);
		return (EXIT_FAILURE);
	}
	close(fd);
	if (diff_size(file, size) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (valid_magic(file) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
