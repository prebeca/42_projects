/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prebeca <prebeca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 00:46:36 by prebeca           #+#    #+#             */
/*   Updated: 2020/01/29 17:09:33 by prebeca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void init_ray(int x, t_ray *ray, t_data *data)
{
	ray->center_x = (2 * x / data->cam.screen_w) - 1;
	ray->x = data->cam.x;
	ray->y = data->cam.y;
	ray->dir_x = data->cam.dir_x + data->cam.screen_dir_x * ray->center_x;
	ray->dir_y = data->cam.dir_y + data->cam.screen_dir_y * ray->center_x;
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
	data->img.buffer[y * data->img.line_size + x * data->img.bpp / 8] = color_c[0];
	data->img.buffer[y * data->img.line_size + x * data->img.bpp / 8 + 1] = color_c[1];
	data->img.buffer[y * data->img.line_size + x * data->img.bpp / 8 + 2] = color_c[2];
}

void    raycast(t_data *data)
{
	
	int x;
	int y;
	double wallx;
	int textx;
	int texty;
	int textsize = 128;

	x = 0;
	data->img.img_ptr = mlx_new_image(data->mlx.mlx_ptr, data->cam.screen_w, data->cam.screen_h);
	data->img.bpp = 3;
	data->img.line_size = data->img.bpp * data->cam.screen_w;
	int endian = 0;
	data->img.buffer = mlx_get_data_addr(data->img.img_ptr, &data->img.bpp, &data->img.line_size, &endian);
	while(x < data->cam.screen_w)
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
		ray.wall_h = fabs(data->cam.screen_h / ray.len);
		wallx -= floor(wallx);
		textx = wallx * 128;
		if ((ray.face == 0 || ray.face == 1) && ray.dir_x > 0) {
			textx = textsize - textx - 1;
		}
		if ((ray.face == 2 || ray.face == 3) && ray.dir_y < 0) {
			textx = textsize - textx - 1;
		}

		//
		ray.draw_start = -ray.wall_h / 2 + data->cam.screen_h / 2;
		ray.draw_end = ray.wall_h / 2 + data->cam.screen_h / 2;

		//
		if (ray.draw_start < 0)
			ray.draw_start = 0;
		if (ray.draw_end >= data->cam.screen_h)
			ray.draw_end = data->cam.screen_h - 1;
		
		//

		//
		y = ray.draw_start;
		while (y < ray.draw_end)
		{
			
			// texty = (y * 2 - data->cam.screen_h + ray.wall_h) * (128 / 2) / ray.wall_h;
			// int rgb;
			// unsigned char *rgb_char;
			// rgb_char = (unsigned char*)&rgb;
			// int bpp = 3;
			// int endian = 0;
			// rgb_char[0] = mlx_get_data_addr(data->map.texture_no, &bpp, &textsize, &endian)[texty * textsize + textx * bpp / 8];
			// rgb_char[1] = mlx_get_data_addr(data->map.texture_no, &bpp, &textsize, &endian)[texty * textsize + textx * bpp / 8 + 1];
			// rgb_char[2] = mlx_get_data_addr(data->map.texture_no, &bpp, &textsize, &endian)[texty * textsize + textx * bpp / 8 + 2];
			
			// set_pixel_color(x, y, rgb, data);

			if (ray.face == 0)
				set_pixel_color( x, y, 0xff0000, data);
			else if (ray.face == 1)
				set_pixel_color( x, y, 0x00ff00, data);
			else if (ray.face == 2)
				set_pixel_color( x, y, 0x0000ff, data);
			else
				set_pixel_color( x, y, 0x000000, data);
			
			// if (ray.face == 1)
			// 	mlx_pixel_put(data->mlx.mlx_ptr, data->mlx.win_ptr, x, y, 0xcccccc);
			// else
			// 	mlx_pixel_put(data->mlx.mlx_ptr, data->mlx.win_ptr, x, y, 0xf2f2f2);
			
			++y;
		}
		if (ray.draw_end < 0)
			ray.draw_end  = data->cam.screen_h;
		
		y = ray.draw_end;
		while (y < data->cam.screen_h)
		{

			set_pixel_color(x, y, data->map.floor_color, data);
			set_pixel_color(x, data->cam.screen_h - y - 1, data->map.ceiling_color, data);
			
			// mlx_pixel_put(data->mlx.mlx_ptr, data->mlx.win_ptr, x, y, 0x00b111);
			// mlx_pixel_put(data->mlx.mlx_ptr, data->mlx.win_ptr, x, data->cam.screen_h - y - 1, 0x54eae5);
			
			++y;
		}

		++x;
	}
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.win_ptr, data->img.img_ptr, 0, 0);
}