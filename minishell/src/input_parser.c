#include "minishell.h"

int	parse_input(char *input)
{
	int i;
	int start;
	char buff[512];

	i = 0;
	while (input[i] && !ft_isalnum(input[i]))
		i++;
	start = i;
	while (input[i] && ft_isalnum(input[i]))
		i++;
	ft_strlcpy(buff, &input[start], i - start + 1);
	if (ft_strcmp("echo", buff) == 0)
		parse_echo(&input[i]);
	else if (ft_strcmp("pwd", buff) == 0)
		ft_putendl_fd(getcwd(buff,512), STDOUT_FILENO);
	else if (ft_strcmp("cd", buff) == 0)
		change_directory(&input[i]);
	else if (ft_strcmp("exit", buff) == 0)
		exit(0);
	return(0);
}