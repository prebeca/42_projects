/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prebeca <prebeca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 13:41:59 by prebeca           #+#    #+#             */
/*   Updated: 2020/01/08 01:40:26 by prebeca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	*ft_map(int *tab, int length, int (*f)(char*))
{
	int *res_tab;
	int i;

	i = -1;
	res_tab = 0;
	if (!(res_tab = malloc(length * sizeof(int))))
		return (0);
	while (++i < length)
		res_tab[i] = (*f)(tab[i]);
	return (res_tab);
}
