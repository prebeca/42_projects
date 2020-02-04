/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prebeca <prebeca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 00:46:36 by prebeca           #+#    #+#             */
/*   Updated: 2020/02/04 04:54:00 by prebeca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void init_ray(int x, t_ray *ray, t_data *data)
{
	ray->center_x = (2 * x / data->map.res_w) - 1;
	ray->x = data->player.pos_x;
	ray->y = data->player.pos_y;
	ray->dir_x = data->player.dir_x + data->cam.screen_dir_x * ray->center_x;
	ray->dir_y = data->player.dir_y + data->cam.screen_dir_y * ray->center_x;
	ray->map_x = (int)ray->x;
	ray->map_y = (int)ray->y;
	ray->delta_dist_x = sqrt(1 + (ray->dir_y * ray->dir_y) / (ray->dir_x * ray->dir_x));
	ray->delta_dist_y = sqrt(1 + (ray->dir_x * ray->dir_x) / (ray->dir_y * ray->dir_y));
	ray->hit = 0;
}

void set_pixel_color(int x, int y, int color, t_data *data)
{
	unsigned char *color_c;
	color_c = (unsigned char*)&color;
	data->buffer.buffer[y * data->buffer.line_size + x * data->buffer.bpp / 8] = color_c[0];
	data->buffer.buffer[y * data->buffer.line_size + x * data->buffer.bpp / 8 + 1] = color_c[1];
	data->buffer.buffer[y * data->buffer.line_size + x * data->buffer.bpp / 8 + 2] = color_c[2];
}

int    raycast(t_data *data)
{
	
	int x;
	int y;
	double wallx;
	int textx;
	int texty;
	int rgb;
	unsigned char *rgb_char;

	x = 0;
	data->buffer.img_ptr = mlx_new_image(data->mlx.mlx_ptr, data->map.res_w, data->map.res_h);
	data->buffer.buffer = mlx_get_data_addr(data->buffer.img_ptr, &data->buffer.bpp, &data->buffer.line_size, &data->buffer.endian);
	while(x < data->map.res_w)
	{
		t_ray ray;
		
		init_ray(x, &ray, data);
		//
		if (ray.dir_x < 0)
		{
			ray.step_x = -1;
			ray.side_dist_x = (ray.x - ray.map_x) * ray.delta_dist_x;
		}
		else
		{
			ray.step_x = 1;
			ray.side_dist_x = (ray.map_x + 1.0 - ray.x) * ray.delta_dist_x;
		}
		if (ray.dir_y < 0)
		{
			ray.step_y = -1;
			ray.side_dist_y = (ray.y - ray.map_y) * ray.delta_dist_y;
		}
		else
		{
			ray.step_y = 1;
			ray.side_dist_y = (ray.map_y + 1.0 - ray.y) * ray.delta_dist_y;
		}
		//
		while (ray.hit == 0)
		{
			if (ray.side_dist_x < ray.side_dist_y)
			{
				ray.side_dist_x += ray.delta_dist_x;
				ray.map_x += ray.step_x;
				if (ray.step_x == 1)
					ray.face = 0;
				else
					ray.face = 1;
			}
			else
			{
				ray.side_dist_y += ray.delta_dist_y;
				ray.map_y += ray.step_y;
				if (ray.step_y == 1)
					ray.face = 2;
				else
					ray.face = 3;
			}
			if (data->map.map[ray.map_x][ray.map_y] > 0)
				ray.hit = 1;
		}

		//
		if (ray.face == 0 || ray.face == 1)
		{
			ray.len = fabs((ray.map_x - ray.x + (1 - ray.step_x) / 2) / ray.dir_x);
			//wallx = ray.x + ((ray.map_y - ray.y + (1 - ray.step_y) / 2) / ray.dir_y) * ray.dir_x;
		}
		else
		{
			ray.len = fabs((ray.map_y - ray.y + (1 - ray.step_y) / 2) / ray.dir_y);
			//wallx = ray.y + ((ray.map_x - ray.x + (1 - ray.step_x) / 2) / ray.dir_x) * ray.dir_y;
		}
		//
		if (ray.face == 0 || ray.face == 1)
			wallx = ray.y + ((ray.map_x - ray.x + (1 - ray.step_x) / 2) / ray.dir_x) * ray.dir_y;
		else
			wallx = ray.x + ((ray.map_y - ray.y + (1 - ray.step_y) / 2) / ray.dir_y) * ray.dir_x;
		//
		ray.wall_h = abs(data->map.res_h / ray.len);
		wallx -= floor(wallx);
		t_img *cur_text;
		if (ray.face == 0)
			cur_text = data->map.texture_so;
		else if (ray.face == 1)
			cur_text = data->map.texture_no;
		else if (ray.face == 2)
			cur_text = data->map.texture_ea;
		else
			cur_text = data->map.texture_we;

		textx = wallx * cur_text->res_w;
		// if ((ray.face == 0 || ray.face == 1) && ray.dir_x > 0) {
		// 	textx = textsize - textx - 1;
		// }
		// if ((ray.face == 2 || ray.face == 3) && ray.dir_y < 0) {
		// 	textx = textsize - textx - 1;
		// }
		// textx = textsize - textx - 1;
		//
		ray.draw_start = -ray.wall_h / 2 + data->map.res_h / 2;
		ray.draw_end = ray.wall_h / 2 + data->map.res_h / 2;

		//
		if (ray.draw_start < 0)
			ray.draw_start = 0;
		if (ray.draw_end >= data->map.res_h)
			ray.draw_end = data->map.res_h;
		
		//

		//			

		y = ray.draw_start;
		while (y < ray.draw_end)
		{
			
			texty = (y * 2 - data->map.res_h + ray.wall_h) * (cur_text->res_w / 2) / ray.wall_h;

			rgb_char = (unsigned char*)&rgb;

			rgb_char[0] = cur_text->buffer[texty * cur_text->line_size + textx * cur_text->bpp / 8];
			rgb_char[1] = cur_text->buffer[texty * cur_text->line_size + textx * cur_text->bpp / 8 + 1];
			rgb_char[2] = cur_text->buffer[texty * cur_text->line_size + textx * cur_text->bpp / 8 + 2];
			
			set_pixel_color(x, y, rgb, data);
			// ft_memcpy(data->buffer.buffer + (y * data->buffer.line_size + x * data->buffer.bpp / 8),
			// 			data->map.texture_no->buffer + (texty * data->map.texture_no->line_size + textx * data->map.texture_no->bpp / 8),
			// 				data->buffer.bpp);

			// if (ray.face == 0)
			// 	set_pixel_color( x, y, 0xff0000, data);
			// else if (ray.face == 1)
			// 	set_pixel_color( x, y, 0x00ff00, data);
			// else if (ray.face == 2)
			// 	set_pixel_color( x, y, 0x0000ff, data);
			// else
			// 	set_pixel_color( x, y, 0x000000, data);
			
			// if (ray.face == 1)
			// 	mlx_pixel_put(data->mlx.mlx_ptr, data->mlx.win_ptr, x, y, 0xcccccc);
			// else
			// 	mlx_pixel_put(data->mlx.mlx_ptr, data->mlx.win_ptr, x, y, 0xf2f2f2);
			
			++y;
		}
		if (ray.draw_end < 0)
			ray.draw_end  = data->map.res_h;
		
		y = ray.draw_end;
		while (y < data->map.res_h)
		{

			set_pixel_color(x, y, data->map.floor_color, data);
			set_pixel_color(x, data->map.res_h - y - 1, data->map.ceiling_color, data);
			
			// mlx_pixel_put(data->mlx.mlx_ptr, data->mlx.win_ptr, x, y, 0x00b111);
			// mlx_pixel_put(data->mlx.mlx_ptr, data->mlx.win_ptr, x, data->cam.screen_h - y - 1, 0x54eae5);
			
			++y;
		}

		++x;
	}
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.win_ptr, data->buffer.img_ptr, 0, 0);
	return (0);
}