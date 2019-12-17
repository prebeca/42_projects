/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prebeca <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 12:20:00 by prebeca           #+#    #+#             */
/*   Updated: 2019/12/04 15:23:45 by prebeca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	get_text(const char *str, int *index)
{
	int i;

	i = 0;
	while (str[i] && str[i] != '%')
		++i;
	write(1, str, i);
	*index += i;
	return (i);
}

static int	get_args(const char *str, va_list ap, int *index)
{
	t_var	var;
	int		len;
	int		i;

	init_var(&var);
	len = 0;
	i = get_flags(str + 1, &var, ap, &len);
	*index += len;
	if (i == 0)
	{
		*index += 1;
		return (len);
	}
	if (check_var(&var) == -1)
		return (-1);
	return (aff_var(var));
}

int			ft_printf(const char *str, ...)
{
	va_list	ap;
	int		i;
	int		ret;
	int		tmp;

	if (!str)
		return (-1);
	va_start(ap, str);
	i = 0;
	ret = 0;
	while (str[i])
	{
		if (str[i] != '%')
			ret += get_text(str + i, &i);
		else if ((tmp = get_args(str + i, ap, &i)) == -1)
			return (-1);
		else
			ret += tmp;
	}
	va_end(ap);
	return (ret);
}
