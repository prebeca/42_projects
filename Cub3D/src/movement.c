/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/16 13:42:25 by user42            #+#    #+#             */
/*   Updated: 2020/05/18 13:26:32 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_left_right(t_data *data)
{
	int mod;

	if (data->cam.right && !data->cam.left)
		mod = 1;
	else if (data->cam.left && !data->cam.right)
		mod = -1;
	else
		return ;
	if (ft_ischarset(data->map.tile_map[(int)data->cam.y][(int)(data->cam.x +
	data->cam.px * (SPEED * mod))], "02NSEw"))
		data->cam.x += data->cam.px * (SPEED * mod);
	if (ft_ischarset(data->map.tile_map[(int)(data->cam.y + data->cam.py *
	(SPEED * mod))][(int)data->cam.x], "02NSEw"))
		data->cam.y += data->cam.py * (SPEED * mod);
}

void	move_fwrd_bckwrd(t_data *data)
{
	int mod;

	if (data->cam.forward && !data->cam.backward)
		mod = 1;
	else if (data->cam.backward && !data->cam.forward)
		mod = -1;
	else
		return ;
	if (ft_ischarset(data->map.tile_map[(int)data->cam.y][(int)(data->cam.x +
	data->cam.dx * (SPEED * mod))], "02NSEw"))
		data->cam.x += data->cam.dx * (SPEED * mod);
	if (ft_ischarset(data->map.tile_map[(int)(data->cam.y + data->cam.dy *
	(SPEED * mod))][(int)data->cam.x], "02NSEw"))
		data->cam.y += data->cam.dy * (SPEED * mod);
}

void	rotate(t_data *data)
{
	double	dx_tmp;
	double	px_tmp;
	int		mod;

	if (data->cam.rot_right && !data->cam.rot_left)
		mod = 1;
	else if (data->cam.rot_left && !data->cam.rot_right)
		mod = -1;
	else
		return ;
	dx_tmp = data->cam.dx;
	data->cam.dx = data->cam.dx * cos(ROT_SPEED * mod) -
	data->cam.dy * sin(ROT_SPEED * mod);
	data->cam.dy = dx_tmp * sin(ROT_SPEED * mod) +
	data->cam.dy * cos(ROT_SPEED * mod);
	px_tmp = data->cam.px;
	data->cam.px = data->cam.px * cos(ROT_SPEED * mod) -
	data->cam.py * sin(ROT_SPEED * mod);
	data->cam.py = px_tmp * sin(ROT_SPEED * mod) +
	data->cam.py * cos(ROT_SPEED * mod);
}

void	move(t_data *data)
{
	move_fwrd_bckwrd(data);
	move_left_right(data);
	rotate(data);
}
