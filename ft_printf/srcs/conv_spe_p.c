/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_spe_p.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prebeca <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 16:44:09 by prebeca           #+#    #+#             */
/*   Updated: 2019/12/04 16:29:21 by prebeca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			check_p(t_var *var)
{
	int len;

	if (var->champs_min < 0)
		var->alignmt = L;
	var->champs_min = (var->champs_min < 0) ?
	-var->champs_min : var->champs_min;
	if ((long)var->value < 0)
		return (-1);
	if (!(var->value = ft_itoa_base((long)var->value, "0123456789abcdef")))
		return (-1);
	len = (int)ft_strlen(var->value);
	if (((char*)var->value)[0] == '0' && var->precision == 0)
		len = 0;
	if (var->precision == -1 || var->precision < len)
		var->precision = len;
	if (var->champs_min < var->precision + 2)
		var->champs_min = var->precision + 2;
	return (1);
}

static void	aff_p_r(t_var var, int len)
{
	int i;

	i = 0;
	while (var.precision + 2 + i < var.champs_min && ++i)
		write(1, " ", 1);
	write(1, "0x", 2);
	i = 0;
	while (len + i < var.precision && ++i)
		write(1, "0", 1);
	write(1, (char*)var.value + var.null_value, len);
	free(var.value);
}

static void	aff_p_l(t_var var, int len)
{
	int i;

	i = 0;
	write(1, "0x", 2);
	while (len + i < var.precision && ++i)
		write(1, "0", 1);
	write(1, (char*)var.value + var.null_value, len);
	while (var.precision + 2 + i < var.champs_min && ++i)
		write(1, " ", 1);
	free(var.value);
}

int			aff_p(t_var var)
{
	int		len;
	int		i;

	len = (int)ft_strlen(var.value);
	if (((char*)var.value)[0] == '0' && var.precision == 0)
		len = 0;
	i = 0;
	if (var.alignmt == R)
	{
		aff_p_r(var, len);
		return (var.champs_min);
	}
	aff_p_l(var, len);
	return (var.champs_min);
}
