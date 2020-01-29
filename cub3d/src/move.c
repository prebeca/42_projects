/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prebeca <prebeca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 14:10:24 by prebeca           #+#    #+#             */
/*   Updated: 2020/01/21 16:49:00 by prebeca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int move(t_data *data)
{
    double tmp_dir_x;
    double tmp_screen_dir_x;
    if (data->move.up)
    {
        if (data->map.map[(int)(data->cam.x + data->cam.dir_x * data->cam.speed)][(int)data->cam.y] == 0)
            data->cam.x += data->cam.dir_x * data->cam.speed;
        if (data->map.map[(int)data->cam.x][(int)(data->cam.y + data->cam.dir_y * data->cam.speed)] == 0)
            data->cam.y += data->cam.dir_y * data->cam.speed;
    }
    if (data->move.down)
    {
        if (data->map.map[(int)(data->cam.x - data->cam.dir_x * data->cam.speed)][(int)data->cam.y] == 0)
            data->cam.x -= data->cam.dir_x * data->cam.speed;
        if (data->map.map[(int)data->cam.x][(int)(data->cam.y - data->cam.dir_y * data->cam.speed)] == 0)
            data->cam.y -= data->cam.dir_y * data->cam.speed;
    }
    if (data->move.right)
    {
        if (data->map.map[(int)(data->cam.x + data->cam.screen_dir_x * data->cam.speed)][(int)data->cam.y] == 0)
            data->cam.x += data->cam.screen_dir_x * data->cam.speed;
        if (data->map.map[(int)data->cam.x][(int)(data->cam.y + data->cam.screen_dir_y * data->cam.speed)] == 0)
            data->cam.y += data->cam.screen_dir_y * data->cam.speed;
    }
    if (data->move.left)
    {
        if (data->map.map[(int)(data->cam.x - data->cam.screen_dir_x * data->cam.speed)][(int)data->cam.y] == 0)
            data->cam.x -= data->cam.screen_dir_x * data->cam.speed;
        if (data->map.map[(int)data->cam.x][(int)(data->cam.y - data->cam.screen_dir_y * data->cam.speed)] == 0)
            data->cam.y -= data->cam.screen_dir_y * data->cam.speed;
    }
    if (data->move.rot_speed)
    {
        tmp_dir_x = data->cam.dir_x;
        data->cam.dir_x = data->cam.dir_x * cos(-data->move.rot_speed) - data->cam.dir_y * sin(-data->move.rot_speed);
        data->cam.dir_y = tmp_dir_x * sin(-data->move.rot_speed) + data->cam.dir_y * cos(-data->move.rot_speed);    
        tmp_screen_dir_x = data->cam.screen_dir_x;
        data->cam.screen_dir_x = data->cam.screen_dir_x * cos(-data->move.rot_speed) - data->cam.screen_dir_y * sin(-data->move.rot_speed);
        data->cam.screen_dir_y = tmp_screen_dir_x * sin(-data->move.rot_speed) + data->cam.screen_dir_y * cos(-data->move.rot_speed);
    }
    raycast(data);
    return (0);
}
