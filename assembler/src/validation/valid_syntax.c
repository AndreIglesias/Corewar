/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 18:11:34 by ciglesia          #+#    #+#             */
/*   Updated: 2020/09/07 19:59:48 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "asm.h"

void	free_instruction(char **cmd, char *pitcher, char *line)
{
	if (cmd)
		free_split(cmd);
	if (pitcher)
		free(pitcher);
	if (line)
		free(line);
}

int		invalid_lexicon(char **cmd)
{
	ft_printf("[");
	for (int i = 0; cmd[i]; i++)
	{
		ft_printf("%s, ", cmd[i]);
	}
	ft_printf("]");
	return (0);
}

int		invalid_syntax(char **cmd)
{
	(void)cmd;
	return (0);
}

int		correct_syntax(int fd, char *line, int l, int s)
{
	char	*pitcher;
	char	**cmd;
	int		i;

	pitcher = NULL;
	i = 0;
	while (get_next_line2(fd, &line, &pitcher) == 1)
	{
		cmd = ft_split(line, " \t");
		if (cmd && cmd[0] && cmd[0][0] != '#')
		{
			l = invalid_lexicon(cmd);
			if (l || (s = invalid_syntax(cmd)))
			{
				free_instruction(cmd, pitcher, line);
				ft_printf_fd(2, ERROR""RED": %s: [%d:%d]"E0M, (l) ? "lexicon" :
							 "syntax", i, (l) ? l : s);
				return (0);
			}
		}
		free_instruction(cmd, NULL, line);
	}
	free_instruction(NULL, NULL, line);
	return (EXIT_SUCCESS);
}
