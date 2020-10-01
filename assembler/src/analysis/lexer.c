/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction_lexicon.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 23:55:20 by ciglesia          #+#    #+#             */
/*   Updated: 2020/09/21 10:57:13 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		end_quote(char **cmd, t_file *file, int modif)
{
	int i;
	int line;

	i = 0;
	line = file->line;
	while (ft_itersplit(cmd, i) && *ft_itersplit(cmd, i) != '"')
		i++;
	if (!ft_itersplit(cmd, i))
		return (1);
	if (ft_itersplit(cmd, i + 1) && *ft_itersplit(cmd, i + 1) != '#')
		return (-1 + lexicon_error(cmd, i, "invalid format or quotes", line));
	if (modif)
		file->quotes = 0;
	return (1);
}

int		is_head(char **cmd, char *str, int line, unsigned int i)
{
	int				quotes;

	while (cmd[0][i] && i < ft_strlen(str))
	{
		if (cmd[0][i] != str[i])
			return (0);
		i++;
	}
	if (i != ft_strlen(str))
		return (0);
	if (*ft_itersplit(cmd, i++) != '"')
		return (-1 + lexicon_error(cmd, i, "invalid number of quotes", line));
	quotes = 1;
	while (ft_itersplit(cmd, i))
	{
		quotes += (*ft_itersplit(cmd, i) == '"');
		if (quotes > 2 || (quotes >= 2 && *ft_itersplit(cmd, i) == '#'))
			break ;
		else if (quotes >= 2 && *ft_itersplit(cmd, i) != '"')
			return (-2 + lexicon_error(cmd, i, "invalid format", line));
		i++;
	}
	return ((quotes > 2 || !quotes) ? -1 +
			lexicon_error(cmd, i, "invalid number of quotes", line) : quotes);
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
