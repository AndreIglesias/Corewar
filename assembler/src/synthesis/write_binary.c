/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_binary.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarault <fgarault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 12:48:19 by fgarault          #+#    #+#             */
/*   Updated: 2020/09/30 11:55:48 by fgarault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int		compiled_name(t_file *file)
{
	int			i;
	char		*name;
	int			fd;

	i = 0;
	fd = 0;
	if (!(name = ft_strnew(ft_strlen(file->name))))
		return (-1);
	while (file->name[i] != '.')
	{
		name[i] = file->name[i];
		i++;
	}
	ft_strcat(name, ".cor");
	if ((fd = open(name, O_RDWR | O_CREAT, 00666)) == -1)
	{
		free(name);
		return (-1);
	}
	free(name);
	return (fd);
}

static int		write_header(t_file *file, int fd)
{
	t_uchar		magic[4];
	t_uchar		size[8];
	int			i;

	ft_bzero(magic, 4);
	ft_bzero(size, 8);
	i = 0;
	itob(magic, COREWAR_EXEC_MAGIC, 4);
	itob(size, file->prog_size, 8);
	write(fd, magic, 4);
	write(fd, file->playername, PROG_NAME_LENGTH);
	write(fd, size, 8);
	write(fd, file->comment, COMMENT_LENGTH);
	while (i++ < 4)
		ft_printf_fd(fd, "%c", 0);
	return (1);
}

static void		write_prog(t_file *file, int fd)
{
	t_code			*tab;
	t_instruction	*ins;
	t_args			*arg;

	tab = file->code_tab;
	while (tab)
	{
		ins = tab->instr;
		while (ins)
		{
			arg = ins->args;
			write(fd, &ins->opcode, 1);
			ins->nargs > 1 ? write(fd, &ins->acb, 1) : 0;
			while (arg)
			{
				write(fd, arg->hex, arg->size);
				arg = arg->next;
			}
			ins = ins->next;
		}
		tab = tab->next;
	}
}

int				writing_exec(t_file *file)
{
	int		fd;

	if ((fd = compiled_name(file)) < 0)
	{
		ft_printf_fd(2, "Failed to create %s", file->name);
		return (EXIT_FAILURE);
	}
	if (!write_header(file, fd))
		return (EXIT_FAILURE);
	write_prog(file, fd);
	close(fd);
	return (EXIT_SUCCESS);
}
