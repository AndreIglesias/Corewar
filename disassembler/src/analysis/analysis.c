/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analysis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 11:01:06 by ciglesia          #+#    #+#             */
/*   Updated: 2020/09/27 17:53:59 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disasm.h"

int		is_op(t_file *file, int *i)
{
	t_uchar	byte;

	byte = file->code[*i];
	if (1 <= byte && byte <= 16)
	{
		ft_printf_fd(file->fd, "%s\t", g_w_tab[byte - 1].name);
		if (ft_strlen(g_w_tab[byte - 1].name) < 4)
			ft_printf_fd(file->fd, "\t");
		g_w_tab[byte - 1].f(file, i);
		ft_printf_fd(file->fd, "\n");
		return (1);
	}
	return (0);
}

int		disassemble(t_file *file)
{
	int i;

	i = 0;
	while (file->prog_size - i)
	{
		if (!is_op(file, &i))
			break ;
	}
	return (EXIT_SUCCESS);
}
