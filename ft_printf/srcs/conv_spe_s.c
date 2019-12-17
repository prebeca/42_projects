/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_spe_s.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prebeca <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 18:25:24 by prebeca           #+#    #+#             */
/*   Updated: 2019/12/03 17:20:40 by prebeca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	check_s(t_var *var)
{
	if (var->champs_min < 0)
		var->alignmt = L;
	var->champs_min = (var->champs_min < 0) ?
	-var->champs_min : var->champs_min;
	if (!var->value)
	{
		if (!(var->value = ft_strdup("(null)")))
			return (-1);
		var->null_value = 1;
	}
	if (var->precision < 0 || var->precision >
			(int)ft_strlen((char *)var->value))
		var->precision = (int)ft_strlen((char*)var->value);
	if (var->champs_min < var->precision)
		var->champs_min = var->precision;
	return (1);
}

int	aff_s(t_var var)
{
	int		ret;
	char	c;

	c = (var.padding == 1) ? '0' : ' ';
	ret = var.champs_min;
	if (var.alignmt == R)
	{
		while (var.champs_min - var.precision > 0 && var.champs_min--)
			write(1, &c, 1);
		write(1, (char*)var.value, var.precision);
	}
	else
	{
		write(1, (char*)var.value, var.precision);
		while (var.champs_min - var.precision > 0 && var.champs_min--)
			write(1, " ", 1);
	}
	if (var.null_value)
		free(var.value);
	if (ret < 0)
		return (0);
	return (ret);
}
