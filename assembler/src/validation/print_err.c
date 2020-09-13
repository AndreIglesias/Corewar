/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/13 20:30:46 by ciglesia          #+#    #+#             */
/*   Updated: 2020/09/13 21:11:46 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		lexicon_error(char **cmd, int i, char *err, int line)
{
	int	spaces;

	ft_printf_fd(2, ERROR""RED": lexicon: %s", err);
	spaces = ft_strlen("ERROR: lexicon: ") + ft_strlen(err);

	ft_printf_fd(2, ": in line %d: "BOLD"%s\n", line,
							cmd[ft_coordsplit(cmd, ft_itersplit(cmd, i)).i]);
	spaces += ft_strlen(": in line : ");
	spaces += ft_sizei(line) + ft_coordsplit(cmd, ft_itersplit(cmd, i)).j;
	ft_repet_fd(' ', spaces, 2);
	ft_printf_fd(2, "^");
	ft_printf_fd(2, "\n"E0M);
	return (0);
}
