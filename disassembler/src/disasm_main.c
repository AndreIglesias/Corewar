/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disasm_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 14:16:09 by ciglesia          #+#    #+#             */
/*   Updated: 2020/09/27 17:37:59 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disasm.h"

int		main(int ac, char **av)
{
	t_file	file;

	if (ac != 2)
		return (ft_puterr(ERROR""RED": assembler needs exactly one file!"E0M,
						EXIT_FAILURE));
	else if (ac == 2)
	{
		file_init(&file, av[1]);
		if (valid_header(&file) == EXIT_FAILURE)
			return (EXIT_FAILURE + file_destructor(&file));
		if (load_exec(&file) == EXIT_FAILURE)
			return (EXIT_FAILURE + file_destructor(&file));
		if (init_writing(&file) == EXIT_FAILURE)
			return (EXIT_FAILURE + file_destructor(&file));
		if (disassemble(&file) == EXIT_FAILURE)
		{
			close(file.fd);
			return (EXIT_FAILURE + file_destructor(&file));
		}
		close(file.fd);
		file_destructor(&file);
	}
	return (EXIT_SUCCESS);
}
