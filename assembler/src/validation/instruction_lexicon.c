/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction_lexicon.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 23:55:20 by ciglesia          #+#    #+#             */
/*   Updated: 2020/09/09 01:31:24 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		is_head(char ** cmd, char *str)
{
	int				quotes;
	unsigned int	i;

	i = 0;
	while (cmd[0][i] && i < ft_strlen(str))
	{
		if (cmd[0][i] != str[i])
			return (0);
		i++;
	}
	if (i != ft_strlen(str))
		return (0);
	if (*ft_itersplit(cmd, i++) != '"')
		return (-1);
	quotes = 1;
	while (ft_itersplit(cmd, i))
	{
		quotes += (*ft_itersplit(cmd, i) == '"');
		if (quotes > 2 || (quotes >= 2 && *ft_itersplit(cmd, i) == '#'))
			break ;
		else if (quotes >= 2 && *ft_itersplit(cmd, i) != '"')
			return (-2);
		i++;
	}
	return ((quotes != 2) ? -1 : 1);
}

int		is_label(char **cmd)
{
	unsigned int	i;

	i = 0;
	while (cmd[0][i] && ft_countchr(LABEL_CHARS, cmd[0][i]))
		i++;
	if (cmd[0][i] && cmd[0][i] == LABEL_CHAR)
		return (i + 1);
	return (0);
}

/*
** sep_pos == 1	: first argument
** sep_pos == 2	: last argument
** valid == 0	: successful valid type
** valid == -1	: not this type
** valid == -2	: separator error
** valid > 0	: position
*/

int		valid_params(char **cmd, int x, int posarg, int nargs)
{
	int i;
	int	separator;
	int	valid;
	int	sep_pos;

	i = 0;
	while (cmd[posarg] && i < nargs)
	{
		sep_pos = (i + 1 == nargs) ? 2 : 0;
		sep_pos = (i == 0) ? 1 : sep_pos;
		valid = -1;
		if (op_tab[x].args[i] & T_REG)
			valid = valid_reg(cmd, posarg, i, sep_pos);
		if ((valid != 0 && valid != -2) && op_tab[x].args[i] & T_DIR)
			valid = valid_dir(cmd, posarg, valid, i, sep_pos);
		if ((valid != 0 && valid != -2) && op_tab[x].args[i] & T_IND)
			valid_ind(cmd, posarg, valid, i, sep_pos);
		if (valid < 0)
			return (0);
		posarg++;
		i++;
	}
	return (1);
}

int		valid_separator(char **cmd, int i, int nargs)
{
	return (1);
}

int		is_opcode(char **cmd, int i)
{
	int		x;
	char	*op;
	int		si;

	x = 0;
	if (*ft_itersplit(cmd, i) == '#')
		return (0);
	while (op_tab[x].name)
	{
		op = ft_itersplit(cmd, i);
		if (ft_strcmp(op_tab[x].name, op) == 0)//maybe ld:label or ld%31
		{
			si = ft_coordsplit(cmd, op).i + 1;
			if (!valid_separator(cmd, i + 1, op_tab[x].nb_arg))
				return (-2);
			if (!valid_params(cmd, x, si, op_tab[x].nb_arg))
				return (-2);
			ft_printf(GREEN"%s-%s\n"E0M, op_tab[x].name, ft_itersplit(cmd, i));
			return (1);
		}
		x++;
	}
	return (-2);
}
