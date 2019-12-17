/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_spe_d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prebeca <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 14:02:39 by prebeca           #+#    #+#             */
/*   Updated: 2019/12/04 12:58:28 by prebeca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	check_prct(t_var *var)
{
	int len;

	if (var->champs_min < 0)
		var->alignmt = L;
	var->champs_min = (var->champs_min < 0) ?
	-var->champs_min : var->champs_min;
	len = 1;
	if (var->alignmt == L)
		var->padding = 0;
	var->precision = 1;
	if (var->champs_min < var->precision)
		var->champs_min = var->precision;
	return (1);
}

int	aff_prct(t_var var)
{
	int		ret;
	int		i;
	char	c;
	int		len;

	len = 1;
	c = ' ';
	if (var.padding == 1)
		c = '0';
	ret = var.champs_min;
	i = 0;
	if (var.alignmt == R)
	{
		while (var.precision + i < var.champs_min && ++i)
			write(1, &c, 1);
		write(1, "%", len);
		free(var.value);
		return (ret);
	}
	write(1, "%", len);
	i = 0;
	while (var.precision + i < var.champs_min && ++i)
		write(1, &c, 1);
	free(var.value);
	return (ret);
}
