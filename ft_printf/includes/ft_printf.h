/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prebeca <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 14:41:38 by prebeca           #+#    #+#             */
/*   Updated: 2019/12/11 02:21:43 by prebeca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "libft.h"

# define CONV_SPE "cspdiuxX%"

typedef enum	{
	R,
	L
}	t_align;

typedef struct	s_var
{
	t_align		alignmt;
	int			padding;
	int			champs_min;
	int			precision;
	char		conv_spe;
	void		*value;
	int			null_value;
}				t_var;

/*
** ft_printf
*/
int				ft_printf(const char *str, ...);

/*
** Parser
*/
int				get_flags(const char *str, t_var *var, va_list ap, int *len);

/*
** Checkers
*/
int				check_var(t_var *var);
int				check_c(t_var *var);
int				check_s(t_var *var);
int				check_d(t_var *var);
int				check_p(t_var *var);
int				check_u(t_var *var);
int				check_x(t_var *var);
int				check_prct(t_var *var);

/*
** Printers
*/
int				aff_var(t_var var);
int				aff_c(t_var var);
int				aff_s(t_var var);
int				aff_d(t_var var);
int				aff_p(t_var var);
int				aff_u(t_var var);
int				aff_x(t_var var);
int				aff_prct(t_var var);

/*
** Others
*/
void			init_var(t_var *var);
char			*ft_itoa_base(long nbr, char *base);

#endif
