/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 11:24:58 by prebeca           #+#    #+#             */
/*   Updated: 2020/05/15 17:27:04 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	word_size(const char *s, char c)
{
	int size;

	size = 0;
	while (s[size] && s[size] != c)
		++size;
	return (size);
}

static char	**alloc_table(const char *s, char **split, char c, int *count)
{
	int i;

	i = 0;
	*count = 0;
	while (s[i])
		if (s[i] && s[i] != c)
		{
			(*count)++;
			while (s[i] && s[i] != c)
				++i;
		}
		else
			++i;
	if (!(split = malloc((*count + 1) * sizeof(char*))))
		return (0);
	split[*count] = 0;
	return (split);
}

static char	**free_table(char **table)
{
	int i;

	i = -1;
	while (table[++i])
		free(table[i]);
	free(table);
	return (0);
}

char		**ft_split(char const *s, char c)
{
	char	**split;
	int		i;
	int		j;
	int		count;

	if (s == 0)
		return (0);
	split = 0;
	if (!(split = alloc_table(s, split, c, &count)))
		return (0);
	i = 0;
	j = 0;
	while (j < count)
	{
		if (s[i] && s[i] != c)
		{
			if (!(split[j] = ft_substr(s, i, word_size(s + i, c))))
				return (free_table(split));
			j++;
			i += word_size(s + i, c);
		}
		i++;
	}
	return (split);
}
