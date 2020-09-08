
#include "asm.h"

int		is_head(char ** cmd, char *str)
{
	int				quotes;
	unsigned int	i;

	i = 0;
	while (cmd[0][i] && i < ft_strlen(str))
	{
		if (cmd[0][i] != str[i])
			return (0);
		i++;
	}
	if (i != ft_strlen(str))
		return (0);
	if (*ft_itersplit(cmd, i++) != '"')
		return (-1);
	quotes = 1;
	while (ft_itersplit(cmd, i))
	{
		quotes += (*ft_itersplit(cmd, i) == '"');
		if (quotes > 2 || (quotes >= 2 && *ft_itersplit(cmd, i) == '#'))
			break ;
		else if (quotes >= 2 && *ft_itersplit(cmd, i) != '"')
			return (-2);
		i++;
	}
	return ((quotes != 2) ? -1 : 1);
}

int		is_label(char **cmd)
{
	unsigned int	i;

	i = 0;
	while (cmd[0][i] && ft_countchr(LABEL_CHARS, cmd[0][i]))
		i++;
	if (cmd[0][i] && cmd[0][i] == LABEL_CHAR)
		return (i + 1);
	return (0);
}

int		is_opcode(char **cmd, int i)
{
	int x;

	x = 0;

	if (*ft_itersplit(cmd, i) == '#')
		return (0);
	while (op_tab[x].name)
	{
		if (ft_strcmp(op_tab[x].name, ft_itersplit(cmd, i)) == 0)
		{
			ft_printf(GREEN"%s-%s\n"E0M, op_tab[x].name, ft_itersplit(cmd, i));
			return (1);
		}
		x++;
	}
	return (-2);
}
