/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prebeca <prebeca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 14:46:43 by prebeca           #+#    #+#             */
/*   Updated: 2020/01/31 01:53:31 by prebeca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


char	*ft_strchr_gnl(const char *s, int c)
{
	while (*s)
		if (*s == c)
			return ((char*)s);
		else
			s++;
	return (NULL);
}


int		ft_strclen_gnl(const char *s, char c)
{
	int size;

	if (!s)
		return (0);
	size = 0;
	while (s[size] && s[size] != c)
		++size;
	return (size);
}


size_t	ft_strlcpy_gnl(char *dst, const char *src, size_t dstsize)
{
	size_t i;
	size_t slen;

	if (dst == 0 || src == 0)
		return (0);
	slen = ft_strclen_gnl(src, '\0');
	if (dstsize == 0)
		return (slen);
	i = 0;
	while (src[i] && i < (dstsize - 1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (slen);
}

char	*ft_substr_gnl(char const *s, unsigned int start, size_t len)
{
	char			*substr;
	unsigned long	slen;

	if (!s)
		return (0);
	slen = ft_strclen_gnl(s, '\0');
	start = (start > slen) ? slen : start;
	len = (start + len > slen) ? slen - start : len;
	substr = 0;
	if (!(substr = malloc((len + 1) * sizeof(char))))
		return (0);
	ft_strlcpy_gnl(substr, s + start, len + 1);
	return (substr);
}

char	*ft_strjoin_gnl(char const *s1, char const *s2)
{
	char	*join;
	int		l1;
	int		l2;

	l1 = ft_strclen_gnl(s1, '\0');
	l2 = ft_strclen_gnl(s2, '\0');
	join = 0;
	if (!(join = malloc((l1 + l2 + 1) * sizeof(char))))
		return (0);
	ft_strlcpy_gnl(join, s1, l1 + 1);
	ft_strlcpy_gnl(join + l1, s2, l2 + 1);
	return (join);
}

