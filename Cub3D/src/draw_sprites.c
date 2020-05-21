/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 15:30:18 by user42            #+#    #+#             */
/*   Updated: 2020/05/21 11:57:11 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sprite_ray_init(t_data *data, t_sprite_ray *ray, t_list *sprite)
{
	ray->x = ((t_point*)sprite->content)->x - data->cam.x;
	ray->y = ((t_point*)sprite->content)->y - data->cam.y;
	ray->inv_det = 1.0 / (data->cam.px * data->cam.dy -
	data->cam.dx * data->cam.py);
	ray->tx = ray->inv_det * (data->cam.dy * ray->x - data->cam.dx * ray->y);
	ray->ty = ray->inv_det * (-data->cam.py * ray->x + data->cam.px * ray->y);
	ray->screen_x = (int)(data->map.width / 2) * (1 + ray->tx / ray->ty);
}

void	sprite_drawing_limit(t_data *data, t_sprite_ray *ray)
{
	ray->height = abs((int)(data->map.height / ray->ty));
	ray->draw_start_y = -ray->height / 2 + data->map.height / 2;
	if (ray->draw_start_y < 0)
		ray->draw_start_y = 0;
	ray->draw_end_y = ray->height / 2 + data->map.height / 2;
	if (ray->draw_end_y >= data->map.height)
		ray->draw_end_y = data->map.height - 1;
	ray->width = abs((int)(data->map.height / ray->ty));
	ray->draw_start_x = -ray->width / 2 + ray->screen_x;
	if (ray->draw_start_x < 0)
		ray->draw_start_x = 0;
	ray->draw_end_x = ray->width / 2 + ray->screen_x;
	if (ray->draw_end_x >= data->map.width)
		ray->draw_end_x = data->map.width - 1;
}

int		get_color(int texture_x, int texture_y, t_data *data)
{
	int color;

	color = 0;
	color += data->map.texture_sprite->data_address[
		data->map.texture_sprite->line_size * texture_y +
		texture_x * data->map.texture_sprite->bpp / 8];
	color += data->map.texture_sprite->data_address[
		data->map.texture_sprite->line_size * texture_y +
		texture_x * data->map.texture_sprite->bpp / 8 + 1] * 256;
	color += data->map.texture_sprite->data_address[
		data->map.texture_sprite->line_size * texture_y +
		texture_x * data->map.texture_sprite->bpp / 8 + 2]
		* 256 * 256;
	return (color);
}

void	draw_sprite_col(t_data *data, t_sprite_ray *ray)
{
	int		y;
	int		x;
	int		texture_x;
	int		texture_y;
	int		color;

	x = ray->draw_start_x - 1;
	while (++x < ray->draw_end_x)
	{
		texture_x = (int)(256 * (x - (-ray->width / 2 + ray->screen_x)) *
		data->map.texture_sprite->width / ray->width) / 256;
		y = ray->draw_start_y - 1;
		if (ray->ty > 0 && x > 0 && x < data->map.width &&
		ray->ty < data->wall_dist[x])
			while (++y < ray->draw_end_y)
			{
				texture_y = (((y * 256 - data->map.height * 128 + ray->height *
				128) * data->map.texture_sprite->height) /
				ray->height) / 256;
				color = get_color(texture_x, texture_y, data);
				if ((color & 0x00FFFFFF) != 0)
					set_pixel_color(x, y, color, data);
			}
	}
}

void	draw_sprites(t_data *data)
{
	t_list			*sprite;
	t_sprite_ray	ray;

	sort_sprites(data->map.sprite_list, data);
	sprite = data->map.sprite_list;
	while (sprite)
	{
		sprite_ray_init(data, &ray, sprite);
		sprite_drawing_limit(data, &ray);
		draw_sprite_col(data, &ray);
		sprite = sprite->next;
	}
}
