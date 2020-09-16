/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/13 20:30:46 by ciglesia          #+#    #+#             */
/*   Updated: 2020/09/15 20:31:36 by ciglesia         ###   ########.fr       */
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

	spaces = a_error("lexicon", err);
	ft_printf_fd(2, ": in line %d: "BOLD"%s\n", line,
							cmd[ft_coordsplit(cmd, ft_itersplit(cmd, i)).i]);
	spaces += ft_strlen(": in line : ");
	spaces += ft_sizei(line) + ft_coordsplit(cmd, ft_itersplit(cmd, i)).j;
	ft_repet_fd(' ', spaces, 2);
	ft_printf_fd(2, "^");
	ft_printf_fd(2, "\n"E0M);
	return (0);
}

int		syntax_error(char **cmd, int i, char *err, int line)
{
	int	spaces;

	spaces = a_error("syntax", err);
	ft_printf_fd(2, ": in line %d: "BOLD"%s\n", line,
							cmd[ft_coordsplit(cmd, ft_itersplit(cmd, i)).i]);
	spaces += ft_strlen(": in line : ");
	spaces += ft_sizei(line) + ft_coordsplit(cmd, ft_itersplit(cmd, i)).j;
	ft_repet_fd(' ', spaces, 2);
	ft_printf_fd(2, "^");
	ft_printf_fd(2, "\n"E0M);
	return (0);
}

int		load_error(char **cmd, int i, char *err, int line)
{
	int	spaces;

	spaces = a_error("load", err);
	ft_printf_fd(2, ": in line %d: "BOLD"%s\n", line,
							cmd[ft_coordsplit(cmd, ft_itersplit(cmd, i)).i]);
	spaces += ft_strlen(": in line : ");
	spaces += ft_sizei(line) + ft_coordsplit(cmd, ft_itersplit(cmd, i)).j;
	ft_repet_fd(' ', spaces, 2);
	ft_printf_fd(2, "^");
	ft_printf_fd(2, "\n"E0M);
	return (0);
}
