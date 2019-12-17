/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_spe_u.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prebeca <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 16:41:59 by prebeca           #+#    #+#             */
/*   Updated: 2019/12/03 17:31:04 by prebeca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			check_u(t_var *var)
{
	int len;

	if (var->champs_min < 0)
		var->alignmt = L;
	var->champs_min = (var->champs_min < 0) ?
	-var->champs_min : var->champs_min;
	if (!(var->value = ft_itoa_base((unsigned int)var->value, "0123456789")))
		return (-1);
	len = (int)ft_strlen(var->value);
	if (((char*)var->value)[0] == '0' && var->precision == 0)
		len = 0;
	if (var->alignmt == L || var->precision > -1)
		var->padding = 0;
	if (var->precision == -1)
		var->precision = len;
	if (var->precision < len)
		var->precision = len;
	if (var->champs_min < var->precision)
		var->champs_min = var->precision;
	return (1);
}

static void	aff_u_r(t_var var, char c, int len)
{
	int i;

	i = 0;
	while (var.precision + i < var.champs_min && ++i)
		write(1, &c, 1);
	i = 0;
	while ((int)ft_strlen(var.value) + i < var.precision && ++i)
		write(1, "0", 1);
	write(1, (char*)var.value, len);
}

static void	aff_u_l(t_var var, char c, int len)
{
	int i;

	i = 0;
	while ((int)ft_strlen(var.value) + i < var.precision && ++i)
		write(1, "0", 1);
	write(1, (char*)var.value, len);
	i = 0;
	while (var.precision + i < var.champs_min && ++i)
		write(1, &c, 1);
}

int			aff_u(t_var var)
{
	int		ret;
	char	c;
	int		len;

	len = (int)ft_strlen(var.value);
	if (((char*)var.value)[0] == '0' && var.precision == 0)
		len = 0;
	c = ' ';
	if (var.padding == 1)
		c = '0';
	ret = var.champs_min;
	if (var.alignmt == R)
		aff_u_r(var, c, len);
	else
		aff_u_l(var, c, len);
	free(var.value);
	return (ret);
}
