/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_source.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 17:18:06 by ciglesia          #+#    #+#             */
/*   Updated: 2020/09/27 17:49:08 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disasm.h"

void	write_header(t_file *file)
{
	ft_printf_fd(file->fd, ".name \"%s\"\n", file->playername);
	ft_printf_fd(file->fd, ".comment \"%s\"\n", file->playername);
}

int		init_writing(t_file *file)
{
	char	*name;
	int		i;

	if (!(name = ft_strnew(ft_strlen(file->name) + 3)))
		return (EXIT_FAILURE);
	i = 0;
	while (file->name[i] != '.')
	{
		name[i] = file->name[i];
		i++;
	}
	ft_strcat(name, "-dis.s");
	free(file->name);
	file->name = name;
	if ((file->fd = open(file->name, O_RDWR | O_CREAT, 00666)) == -1)
		return (ft_puterr(ERROR": Couldn't write file"E0M, EXIT_FAILURE));
	write_header(file);
	return (EXIT_SUCCESS);
}
