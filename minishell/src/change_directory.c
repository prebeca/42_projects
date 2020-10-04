#include "minishell.h"

void	change_directory(char *path)
{
	char *path_clean;
	char **argv;
	int tab_len;

	path_clean = ft_strtrim(path, " \n");
	if ((argv = ft_split(path_clean, ' ')) == 0)
		return;
	tab_len = table_len(argv);
	if ( tab_len != 1)
		ft_putendl_fd("cd : Too many arguments", STDERR_FILENO);
	if (tab_len == 1 && chdir(path_clean) == -1)
	{
		ft_putstr_fd("cd : ", STDERR_FILENO);
		ft_putstr_fd(path_clean, STDERR_FILENO);
		ft_putstr_fd(" : ", STDERR_FILENO);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
	}
}