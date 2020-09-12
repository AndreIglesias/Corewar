/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 20:49:08 by ciglesia          #+#    #+#             */
/*   Updated: 2020/09/07 20:57:48 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	file_init(t_file *file)
{
	file->fd = -1;
	file->name = NULL;
	file->comment = NULL;
	file->playername = NULL;
	ft_memset(file->code, 0, CHAMP_MAX_SIZE);
}
