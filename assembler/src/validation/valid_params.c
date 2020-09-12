/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 00:13:47 by ciglesia          #+#    #+#             */
/*   Updated: 2020/09/12 13:21:39 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"


/*
** sep_pos == 1	: first argument
** sep_pos == 2	: last argument
** valid == 0	: successful valid type
** valid == -1	: not this type
** valid == -2	: separator error
** valid > 0	: position
*/
/*
int		valid_reg(char **cmd, int pos, int sep_pos)
{
	int	i;

	i = 0;
	if ((cmd[pos][i] && cmd[pos][i] == ',') && sep_pos == 1)
		return (-2);
	if (cmd[pos][i] && cmd[pos][i] == ',')
		i++;
	if (!cmd[pos][i] || !cmd[pos][i] != 'r')
		return (-1);
	if (!cmd[pos][i + 1] || !('1' <= cmd[pos][i + 1] && cmd[pos][i + 1] <= '9'))
		return (-1);
	if (!cmd[pos][i + 2])
		return (i + 2);
	if (cmd[pos][i + 2] == ',')
		return (i + 2);
	else if (!('0' <= cmd[pos][i + 2] && cmd[pos][i + 2] <= '6'))
		return (-1);
	if (!cmd[pos][i + 3])
		return (0);
	if (cmd[pos][i + 3] == ',')
		return ((sep_pos == 2) ? -2 : i + 3);
	if (!cmd[pos][i + 4])
		return (0);
	return (i + 4);
}
*/
/*
** return -1	: not this type
** return 0		: successful valid type
** return > 0	: position
*/
/*
int		label_param(char **cmd, int pos, unsigned int i)
{
	if (cmd[pos][i] && cmd[pos][i] == LABEL_CHAR)
		i++;
	else
		return (-1);
	while (cmd[pos][i] && ft_countchr(LABEL_CHARS, cmd[pos][i]))
		i++;
	if (cmd[pos][i])
		return (i + 1);
	return (0);
}

int		valid_dir(char **cmd, int pos, int i, int sep_pos)
{
	if ((cmd[pos][i] && cmd[pos][i] == ',') && sep_pos == 1)
		return (-2);
}

int		valid_ind(char **cmd, int pos, int i, int sep_pos)
{
	if ((cmd[pos][i] && cmd[pos][i] == ',') && sep_pos == 1)
		return (-2);
}
*/
