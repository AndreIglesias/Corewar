/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:21:40 by ciglesia          #+#    #+#             */
/*   Updated: 2020/09/05 22:34:07 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		main(int ac, char **av)
{
	if (ac != 2)
		return (ft_puterr(RED"ERROR: assembler needs exactly one file!"E0M,
						EXIT_FAILURE));
	else
	{
		(void)av;
		ft_printf("HOLA;)");
	}
	return (EXIT_SUCCESS);
}
