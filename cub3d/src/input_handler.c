/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prebeca <prebeca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 12:11:20 by prebeca           #+#    #+#             */
/*   Updated: 2020/01/29 17:02:09 by prebeca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int key_press(int keycode, t_data *data)
{
    if (keycode == 53)
        exit(0);
    if (keycode == 13)
        data->move.up = 1;
    else if (keycode == 0)
        data->move.left = 1;
    else if (keycode == 1)
        data->move.down = 1;
    else if (keycode == 2)
        data->move.right = 1;
    else if (keycode == 123)
        data->move.rot_speed = -0.1;
    else if (keycode == 124)
        data->move.rot_speed = 0.1;
    return (0);
}

int key_release(int keycode, t_data *data)
{
    if (keycode == 13)
        data->move.up = 0;
    else if (keycode == 0)
        data->move.left = 0;
    else if (keycode == 1)
        data->move.down = 0;
    else if (keycode == 2)
        data->move.right = 0;
    else if (keycode == 123)
        data->move.rot_speed = 0;
    else if (keycode == 124)
        data->move.rot_speed = 0;
    return (0);
}