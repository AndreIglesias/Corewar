/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op1_5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 10:27:17 by ciglesia          #+#    #+#             */
/*   Updated: 2020/09/27 18:02:31 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disasm.h"

void							w_live(t_file *file, int *pos)
{
	int live;

	live = reverse_bytes(file->code, *pos + 1, 4);
	ft_printf_fd(file->fd, "%%%d", live);
	*pos += 5;
}

void							w_ld(t_file *file, int *pos)
{
	t_uchar	acb;
	int		reg;
	int		move;

	acb = file->code[*pos + 1];
	reg = *pos + 6 - ((acb & 0b01100000) >> 5);
	if (((p_acb(acb, 1) == DIR || p_acb(acb, 1) == IND) && p_acb(acb, 2) == REG)
		&& is_reg(file->code, reg))
	{
		if (p_acb(acb, 1) == DIR)
		{
			move = reverse_bytes(file->code, *pos + 2, 4);
			ft_printf_fd(file->fd, "%%%d, ", move);
		}
		else
		{
			move = reverse_bytes(file->code, *pos + 2, 2) % IDX_MOD;
			ft_printf_fd(file->fd, "%d, ", move);
		}
		ft_printf_fd(file->fd, "r%d", file->code[reg]);
	}
	*pos += octal_shift(acb, 4, 2);
}

void							w_st(t_file *file, int *pos)
{
	t_uchar	acb;
	int		move;

	acb = file->code[*pos + 1];
	if (p_acb(acb, 1) == REG && is_reg(file->code, *pos + 2))
	{
		ft_printf_fd(file->fd, "r%d, ", file->code[*pos + 2]);
		if (p_acb(acb, 2) == REG && is_reg(file->code, *pos + 3))
			ft_printf_fd(file->fd, "r%d", file->code[*pos + 3]);
		else if (p_acb(acb, 2) == IND)
		{
			move = reverse_bytes(file->code, *pos + 3, 2);
			ft_printf_fd(file->fd, "%d", move);
		}
	}
	*pos += octal_shift(acb, 4, 2);
}

void							w_add(t_file *file, int *pos)
{
	t_uchar	acb;

	acb = file->code[*pos + 1];
	if (is_argsize(3, acb, 3) && is_reg(file->code, *pos + 2) &&
		is_reg(file->code, *pos + 3) && is_reg(file->code, *pos + 4))
	{
		ft_printf_fd(file->fd, "r%d, ", file->code[*pos + 2]);
		ft_printf_fd(file->fd, "r%d, ", file->code[*pos + 3]);
		ft_printf_fd(file->fd, "r%d", file->code[*pos + 4]);
	}
	*pos += octal_shift(acb, 4, 3);
}

void							w_sub(t_file *file, int *pos)
{
	t_uchar	acb;

	acb = file->code[*pos + 1];
	if (is_argsize(4, acb, 3) && is_reg(file->code, *pos + 2) &&
		is_reg(file->code, *pos + 3) && is_reg(file->code, *pos + 4))
	{
		ft_printf_fd(file->fd, "r%d, ", file->code[*pos + 2]);
		ft_printf_fd(file->fd, "r%d, ", file->code[*pos + 3]);
		ft_printf_fd(file->fd, "r%d", file->code[*pos + 4]);
	}
	*pos += octal_shift(acb, 4, 3);
}
