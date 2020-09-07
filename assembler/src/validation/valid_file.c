/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 18:21:29 by ciglesia          #+#    #+#             */
/*   Updated: 2020/09/07 19:39:42 by ciglesia         ###   ########.fr       */
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
		ft_printf_fd(2, ERROR""RED": %s: Cannot open file .s\n"E0M, file);
		return (EXIT_FAILURE);
	}
	close(fd);
	if (!correct_syntax(open(file, O_RDONLY), NULL, 0, 0))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
