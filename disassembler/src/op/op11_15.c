/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op11_15.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 10:28:23 by ciglesia          #+#    #+#             */
/*   Updated: 2020/09/27 17:43:45 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disasm.h"

void							w_sti(t_file *file, int *pos)
{
	t_uchar	acb;
	int		args;
	t_uchar	type;
	t_uchar	mv;

	acb = file->code[*pos + 1];
	args = 3;
	mv = 0;
	if (is_argsize(10, acb, args))
	{
		while (args--)
		{
			type = (acb >> ((args + 1) * 2)) & 0b11;
			if (type == REG && !is_reg(file->code, *pos + 2 + mv))
				break ;
			file->type = type + 4;
			get_arg(file->code, *pos, &mv, file);
			if (args)
				ft_printf_fd(file->fd, ", ");
		}
	}
	*pos += octal_shift(acb, 2, 3);
}

void							w_fork(t_file *file, int *pos)
{
	int	move;

	move = reverse_bytes(file->code, *pos + 1, 2);
	ft_printf_fd(file->fd, "%%%d", move);
	*pos += 3;
}

void							w_lld(t_file *file, int *pos)
{
	t_uchar	acb;
	int		reg;
	int		move;

	acb = file->code[*pos + 1];
	if (is_argsize(12, acb, 2))
	{
		reg = *pos + 6 - ((acb & 0b01100000) >> 5);
		if (is_reg(file->code, reg))
		{
			if (p_acb(acb, 1) == DIR)
			{
				move = reverse_bytes(file->code, *pos + 2, 4);
				ft_printf_fd(file->fd, "%%%d, ", move);
			}
			else
			{
				move = reverse_bytes(file->code, *pos + 2, 2);
				ft_printf_fd(file->fd, "%d, ", move);
			}
			ft_printf_fd(file->fd, "r%d", file->code[reg]);
		}
	}
	*pos += octal_shift(acb, 4, 2);
}

void							w_lldi(t_file *file, int *pos)
{
	disect_args(file->code, pos, 2, file);
}

void							w_lfork(t_file *file, int *pos)
{
	int	move;

	move = reverse_bytes(file->code, *pos + 1, 2);
	ft_printf_fd(file->fd, "%%%d", move);
	*pos += 3;
}
