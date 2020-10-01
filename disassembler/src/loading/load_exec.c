/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 00:29:17 by ciglesia          #+#    #+#             */
/*   Updated: 2020/09/23 11:02:54 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disasm.h"

int		load_exec(t_file *file)
{
	int	size;

	if ((file->fd = open(file->name, O_RDONLY)) < 0)
	{
		ft_printf_fd(2, ERROR": %s: Couldn't open file."E0M, file->name);
		return (EXIT_FAILURE);
	}
	read(file->fd, &file->exec_magic, sizeof(int));
	read(file->fd, &file->playername, PROG_NAME_LENGTH);
	lseek(file->fd, 8, SEEK_CUR);
	read(file->fd, &file->comment, COMMENT_LENGTH);
	lseek(file->fd, 4, SEEK_CUR);
	size = read(file->fd, &file->code, CHAMP_MAX_SIZE);
	file->prog_size = size;
	close(file->fd);
	return (EXIT_SUCCESS);
}
