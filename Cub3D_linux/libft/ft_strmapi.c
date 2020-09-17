/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prebeca <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 11:55:59 by prebeca           #+#    #+#             */
/*   Updated: 2019/11/14 11:10:12 by prebeca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*s2;
	unsigned int	i;

	if (!s || !f)
		return (0);
	if (!(s2 = malloc((ft_strlen(s) + 1) * sizeof(char))))
		return (0);
	i = -1;
	while (s[++i])
		s2[i] = (*f)(i, s[i]);
	s2[i] = '\0';
	return (s2);
}
