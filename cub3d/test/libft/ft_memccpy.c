/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prebeca <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 15:37:38 by prebeca           #+#    #+#             */
/*   Updated: 2019/11/12 14:25:28 by prebeca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*scur;
	unsigned char	*dcur;

	scur = (unsigned char*)src;
	dcur = (unsigned char*)dst;
	i = 0;
	while (i < n)
	{
		dcur[i] = scur[i];
		if (scur[i] == (unsigned char)c)
			return (dcur + i + 1);
		i++;
	}
	return (NULL);
}
