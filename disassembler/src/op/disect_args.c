/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disect_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 15:54:53 by ciglesia          #+#    #+#             */
/*   Updated: 2020/09/27 18:02:50 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disasm.h"

/*
** param l: if 2 -> is load function
** if 0 -> compare function
*/

void		get_arg(t_uchar *code, int pos, t_uchar *move, t_file *file)
{
	int		ret;
	int		value;
	t_uchar	label;
	t_uchar	type;

	type = file->type;
	label = (type >> 0b10) ? 0b10 : 0b100;
	if ((type & 0b11) == REG)
	{
		value = code[pos + 2 + (*move)++];
		ft_printf_fd(file->fd, "r%d", value);
	}
	else if ((type & 0b11) == DIR)
	{
		ret = reverse_bytes(code, pos + 2 + *move, label);
		ft_printf_fd(file->fd, "%%%d", ret);
		*move += label;
	}
	else
	{
		value = reverse_bytes(code, pos + 2 + *move, 2) % IDX_MOD;
		ft_printf_fd(file->fd, "%d", value);
		*move += 2;
	}
}

void		disect_args(t_uchar *code, int *pos, int l, t_file *file)
{
	t_uchar	acb;
	int		args;
	t_uchar	type;
	t_uchar	move;

	args = 3;
	move = 0;
	acb = code[*pos + 1];
	if (is_argsize(code[*pos] - 1, acb, args))
	{
		while (args)
		{
			type = (acb >> ((args--) * 2)) & 0b11;
			if (type == REG && !is_reg(code, *pos + 2 + move))
				break ;
			file->type = type + (l * 2);
			get_arg(code, *pos, &move, file);
			if (args)
				ft_printf_fd(file->fd, ", ");
		}
	}
	*pos += octal_shift(acb, 4 - l, 3);
}
