/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prebeca <prebeca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 04:22:17 by prebeca           #+#    #+#             */
/*   Updated: 2020/02/04 05:21:18 by prebeca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int printerr(char *err)
{
	ft_putendl_fd("ERROR", 2);
	ft_putendl_fd(err, 2);
	return (-1);
}

int check_data(t_data *data)
{
	if (data->map.res_h == 0 || data->map.res_w == 0)
		return (printerr("bad screen res"));
	if (data->player.pos_x == 0 || data->player.pos_y == 0)
		return (printerr("no player pos found"));
	if (data->map.texture_no == 0 || data->map.texture_so == 0 ||data->map.texture_ea == 0 ||data->map.texture_we == 0)
		return (printerr("texture file error"));
}