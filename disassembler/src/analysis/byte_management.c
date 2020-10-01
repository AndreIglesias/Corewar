/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   byte_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 11:38:06 by ciglesia          #+#    #+#             */
/*   Updated: 2020/09/27 16:33:24 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disasm.h"

int		is_argsize(t_uchar ir, t_uchar acb, t_uchar narg)
{
	int m;
	int n;
	int i;

	m = 6;
	i = 0;
	while (narg)
	{
		n = 0;
		if ((acb >> m) & 0b11)
			n = 0b01 << (((acb >> m) & 0b11) - 1);
		if (!(n & g_w_tab[ir].args[i]))
			return (0);
		i++;
		narg--;
		m -= 2;
	}
	return (1);
}

int		p_acb(t_uchar acb, int p_number)
{
	if (p_number == 1)
		return ((acb & 0b11000000) >> 6);
	if (p_number == 2)
		return ((acb & 0b110000) >> 4);
	if (p_number == 3)
		return ((acb & 0b1100) >> 2);
	return (EXIT_FAILURE);
}

int		octal_shift(t_uchar acb, t_uchar label_size, t_uchar narg)
{
	int shift;

	shift = 0b10;
	while (++narg <= 0b100)
		acb >>= 0b10;
	while (acb)
	{
		shift += ((acb & 0b11) == REG) ? 1 : 0;
		shift += ((acb & 0b11) == IND) ? 2 : 0;
		shift += ((acb & 0b11) == DIR) ? label_size : 0;
		acb >>= 0b10;
	}
	return (shift);
}

int		reverse_bytes(t_uchar *code, unsigned int pc, int bytes)
{
	t_uchar bytes2[2];
	t_uchar bytes4[4];

	if (bytes == 4)
	{
		bytes4[0] = code[pc + 3];
		bytes4[1] = code[pc + 2];
		bytes4[2] = code[pc + 1];
		bytes4[3] = code[pc];
		return (*(int*)&bytes4[0]);
	}
	if (bytes == 2)
	{
		bytes2[0] = code[pc + 1];
		bytes2[1] = code[pc];
		return (*(short*)&bytes2[0]);
	}
	return (-1);
}

int		is_reg(t_uchar *code, int nb)
{
	int comp;

	comp = code[nb];
	return (1 <= comp && comp <= 16);
}
