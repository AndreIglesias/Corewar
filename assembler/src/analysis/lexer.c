/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction_lexicon.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 23:55:20 by ciglesia          #+#    #+#             */
/*   Updated: 2020/09/14 12:55:44 by ciglesia         ###   ########.fr       */
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
** valid == -1	: not this type
** valid > 0	: successful valid type, position
** -------------
** valid_params.c: valid_reg, valid_dir, valid_ind
*/

//si = ft_coordsplit(cmd, op).i + 1;

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
			return (lexicon_error(cmd, i, "invalid parameter", line));
		nargs--;
		i = valid;
		type++;
	}
	if (ft_itersplit(cmd, i) && *ft_itersplit(cmd, i) != '#')
		return (lexicon_error(cmd, i, "invalid parameter", line));
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
			return (lexicon_error(cmd, i, "invalid format", line));
		if (nargs != 1 && ft_itersplit(cmd, i) && *ft_itersplit(cmd, i) != ',')
			return (lexicon_error(cmd, i, "separator missing", line));
		if (nargs == 1 && ft_itersplit(cmd, i) && *ft_itersplit(cmd, i) != '#')
			return (lexicon_error(cmd, i, "invalid format", line));
		nargs--;
		i++;
	}
	if (nargs >= 1)
		return (lexicon_error(cmd, i, "invalid format", line));
	return (1);
}

int		is_opcode(char **cmd, int i, int line)
{
	int		x;
	char	*op;

	x = 0;
	if (!ft_itersplit(cmd, i) || *ft_itersplit(cmd, i) == '#')
		return (0);
	while (g_op_tab[x].name)
	{
		op = ft_itersplit(cmd, i);
		if (ft_strcmpn(g_op_tab[x].name, op, ":%") == 0)
		{
			//ft_printf(GREEN"%s\n"E0M, g_op_tab[x].name);
			if (!valid_separator(cmd, i + ft_strlen(g_op_tab[x].name),
								g_op_tab[x].nb_arg, line))
				return (-1);
			if (!valid_params(cmd, x, i + ft_strlen(g_op_tab[x].name), line))
				return (-1);
			return (1);
		}
		x++;
	}
	return (-1 + lexicon_error(cmd, i, "invalid format", line));
}
