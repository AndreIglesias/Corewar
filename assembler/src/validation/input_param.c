/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_param.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/06 21:55:33 by ciglesia          #+#    #+#             */
/*   Updated: 2020/09/06 22:21:11 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		valid_input(char *file)
{
	int fd;

	if (!file_name(file, ".s"))
		return (EXIT_FAILURE);
	if ((fd = open(file, O_RDONLY) < 0) || read(fd, NULL, 0))
	{
		ft_printf_fd(2, ERROR": %s: Cannot open file .s\n",	file);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
