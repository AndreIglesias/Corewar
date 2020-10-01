/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 18:11:34 by ciglesia          #+#    #+#             */
/*   Updated: 2020/09/25 17:57:14 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

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

int		invalid_line(char **cmd, int line, t_file *file)
{
	int err;
	int	pos;

	err = 0;
	pos = 0;
	if (file->quotes && (err = end_quote(cmd, file, 0)) == 1)
		return (0);
	if (err == 0 && ((err = is_head(cmd, ".name", line, 0)) == 1 || err == 2))
		return (0);
	if (err == 0 && ((err = is_head(cmd, ".comment", line, 0)) < 3 && err))
		return (0);
	if (err == 0)
		pos = is_label(cmd);
	if (err == 0 && (err = is_opcode(cmd, pos, line)) == 1)
		return (0);
	return ((err < 0) ? 1 : 0);
}

int		capture_syntax(char **cmd, t_file *file, char *inst, int pos)
{
	int	err;
	int quotes;

	err = 0;
	quotes = file->quotes;
	(quotes) ? end_quote(cmd, file, 1) : 0;
	if (quotes == 1 || (!err && ((err = is_head(cmd, ".name", file->line,
								0)) == 1 || err == 2) && !file->playername[0]))
	{
		fill_header(file->playername, inst, PROG_NAME_LENGTH, err);
		file->quotes = (err == 1) ? 1 : file->quotes;
		return (0);
	}
	if (quotes == 2 || (!err && ((err = is_head(cmd, ".comment",
							file->line, 0)) < 3 && err) && !file->comment[0]))
	{
		fill_header(file->comment, inst, COMMENT_LENGTH, err);
		file->quotes = (err == 1) ? 2 : file->quotes;
		return (0);
	}
	if ((pos = is_label(cmd)))
		add_label(file, cmd[0]);
	if (err == 0 && (err = is_opcode(cmd, pos, file->line)) == 1)
		add_instruction(file, cmd, pos);
	return (0);
}

/*
** verif semantics consistency
*/

int		verify_code(t_file *file, char *line, int l, int s)
{
	char	*pitcher;
	char	**cmd;
	int		i;

	pitcher = NULL;
	i = 1;
	while (get_next_line2(file->fd, &line, &pitcher) == 1)
	{
		cmd = ft_split(line, " \t");
		file->line = i;
		if (cmd && cmd[0])
		{
			l = invalid_line(cmd, i, file);
			if (l || (s = capture_syntax(cmd, file, line, 0)))
			{
				free_instruction(cmd, pitcher, line, file->fd);
				return (EXIT_FAILURE);
			}
		}
		i++;
		free_instruction(cmd, NULL, line, -1);
	}
	free_instruction(NULL, NULL, line, file->fd);
	return (unknown_labels(file->code_tab) ? EXIT_FAILURE : EXIT_SUCCESS);
}
