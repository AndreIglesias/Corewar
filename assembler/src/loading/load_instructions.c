/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_instructions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 20:27:27 by ciglesia          #+#    #+#             */
/*   Updated: 2020/09/24 11:44:20 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	load_params(char **cmd, int x, int i, t_instruction *inst)
{
	int	valid;
	int type;
	int nargs;

	type = 0;
	nargs = g_op_tab[x].nb_arg;
	while (nargs)
	{
		valid = -1;
		if (ft_itersplit(cmd, i) && *ft_itersplit(cmd, i) == ',')
			i++;
		if ((g_op_tab[x].args[type] & T_REG) == T_REG &&
						(valid = valid_reg(cmd, i)) >= 0)
			add_arg(inst, ft_atoi(ft_itersplit(cmd, i + 1)), NULL, NULL);
		if (valid == -1 && (g_op_tab[x].args[type] & T_DIR) == T_DIR &&
										(valid = valid_dir(cmd, i)) >= 0)
			add_arg(inst, 0, ft_strndup(ft_itersplit(cmd, i), valid - i), NULL);
		if (valid == -1 && (g_op_tab[x].args[type] & T_IND) == T_IND &&
										(valid = valid_ind(cmd, i)) >= 0)
			add_arg(inst, 0, NULL, ft_strndup(ft_itersplit(cmd, i), valid - i));
		nargs--;
		i = valid;
		type++;
	}
}

void	load_op(char **cmd, int i, t_instruction *instr)
{
	int		x;
	char	*op;

	x = 0;
	if (!ft_itersplit(cmd, i) || *ft_itersplit(cmd, i) == '#')
		return ;
	while (g_op_tab[x].name)
	{
		op = ft_itersplit(cmd, i);
		if (ft_strcmpn(g_op_tab[x].name, op, ":%") == 0)
		{
			instr->opcode = x + 1;
			instr->nargs = g_op_tab[x].nb_arg;
			load_params(cmd, x, i + ft_strlen(g_op_tab[x].name), instr);
			return ;
		}
		x++;
	}
}
