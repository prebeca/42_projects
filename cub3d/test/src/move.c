/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prebeca <prebeca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 14:10:24 by prebeca           #+#    #+#             */
/*   Updated: 2020/01/31 02:51:29 by prebeca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int move(t_data *data)
{
    double tmp_dir_x;
    double tmp_screen_dir_x;
    if (data->player.move.up)
    {
        if (data->map.map[(int)(data->player.pos_x + data->player.dir_x * (data->player.move.speed * data->player.move.sprint))][(int)data->player.pos_y] == 0)
            data->player.pos_x += data->player.dir_x * (data->player.move.speed * data->player.move.sprint);
        if (data->map.map[(int)data->player.pos_x][(int)(data->player.pos_y + data->player.dir_y * (data->player.move.speed * data->player.move.sprint))] == 0)
            data->player.pos_y += data->player.dir_y * (data->player.move.speed * data->player.move.sprint);
    }
    if (data->player.move.down)
    {
        if (data->map.map[(int)(data->player.pos_x - data->player.dir_x * (data->player.move.speed * data->player.move.sprint))][(int)data->player.pos_y] == 0)
            data->player.pos_x -= data->player.dir_x * (data->player.move.speed * data->player.move.sprint);
        if (data->map.map[(int)data->player.pos_x][(int)(data->player.pos_y - data->player.dir_y * (data->player.move.speed * data->player.move.sprint))] == 0)
            data->player.pos_y -= data->player.dir_y * (data->player.move.speed * data->player.move.sprint);
    }
    if (data->player.move.right)
    {
        if (data->map.map[(int)(data->player.pos_x + data->cam.screen_dir_x * (data->player.move.speed * data->player.move.sprint))][(int)data->player.pos_y] == 0)
            data->player.pos_x += data->cam.screen_dir_x * (data->player.move.speed * data->player.move.sprint);
        if (data->map.map[(int)data->player.pos_x][(int)(data->player.pos_y + data->cam.screen_dir_y * (data->player.move.speed * data->player.move.sprint))] == 0)
            data->player.pos_y += data->cam.screen_dir_y * (data->player.move.speed * data->player.move.sprint);
    }
    if (data->player.move.left)
    {
        if (data->map.map[(int)(data->player.pos_x - data->cam.screen_dir_x * (data->player.move.speed * data->player.move.sprint))][(int)data->player.pos_y] == 0)
            data->player.pos_x -= data->cam.screen_dir_x * (data->player.move.speed * data->player.move.sprint);
        if (data->map.map[(int)data->player.pos_x][(int)(data->player.pos_y - data->cam.screen_dir_y * (data->player.move.speed * data->player.move.sprint))] == 0)
            data->player.pos_y -= data->cam.screen_dir_y * (data->player.move.speed * data->player.move.sprint);
    }
    if (data->player.move.rot_speed)
    {
        tmp_dir_x = data->player.dir_x;
        data->player.dir_x = data->player.dir_x * cos(-data->player.move.rot_speed) - data->player.dir_y * sin(-data->player.move.rot_speed);
        data->player.dir_y = tmp_dir_x * sin(-data->player.move.rot_speed) + data->player.dir_y * cos(-data->player.move.rot_speed);    
        tmp_screen_dir_x = data->cam.screen_dir_x;
        data->cam.screen_dir_x = data->cam.screen_dir_x * cos(-data->player.move.rot_speed) - data->cam.screen_dir_y * sin(-data->player.move.rot_speed);
        data->cam.screen_dir_y = tmp_screen_dir_x * sin(-data->player.move.rot_speed) + data->cam.screen_dir_y * cos(-data->player.move.rot_speed);
    }
    raycast(data);
    return (0);
}
