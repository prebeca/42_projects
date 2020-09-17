/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 11:46:29 by user42            #+#    #+#             */
/*   Updated: 2020/05/21 11:52:36 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_ray(t_data *data, t_ray *ray, int x)
{
	ray->center_x_offset = (2 * x / data->map.width) - 1;
	ray->x = data->cam.x;
	ray->y = data->cam.y;
	ray->map_x = (int)ray->x;
	ray->map_y = (int)ray->y;
	ray->dx = data->cam.dx + data->cam.px * ray->center_x_offset;
	ray->dy = data->cam.dy + data->cam.py * ray->center_x_offset;
	ray->len_x = 0;
	ray->len_y = 0;
	ray->dlen_x = sqrt(1 + (ray->dy * ray->dy) / (ray->dx * ray->dx));
	ray->dlen_y = sqrt(1 + (ray->dx * ray->dx) / (ray->dy * ray->dy));
	ray->step_x = 0;
	ray->step_y = 0;
	ray->wall_dist = 0;
	ray->wall_side = 0;
	ray->wall_x = 0;
	ray->texture = 0;
}

void	set_pixel_color(int x, int y, int color, t_data *data)
{
	unsigned char *color_c;

	color_c = (unsigned char*)&color;
	data->image.data_address[y * data->image.line_size + x *
	data->image.bpp / 8] = color_c[0];
	data->image.data_address[y * data->image.line_size + x *
	data->image.bpp / 8 + 1] = color_c[1];
	data->image.data_address[y * data->image.line_size + x *
	data->image.bpp / 8 + 2] = color_c[2];
}

void	get_step_and_dlen(t_ray *ray)
{
	if (ray->dx < 0)
	{
		ray->step_x = -1;
		ray->len_x = (ray->x - ray->map_x) * ray->dlen_x;
	}
	else
	{
		ray->step_x = 1;
		ray->len_x = (ray->map_x + 1.0 - ray->x) * ray->dlen_x;
	}
	if (ray->dy < 0)
	{
		ray->step_y = -1;
		ray->len_y = (ray->y - ray->map_y) * ray->dlen_y;
	}
	else
	{
		ray->step_y = 1;
		ray->len_y = (ray->map_y + 1.0 - ray->y) * ray->dlen_y;
	}
}

void	rectify_wall_dist(t_ray *ray)
{
	if (ray->wall_side == 0)
	{
		ray->wall_x = ray->y + ((ray->map_x - ray->x +
		(1 - ray->step_x) / 2) / ray->dx) * ray->dy;
		ray->wall_dist = fabs((ray->map_x - ray->x +
		(1 - ray->step_x) / 2) / ray->dx);
	}
	else
	{
		ray->wall_x = ray->x + ((ray->map_y - ray->y +
		(1 - ray->step_y) / 2) / ray->dy) * ray->dx;
		ray->wall_dist = fabs((ray->map_y - ray->y +
		(1 - ray->step_y) / 2) / ray->dy);
	}
	ray->wall_x -= (int)ray->wall_x;
}
