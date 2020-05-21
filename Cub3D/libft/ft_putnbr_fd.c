/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prebeca <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 13:02:52 by prebeca           #+#    #+#             */
/*   Updated: 2019/11/13 15:55:30 by prebeca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int un;

	un = (n < 0) ? -n : n;
	if (n < 0)
		ft_putchar_fd('-', fd);
	if (un >= 10)
		ft_putnbr_fd((un / 10), fd);
	ft_putchar_fd((un % 10) + '0', fd);
}
