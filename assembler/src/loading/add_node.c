/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 18:59:54 by ciglesia          #+#    #+#             */
/*   Updated: 2020/09/15 21:34:28 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	add_label(t_file *file, char *label)
{
	unsigned int	i;
	t_code			*new;
	t_code			*aux;

	i = 0;
	while (label[i] && label[i] != ':')
		i++;
	new = new_label();
	new->label = ft_strndup(label, i);
	aux = file->code_tab;
	if (!aux)
		file->code_tab = new;
	else
	{
		while (aux->next)
			aux = aux->next;
		aux->next = new;

	}
}

void	add_instruction(t_file *file, char **cmd, int i, int line)
{
	t_instruction	*new;
	t_code			*aux;
	t_instruction	*iaux;

	new = new_instruction();
	load_op(cmd, i, line, new);
	aux = file->code_tab;
	if (!aux)
		add_label(file, "MAIN_LABEL");
	while (aux->next)
		aux = aux->next;
	/*if (ft_itersplit(cmd, i))
		ft_printf("OPCODE: %s = %s\n", ft_itersplit(cmd, i), g_op_tab[new->opcode-1].name);
	*/
	iaux = aux->instr;
	if (!iaux)
		aux->instr = new;
	else
	{
		while (iaux->next)
			iaux = iaux->next;
		iaux->next = new;
	}
}
