/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 18:11:34 by ciglesia          #+#    #+#             */
/*   Updated: 2020/09/08 18:35:19 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "asm.h"

void	free_instruction(char **cmd, char *pitcher, char *line, int fd)
{
	if (fd >= 0)
		close(fd);
	if (cmd)
		free_split(cmd);
	if (pitcher)
		free(pitcher);
	if (line)
		free(line);
}

int		invalid_lexicon(char **cmd)
{
	int err;
	int	pos;

	err = 0;
	pos = 0;
	if ((err = is_head(cmd, ".name")) == 1)
		return (0);
	if (err == 0 && (err = is_head(cmd, ".comment")) == 1)
		return (0);
	if (err == 0 && (pos = is_label(cmd)) < 0)
		err = pos;
	if (err == 0 && (err = is_opcode(cmd, pos)) == 1)
		return (0);
	if (err == -1)
		ft_printf_fd(2, ERROR""RED": lexicon: invalid number of quotes"E0M);
	else if (err == -2)
		ft_printf_fd(2, ERROR""RED": lexicon: invalid format"E0M);
	return ((err < 0) ? 1 : 0);
}

int		invalid_syntax(char **cmd, int i, int j)
{
	(void)j;
	while (cmd[i])
	{
		if (cmd[i][0] == '#')
			break ;
		i++;
	}
	return (0);
}

int		correct_syntax(t_file *file, char *line, int l, int s)
{
	char	*pitcher;
	char	**cmd;
	int		i;

	pitcher = NULL;
	i = 1;
	while (get_next_line2(file->fd, &line, &pitcher) == 1)
	{
		cmd = ft_split(line, " \t");
		if (cmd && cmd[0] && cmd[0][0] != '#')
		{
			l = invalid_lexicon(cmd);
			if (l || (s = invalid_syntax(cmd, 0, 0)))
			{
				free_instruction(cmd, pitcher, line, file->fd);
				ft_printf_fd(2, RED": line %d\n"E0M, i);
				return (0);
			}
		}
		i++;
		free_instruction(cmd, NULL, line, -1);
	}
	free_instruction(NULL, NULL, line, file->fd);
	return (EXIT_SUCCESS);
}
