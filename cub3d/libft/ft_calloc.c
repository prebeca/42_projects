/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prebeca <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 09:47:42 by prebeca           #+#    #+#             */
/*   Updated: 2019/11/13 14:30:00 by prebeca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_calloc(size_t count, size_t size)
{
	void *mem;

	if (!count || !size)
	{
		count = 1;
		size = 1;
	}
	mem = 0;
	if ((mem = malloc(count * size)))
		ft_bzero(mem, count * size);
	return (mem);
}
