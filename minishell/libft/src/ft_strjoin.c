/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prebeca <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 18:19:28 by prebeca           #+#    #+#             */
/*   Updated: 2019/11/14 12:44:24 by prebeca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	int		l1;
	int		l2;

	if (s1 == 0 || s2 == 0)
		return (0);
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	join = 0;
	if (!(join = malloc((l1 + l2 + 1) * sizeof(char))))
		return (0);
	ft_strlcpy(join, s1, l1 + 1);
	ft_strlcpy(join + l1, s2, l2 + 1);
	return (join);
}
