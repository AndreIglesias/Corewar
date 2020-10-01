/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 22:01:52 by ciglesia          #+#    #+#             */
/*   Updated: 2020/09/29 20:14:26 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		main(int ac, char **av)
{
	t_vm	vm;

	if (valid_input(ac, av) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (vm_load(&vm, ac, av) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (vm.ncurses)
		print_arena(&vm);
	run_processes(&vm, 0);
	kill_players(&vm);
	return (EXIT_SUCCESS);
}
