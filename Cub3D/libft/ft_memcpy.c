/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prebeca <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 13:28:26 by prebeca           #+#    #+#             */
/*   Updated: 2019/11/12 14:25:45 by prebeca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*scur;
	unsigned char	*dcur;

	scur = (unsigned char*)src;
	dcur = (unsigned char*)dst;
	if (dst == src)
		return (dst);
	while (n-- > 0)
		dcur[n] = scur[n];
	return (dst);
}
