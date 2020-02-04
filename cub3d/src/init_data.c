/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prebeca <prebeca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 23:22:19 by prebeca           #+#    #+#             */
/*   Updated: 2020/02/04 03:36:40 by prebeca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int init_mlx(t_data *data)
{
	if ((data->mlx.win_ptr = mlx_new_window(data->mlx.mlx_ptr, data->map.res_w, data->map.res_h, "Cub3d")) == 0)
		return (-1);
	mlx_hook(data->mlx.win_ptr, DestroyNotify, StructureNotifyMask, &exit_hook, data);
	mlx_hook(data->mlx.win_ptr, KeyPress, KeyPressMask, &key_press, data);
	mlx_hook(data->mlx.win_ptr, KeyRelease, KeyReleaseMask, &key_release, data);
	mlx_loop_hook(data->mlx.mlx_ptr, &loop_hook, data);
	return (0);
}

static int init_player(t_data *data)
{
	data->player.move.up = 0;
	data->player.move.down = 0;
	data->player.move.right = 0;
	data->player.move.left = 0;
	data->player.move.speed = 0.15;
	data->player.move.sprint = 1;
	data->player.move.rot_speed = 0;
	return (0);
}

int	init_data(t_data *data)
{
	if (init_mlx(data) == -1)
		return (-1);
	init_player(data);
	return (0);
}