/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:21:40 by ciglesia          #+#    #+#             */
/*   Updated: 2020/09/16 12:29:15 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		main(int ac, char **av)
{
	t_file	file;

	if (ac != 2 && ac != 3)
		return (ft_puterr(ERROR""RED": assembler needs exactly one file!"E0M,
						EXIT_FAILURE));
	else if (ac == 2 || (ac == 3 && ft_strcmp(av[1], "-v") == 0))
	{
		file_init(&file);
		if (valid_input((ac == 2) ? av[1] : av[2], &file) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (verify_code(&file, NULL, 0, 0) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		translate(&file, (ac == 3) ? ft_strcmp(av[1], "-v") == 0 : 0);
		//free table, lists, char*
	}
	return (EXIT_SUCCESS);
}
