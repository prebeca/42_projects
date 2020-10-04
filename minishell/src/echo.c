#include "minishell.h"

void	echo_n(char *line)
{
	char *buf;
	int i;

	i = 1;
	while (line[i] == 'n')
		i++;
	buf = ft_strtrim(line, " \n");
	ft_putstr_fd(buf, STDOUT_FILENO);
}

int		parse_echo(char *line)
{
	int i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] && !ft_strncmp("-n", &line[i], 2))
		echo_n(&line[i]);
	else
		ft_putstr_fd(&line[i], STDOUT_FILENO);
	return (0);
}