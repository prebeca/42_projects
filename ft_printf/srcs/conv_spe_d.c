/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_spe_d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prebeca <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 14:02:39 by prebeca           #+#    #+#             */
/*   Updated: 2019/12/04 13:48:39 by prebeca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			check_d(t_var *var)
{
	int len;

	if (var->champs_min < 0)
		var->alignmt = L;
	var->champs_min = (var->champs_min < 0) ?
	-var->champs_min : var->champs_min;
	var->null_value = ((int)var->value < 0) ? 1 : 0;
	if (!(var->value = ft_itoa((int)var->value)))
		return (-1);
	len = (int)ft_strlen(var->value) - var->null_value;
	if (((char*)var->value)[0] == '0' && var->precision == 0)
		len = 0;
	if (var->alignmt == L || var->precision > -1)
		var->padding = 0;
	if (var->precision == -1)
		var->precision = len;
	if (var->precision < len)
		var->precision = len;
	if (var->champs_min < var->precision)
		var->champs_min = var->precision + var->null_value;
	return (1);
}

static void	aff_d_r(t_var var, char c, int len)
{
	int i;

	i = 0;
	if (var.null_value && var.padding)
		write(1, (char*)var.value, 1);
	while (var.precision + i < var.champs_min - var.null_value && ++i)
		write(1, &c, 1);
	if (var.null_value && !var.padding)
		write(1, (char*)var.value, 1);
	i = 0;
	while ((int)ft_strlen(var.value) - var.null_value + i
			< var.precision && ++i)
		write(1, "0", 1);
	write(1, (char*)var.value + var.null_value, len);
}

static void	aff_d_l(t_var var, char c, int len)
{
	int i;

	i = 0;
	if (var.null_value)
		write(1, (char*)var.value, 1);
	while ((int)ft_strlen(var.value) - var.null_value + i
			< var.precision && ++i)
		write(1, "0", 1);
	write(1, (char*)var.value + var.null_value, len);
	i = 0;
	while (var.precision + i < var.champs_min - var.null_value && ++i)
		write(1, &c, 1);
}

int			aff_d(t_var var)
{
	int		ret;
	char	c;
	int		len;

	len = (int)ft_strlen(var.value) - var.null_value;
	if (((char*)var.value)[0] == '0' && var.precision == 0)
		len = 0;
	c = ' ';
	if (var.padding == 1)
		c = '0';
	ret = var.champs_min;
	if (var.alignmt == R)
		aff_d_r(var, c, len);
	else
		aff_d_l(var, c, len);
	free(var.value);
	if (var.champs_min > len)
		return (ret);
	return (ret + var.null_value);
}
