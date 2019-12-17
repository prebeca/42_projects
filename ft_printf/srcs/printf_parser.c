/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prebeca <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 10:34:17 by prebeca           #+#    #+#             */
/*   Updated: 2019/12/04 15:07:13 by prebeca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	get_arg(t_var *var, va_list ap)
{
	if (var->conv_spe == 'c')
		var->value = (va_arg(ap, int*));
	else if (var->conv_spe == 's')
		var->value = (va_arg(ap, char*));
	else if (var->conv_spe == 'p')
		var->value = (va_arg(ap, long*));
	else if (var->conv_spe == 'd' || var->conv_spe == 'i')
		var->value = (va_arg(ap, int*));
	else if (var->conv_spe == 'u')
		var->value = (va_arg(ap, unsigned int*));
	else if (var->conv_spe == 'x' || var->conv_spe == 'X')
		var->value = (va_arg(ap, unsigned int*));
}

static int	get_preci(const char *str, t_var *var, va_list ap)
{
	int len;

	len = 0;
	if (ft_isdigit(str[len]))
		var->precision = ft_atoi(str);
	else if (str[len] == '*' && ++len)
		var->precision = va_arg(ap, int);
	else
		var->precision = 0;
	return (len);
}

int			get_flags(const char *str, t_var *var, va_list ap, int *len)
{
	while (!ft_strchr("cspdiuxX%", str[*len]))
		if (str[*len] == '-' && ++(*len))
			var->alignmt = L;
		else if (str[*len] == '0' && ++(*len))
			var->padding = 1;
		else if (ft_isdigit(str[*len]))
		{
			var->champs_min = ft_atoi(str + *len);
			while (ft_isdigit(str[*len]))
				++(*len);
		}
		else if (str[*len] == '*' && ++(*len))
			var->champs_min = va_arg(ap, int);
		else if (str[*len] == '.' && ++(*len))
		{
			*len += get_preci(str + *len, var, ap);
			while (ft_isdigit(str[*len]))
				++(*len);
		}
		else
			return (0);
	var->conv_spe = str[(*len)++];
	get_arg(var, ap);
	(*len)++;
	return (1);
}
