/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 00:13:47 by ciglesia          #+#    #+#             */
/*   Updated: 2020/09/14 12:55:36 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"


/*
** valid == -1	: not this type
** valid > 0	: position
*/

int		valid_reg(char **cmd, int i)
{
	//ft_printf(RED"%s"E0M, ft_itersplit(cmd, i));//
	if (!ft_itersplit(cmd, i) || *ft_itersplit(cmd, i) != 'r')
		return (-1);
	if (!ft_itersplit(cmd, i + 1) || !('1' <= *ft_itersplit(cmd, i + 1) &&
										*ft_itersplit(cmd, i + 1) <= '9'))
		return (-1);
	if (!ft_itersplit(cmd, i + 2) || (*ft_itersplit(cmd, i + 2) == ','
									|| *ft_itersplit(cmd, i + 2) == '#'))
		return (i + 2);
	if (!('0' <= *ft_itersplit(cmd, i + 2) && *ft_itersplit(cmd, i + 2) <= '6'))
		return (-1);
	if ('1' != *ft_itersplit(cmd, i + 1))
		return (-1);
	return (i + 3);
}

/*
** return -1	: not this type
** return > 0	: position
*/

int		label_param(char **cmd, unsigned int i)
{
	//ft_printf(RED"%s"E0M, ft_itersplit(cmd, i));//
	if (ft_itersplit(cmd, i) && *ft_itersplit(cmd, i) == LABEL_CHAR)
		i++;
	else
		return (0);
	while (ft_itersplit(cmd, i) && ft_countchr(LABEL_CHARS, *ft_itersplit(cmd, i)))
		i++;
	return (i);
}

int		valid_dir(char **cmd, int i)
{
	int ret;

	//ft_printf(RED"%s"E0M, ft_itersplit(cmd, i));//
	if (!ft_itersplit(cmd, i) || *ft_itersplit(cmd, i) != '%')
		return (-1);
	if ((ret = valid_ind(cmd, i + 1)) < 0)
		return (-2);
	return (ret);
}

int		valid_ind(char **cmd, int i)
{
	int	ret;

	//ft_printf(RED"%s"E0M, ft_itersplit(cmd, i));//
	if ((ret = label_param(cmd, i)))
		return (ret);
	if (ft_itersplit(cmd, i) && *ft_itersplit(cmd, i) == '-')
		i++;
	ret = i;
	while (ft_itersplit(cmd, i) && ('0' <= *ft_itersplit(cmd, i) &&
									*ft_itersplit(cmd, i) <= '9'))
		i++;
	if (ret == i)
		return (-1);
	return (i);
}
