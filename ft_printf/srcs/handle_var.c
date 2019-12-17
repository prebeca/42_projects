/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prebeca <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 10:36:25 by prebeca           #+#    #+#             */
/*   Updated: 2019/12/04 10:38:00 by prebeca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	init_var(t_var *var)
{
	var->alignmt = R;
	var->padding = 0;
	var->champs_min = 0;
	var->precision = -1;
	var->conv_spe = '\0';
	var->value = 0;
	var->null_value = 0;
}

int		check_var(t_var *var)
{
	if (var->conv_spe == 'c' && check_c(var) > 0)
		return (1);
	else if (var->conv_spe == 's' && check_s(var) > 0)
		return (1);
	else if ((var->conv_spe == 'd' || var->conv_spe == 'i') && check_d(var) > 0)
		return (1);
	else if (var->conv_spe == 'p' && check_p(var) > 0)
		return (1);
	else if (var->conv_spe == 'u' && check_u(var) > 0)
		return (1);
	else if ((var->conv_spe == 'x' || var->conv_spe == 'X') && check_x(var) > 0)
		return (1);
	else if (var->conv_spe == '%' && check_prct(var) > 0)
		return (1);
	return (-1);
}

int		aff_var(t_var var)
{
	if (var.conv_spe == 'c')
		return (aff_c(var));
	else if (var.conv_spe == 's')
		return (aff_s(var));
	else if (var.conv_spe == 'd' || var.conv_spe == 'i')
		return (aff_d(var));
	else if (var.conv_spe == 'p')
		return (aff_p(var));
	else if (var.conv_spe == 'u')
		return (aff_u(var));
	else if (var.conv_spe == 'x' || var.conv_spe == 'X')
		return (aff_x(var));
	else if (var.conv_spe == '%')
		return (aff_prct(var));
	return (-1);
}
