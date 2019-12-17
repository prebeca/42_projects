/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_spe_c.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prebeca <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 16:12:55 by prebeca           #+#    #+#             */
/*   Updated: 2019/12/04 16:08:52 by prebeca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	check_c(t_var *var)
{
	if (var->champs_min < 0)
		var->alignmt = L;
	var->champs_min = (var->champs_min < 0) ?
	-var->champs_min : var->champs_min;
	if (var->precision != -1)
		var->precision = -1;
	return (1);
}

int	aff_c(t_var var)
{
	int ret;

	ret = (var.champs_min > 1) ? var.champs_min : 1;
	if (var.alignmt == R)
	{
		while (var.champs_min - 1 > 0 && var.champs_min--)
			write(1, " ", 1);
		ft_putchar_fd((int)var.value, 1);
	}
	else
	{
		ft_putchar_fd((int)var.value, 1);
		while (var.champs_min - 1 > 0 && var.champs_min--)
			write(1, " ", 1);
	}
	return (ret);
}
