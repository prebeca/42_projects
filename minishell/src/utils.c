
#include "minishell.h"

int	table_len(char ** tab)
{
	int i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}