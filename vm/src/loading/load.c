/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 19:15:21 by ciglesia          #+#    #+#             */
/*   Updated: 2020/08/30 20:48:34 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "vm.h"

int		vm_load(t_vm *vm, int ac, char **av)
{
	vm_init(vm);
	if (load_input(vm, ac, av) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (load_champions(vm) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (load_processes(vm) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	//print_ram(vm);
	return (EXIT_SUCCESS);
}
