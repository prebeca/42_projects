/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prebeca <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 10:05:08 by prebeca           #+#    #+#             */
/*   Updated: 2019/11/15 13:42:18 by prebeca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strtrim(char const *s1, char const *set)
{
	int		min;
	int		max;

	if (!s1 || !set)
		return (0);
	min = 0;
	while (s1[min] && ft_strchr(set, s1[min]))
		++min;
	max = ft_strlen(s1);
	while (min < max && ft_strchr(set, s1[max - 1]))
		--max;
	return (ft_substr(s1, min, max - min));
}
