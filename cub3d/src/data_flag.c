/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_flag.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prebeca <prebeca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 12:52:08 by prebeca           #+#    #+#             */
/*   Updated: 2020/01/29 15:35:07 by prebeca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_flag *new_flag(char *flag_name, int (*fct)(t_data*, char**))
{
    t_flag *flag;

    if (flag_name == 0 || fct == 0)
        return (0);
    if ((flag = malloc(sizeof(t_flag))) == 0)
        return (0);
    flag->flag = ft_strdup(flag_name);
    flag->fct = fct;
    return (flag);
}

int init_flag_table(t_flag **flag_table)
{
    flag_table[0] = new_flag("R", &get_res);
    flag_table[1] = new_flag("NO", &texture_switch);
    flag_table[2] = new_flag("SO", &texture_switch);
    flag_table[3] = new_flag("WE", &texture_switch);
    flag_table[4] = new_flag("EA", &texture_switch);
    flag_table[5] = new_flag("S", &texture_switch);
    flag_table[6] = new_flag("F", &texture_switch);
    flag_table[7] = new_flag("C", &texture_switch);
    flag_table[NB_FLAGS] = 0;
    return (0);
}