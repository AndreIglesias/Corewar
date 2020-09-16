/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 19:53:57 by ciglesia          #+#    #+#             */
/*   Updated: 2020/09/15 20:15:47 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** valid == -1	: not this type
** valid > 0	: successful valid type, position
** -------------
** valid_params.c: valid_reg, valid_dir, valid_ind
*/

int		valid_params(char **cmd, int x, int i, int line)
{
	int	valid;
	int type;
	int nargs;

	type = 0;
	nargs = g_op_tab[x].nb_arg;
	while (nargs)
	{
		valid = -1;
		if (ft_itersplit(cmd, i) && *ft_itersplit(cmd, i) == ',')
			i++;
		if ((g_op_tab[x].args[type] & T_REG) == T_REG)
			valid = valid_reg(cmd, i);
		if (valid == -1 && (g_op_tab[x].args[type] & T_DIR) == T_DIR)
			valid = valid_dir(cmd, i);
		if (valid == -1 && (g_op_tab[x].args[type] & T_IND) == T_IND)
			valid = valid_ind(cmd, i);
		if (valid < 0)
			return (syntax_error(cmd, i, "invalid parameter", line));
		nargs--;
		i = valid;
		type++;
	}
	if (ft_itersplit(cmd, i) && *ft_itersplit(cmd, i) != '#')
		return (syntax_error(cmd, i, "invalid parameter", line));
	return (1);
}

int		valid_separator(char **cmd, int i, int nargs, int line)
{
	int x;
	int si;

	while (nargs)
	{
		x = i;
		si = ft_coordsplit(cmd, ft_itersplit(cmd, i)).i;
		while (ft_itersplit(cmd, i) && ft_coordsplit(cmd,
				ft_itersplit(cmd, i)).i == si && ft_countchr(":-%"LABEL_CHARS,
														*ft_itersplit(cmd, i)))
			i++;
		if (nargs > 1 && ft_itersplit(cmd, i) && *ft_itersplit(cmd, i) == '#')
			break ;
		if (i == x)
			return (syntax_error(cmd, i, "invalid format", line));
		if (nargs != 1 && ft_itersplit(cmd, i) && *ft_itersplit(cmd, i) != ',')
			return (syntax_error(cmd, i, "separator missing", line));
		if (nargs == 1 && ft_itersplit(cmd, i) && *ft_itersplit(cmd, i) != '#')
			return (syntax_error(cmd, i, "invalid format", line));
		nargs--;
		i++;
	}
	if (nargs >= 1)
		return (syntax_error(cmd, i, "invalid format", line));
	return (1);
}
