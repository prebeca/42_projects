/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 23:05:33 by user42            #+#    #+#             */
/*   Updated: 2020/06/16 13:14:48 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ray_casting(t_data *data, t_ray *ray)
{
	t_bool hit;

	hit = false;
	while (hit == false)
	{
		if (ray->len_x < ray->len_y)
		{
			ray->len_x += ray->dlen_x;
			ray->map_x += ray->step_x;
			ray->wall_side = 0;
		}
		else
		{
			ray->len_y += ray->dlen_y;
			ray->map_y += ray->step_y;
			ray->wall_side = 1;
		}
		if (data->map.tile_map[ray->map_y][ray->map_x] == '1')
			hit = true;
	}
}

void	texture_switch(t_data *data, t_ray *ray)
{
	if (ray->wall_side == 1 && ray->dy > 0)
		ray->texture = data->map.texture_so;
	else if (ray->wall_side == 1 && ray->dy < 0)
		ray->texture = data->map.texture_no;
	else if (ray->wall_side == 0 && ray->dx > 0)
		ray->texture = data->map.texture_ea;
	else
		ray->texture = data->map.texture_we;
	ray->text_x = (1 - ray->wall_x) * ray->texture->width;
	if (ray->wall_side == 0 && ray->dx > 0)
		ray->text_x = ray->texture->width - ray->text_x - 1;
	if (ray->wall_side == 1 && ray->dy < 0)
		ray->text_x = ray->texture->width - ray->text_x - 1;
	if (ray->text_x < 0)
		ray->text_x = 0;
	if (ray->text_x > ray->texture->width)
		ray->text_x = 0;
}

void	draw_col_texture(t_ray *ray, int x, int y, t_data *data)
{
	ray->text_y = (ray->text_y < 0) ? 0 : ray->text_y;
	ray->text_y = (ray->text_y > ray->texture->height) ?
	ray->texture->height : ray->text_y;
	ft_memcpy(&data->image.data_address[(y *
	data->image.line_size + x * data->image.bpp / 8)],
	&ray->texture->data_address[(ray->text_y *
	ray->texture->line_size + ray->text_x *
	ray->texture->bpp / 8)], ray->texture->bpp / 8);
}

void	draw_col(t_data *data, t_ray *ray, int x)
{
	int wall_height;
	int wall_start;
	int wall_end;
	int	y;

	texture_switch(data, ray);
	wall_height = abs((int)(data->map.height / ray->wall_dist));
	wall_start = (int)(-wall_height / 2 + data->map.height / 2);
	wall_end = (int)(wall_height / 2 + data->map.height / 2);
	if (wall_start < 0)
		wall_start = 0;
	if (wall_end > data->map.height)
		wall_end = data->map.height;
	y = 0;
	while (y < wall_start)
		set_pixel_color(x, y++, data->map.ceiling_color, data);
	while (y < wall_end)
	{
		ray->text_y = (y * 2 - data->map.height + wall_height) *
		(ray->texture->height / 2) / wall_height;
		draw_col_texture(ray, x, y++, data);
	}
	while (y < data->map.height)
		set_pixel_color(x, y++, data->map.floor_color, data);
}

void	draw(t_data *data)
{
	t_ray	ray;
	int		x;

	if (data->image.img_ptr)
		mlx_destroy_image(data->mlx.mlx_ptr, data->image.img_ptr);
	data->image.height = data->map.height;
	data->image.width = data->map.width;
	data->image.img_ptr = mlx_new_image(data->mlx.mlx_ptr,
	data->image.width, data->image.height);
	data->image.data_address = mlx_get_data_addr(data->image.img_ptr,
	&data->image.bpp, &data->image.line_size, &data->image.endian);
	x = -1;
	while (++x < data->map.width)
	{
		init_ray(data, &ray, x);
		get_step_and_dlen(&ray);
		ray_casting(data, &ray);
		rectify_wall_dist(&ray);
		draw_col(data, &ray, x);
		data->wall_dist[x] = ray.wall_dist;
	}
	draw_sprites(data);
}
