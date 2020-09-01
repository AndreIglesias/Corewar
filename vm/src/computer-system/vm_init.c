/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 22:44:00 by ciglesia          #+#    #+#             */
/*   Updated: 2020/08/30 12:53:31 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**
** +------+-----+------------+-----+-----------------+
** |           CPU           |     |      RAM        |
** +------+------------+-----|     |-----------------+
** | REGS |    ALU     |     |     |   Instructions  |
** +------+------------+-----|     |------+----------+
** |  R0  | Arithmetic | IR  |     | Addr | Mem Cell |
** |  R1  | Logic Unit | PC  |     +------+----------+
** |  R2  |            | PSR |     |  0   |    0     |
** |  R3  |            |     |     |  1   |    22    |
** |  R4  |            |     |     |  2   |    4     |
** |  ... |            |     |     |  ... |    ...   |
** +------+------------+-----+-----+------+----------+
**
*/

#include "vm.h"

int		vm_init(t_vm *vm)
{
	vm->cycle_to_die = CYCLE_TO_DIE;
	vm->dump_param = -1;
	vm->nplayers = 0;
	vm->nprocess = 0;
	vm->ncurses = 0;
	vm->cycles = 0;
	vm->nlives = 0;
	vm->height = 0;
	vm->width = 0;
	vm->nchecks = 0;
	vm->last_alive = 0;
	vm->process_alive = 0;
	vm->player = NULL;
	vm->mainWin = NULL;
	vm->sideWin = NULL;
	vm->processes = NULL;
	ft_memset(vm->ram.arena, 0, sizeof(unsigned char) * MEM_SIZE);
	ft_memset(vm->ram.owner, 0, sizeof(unsigned char) * MEM_SIZE);
	ft_memset(vm->ram.scrb, 0, sizeof(unsigned char) * MEM_SIZE);
	return (EXIT_SUCCESS);
}
