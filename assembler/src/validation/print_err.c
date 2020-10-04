/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/13 20:30:46 by ciglesia          #+#    #+#             */
/*   Updated: 2020/10/04 23:28:57 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		a_error(char *type, char *err)
{
	ft_printf_fd(2, ERROR""RED": %s: %s", type, err);
	return (ft_strlen("ERROR: : ") + ft_strlen(type) + ft_strlen(err));
}

int		lexicon_error(char **cmd, int i, char *err, int line)
{
	int	spaces;
	int posi;
	int posj;

	spaces = a_error("lexicon", err);
	if (!ft_itersplit(cmd, i))
	{
		posi = 0;
		posj = ft_strlen(cmd[0]);
	}
	else
	{
		posi = ft_coordsplit(cmd, ft_itersplit(cmd, i)).i;
		posj = ft_coordsplit(cmd, ft_itersplit(cmd, i)).j;
	}
	ft_printf_fd(2, ": in line %d: "BOLD"%s\n", line, cmd[posi]);
	spaces += ft_strlen(": in line : ");
	spaces += ft_sizei(line) + posj;
	ft_repet_fd(' ', spaces, 2);
	ft_printf_fd(2, "^");
	ft_printf_fd(2, "\n"E0M);
	return (0);
}

int		syntax_error(char **cmd, int i, char *err, int line)
{
	int	spaces;
	int posi;
	int posj;

	spaces = a_error("syntax", err);
	if (!ft_itersplit(cmd, i))
	{
		posi = 0;
		posj = ft_strlen(cmd[0]);
	}
	else
	{
		posi = ft_coordsplit(cmd, ft_itersplit(cmd, i)).i;
		posj = ft_coordsplit(cmd, ft_itersplit(cmd, i)).j;
	}
	ft_printf_fd(2, ": in line %d: "BOLD"%s\n", line, cmd[posi]);
	spaces += ft_strlen(": in line : ");
	spaces += ft_sizei(line) + posj;
	ft_repet_fd(' ', spaces, 2);
	ft_printf_fd(2, "^");
	ft_printf_fd(2, "\n"E0M);
	return (0);
}

int		load_error(char **cmd, int i, char *err, int line)
{
	int	spaces;
	int posi;
	int posj;

	spaces = a_error("load", err);
	if (!ft_itersplit(cmd, i))
	{
		posi = 0;
		posj = ft_strlen(cmd[0]);
	}
	else
	{
		posi = ft_coordsplit(cmd, ft_itersplit(cmd, i)).i;
		posj = ft_coordsplit(cmd, ft_itersplit(cmd, i)).j;
	}
	ft_printf_fd(2, ": in line %d: "BOLD"%s\n", line, cmd[posi]);
	spaces += ft_strlen(": in line : ");
	spaces += ft_sizei(line) + posj;
	ft_repet_fd(' ', spaces, 2);
	ft_printf_fd(2, "^");
	ft_printf_fd(2, "\n"E0M);
	return (0);
}

void	print_usage(char *str, char *end, char *flag, char *messflag)
{
	ft_printf_fd(2, E0M""BOLD"USAGE"E0M": %s [%s] file%s\n", str, flag, end);
	ft_printf_fd(2, "%s\t%s\n", flag, messflag);
}
