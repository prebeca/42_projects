/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prebeca <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 18:57:12 by prebeca           #+#    #+#             */
/*   Updated: 2019/11/13 13:11:45 by prebeca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*cpy;
	int		slen;
	int		i;

	slen = 0;
	while (s1[slen])
		++slen;
	++slen;
	if (!(cpy = malloc(slen * sizeof(char))))
		return (0);
	i = 0;
	while (slen--)
		cpy[slen] = s1[slen];
	return (cpy);
}
