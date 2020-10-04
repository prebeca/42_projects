#include "minishell.h"

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	int exit;
	char input[512];
	exit = 0;
	while (!exit)
	{
		ft_bzero(input, 512);
		ft_putstr_fd(getcwd(NULL, 0), STDOUT_FILENO);
		ft_putstr_fd("> ", STDOUT_FILENO);
		if(read(STDIN_FILENO, input, 512) == -1)
			return(1);
		parse_input(input);
	}
	return (0);
}