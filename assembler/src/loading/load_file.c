/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 17:45:51 by ciglesia          #+#    #+#             */
/*   Updated: 2020/09/20 20:33:54 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	fill_header(char *dest, char *inst, int size, int headline)
{
	int i;
	int j;

	i = 0;
	while (dest[i])
		i++;
	j = 0;
	if (headline)
	{
		while (inst[j] && inst[j] != '"')
			j++;
		j++;
	}
	else
		dest[i++] = '\n';
	while (inst[j] && inst[j] != '"' && i < size)
		dest[i++] = inst[j++];
}
