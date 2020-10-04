/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prebeca <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 10:42:13 by prebeca           #+#    #+#             */
/*   Updated: 2019/11/15 15:20:22 by prebeca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*reverse(char *str)
{
	size_t	len;
	size_t	i;
	char	tmp;

	len = ft_strlen(str);
	--len;
	i = 0;
	while (i < len - i)
	{
		tmp = str[i];
		str[i] = str[len - i];
		str[len - i] = tmp;
		++i;
	}
	return (str);
}

static char	*allocstr(int n)
{
	int				len;
	char			*str;
	unsigned int	un;

	len = 0;
	if (n < 0)
		++len;
	un = 0;
	un = (n < 0) ? -n : n;
	while (un > 0)
	{
		un = un / 10;
		++len;
	}
	str = 0;
	if (!(str = malloc((len + 1) * sizeof(char))))
		return (0);
	return (str);
}

char		*ft_itoa(int n)
{
	char			*str;
	int				i;
	unsigned int	un;

	if (n == 0)
	{
		if (!(str = malloc(2 * sizeof(char))))
			return (0);
		str[0] = '0';
		str[1] = '\0';
		return (str);
	}
	if (!(str = allocstr(n)))
		return (0);
	un = (n < 0) ? -n : n;
	i = 0;
	while (un > 0)
	{
		str[i++] = (un % 10) + '0';
		un = un / 10;
	}
	if (n < 0)
		str[i++] = '-';
	str[i] = '\0';
	return (reverse(str));
}
