/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prebeca <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 17:35:45 by prebeca           #+#    #+#             */
/*   Updated: 2019/11/14 12:50:28 by prebeca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*substr;
	unsigned long	slen;

	if (!s)
		return (0);
	slen = ft_strlen(s);
	start = (start > slen) ? slen : start;
	len = (start + len > slen) ? slen - start : len;
	substr = 0;
	if (!(substr = malloc((len + 1) * sizeof(char))))
		return (0);
	ft_strlcpy(substr, s + start, len + 1);
	return (substr);
}
