/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 18:57:12 by prebeca           #+#    #+#             */
/*   Updated: 2020/10/04 13:50:57 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*cpy;
	int		slen;

	slen = 0;
	while (s1[slen])
		++slen;
	++slen;
	if (!(cpy = malloc(slen * sizeof(char))))
		return (0);
	while (slen--)
		cpy[slen] = s1[slen];
	return (cpy);
}
