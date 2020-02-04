/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prebeca <prebeca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 23:35:22 by prebeca           #+#    #+#             */
/*   Updated: 2020/02/04 03:53:37 by prebeca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int loop_hook(t_data *data)
{
	if (data->player.move.up == 1 || data->player.move.down == 1 || data->player.move.right == 1 || data->player.move.left == 1 || data->player.move.rot_speed != 0)
		move(data);
	return (0);
}

int	exit_hook(t_data *data)
{
	(void)data;
	exit(0);
	return (0);
}

int key_press(int keycode, t_data *data)
{
    if (keycode == 53)
        exit(0);
    if (keycode == 13)
        data->player.move.up = 1;
    else if (keycode == 0)
        data->player.move.left = 1;
    else if (keycode == 1)
        data->player.move.down = 1;
    else if (keycode == 2)
        data->player.move.right = 1;
    else if (keycode == 123)
        data->player.move.rot_speed = -0.1;
    else if (keycode == 124)
        data->player.move.rot_speed = 0.1;
    else if (keycode == 257)
        data->player.move.sprint = 3;
    return (0);
}

int key_release(int keycode, t_data *data)
{
    if (keycode == 13)
        data->player.move.up = 0;
    else if (keycode == 0)
        data->player.move.left = 0;
    else if (keycode == 1)
        data->player.move.down = 0;
    else if (keycode == 2)
        data->player.move.right = 0;
    else if (keycode == 123)
        data->player.move.rot_speed = 0;
    else if (keycode == 124)
        data->player.move.rot_speed = 0;
    else if (keycode == 257)
        data->player.move.sprint = 1;
    return (0);
}