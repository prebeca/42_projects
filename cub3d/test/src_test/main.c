/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prebeca <prebeca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/29 21:54:21 by prebeca           #+#    #+#             */
/*   Updated: 2020/01/14 23:21:13 by prebeca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "map.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct	s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	int		plan_x;
	int		plan_y;
	t_map	*map;
}				t_data;

typedef struct s_ray
{
	double camx;
	double posx;
	double posy;
	double dirx;
	double diry;
}	t_ray;

void render(t_data *data)
{
	int x = 0;
	int y = 0;
	t_ray ray;

	while(x < data->map->res_x)
	{
		ray.camx = (2*x/data->map->res_x)-1;
		ray.posx = data->pos_x;
		ray.posy = data->pos_y;
		ray.dirx = data->dir_x + data->plan_x * ray.camx;
		ray.diry = data->dir_y + data->plan_y * ray.camx;
		int mapx = ray.posx;
		int mapy = ray.posy;
		double distx = 0;
		double disty = 0;
		double deltadistx = sqrt(1+(ray.diry*ray.diry)/(ray.dirx*ray.dirx));
		double deltadisty = sqrt(1+(ray.dirx*ray.dirx)/(ray.diry*ray.diry));
		int stepx = 0;
		int stepy = 0;
		int hit = 0;
		int side;
		double perpwalldist = 0;

		if (ray.dirx<0)
		{
			stepx=-1;
			distx = (ray.posx - mapx) * deltadistx;
		} else
			{
				stepx = 1;
				distx = (mapx + 1.0 - ray.posx) * deltadistx;
			}
		if (ray.diry < 0){
			stepy = -1;
			disty = (ray.posy - mapy) * deltadisty;
		} else
		{
			stepy = 1;
			disty = (mapy + 1.0 - ray.posy) * deltadisty;
		}
		
		while (hit == 0)
		{ 
			if (distx<disty) {
				distx += deltadistx;
				mapx += stepx;
				side = 0;
			} else {
				disty += deltadisty;
				mapy += stepy;
				side = 1;
			}
			if ((data->map->map[(int)mapx][(int)mapy]) > 0) {
				hit = 1;
			}
		}
		if (side == 0)
		{
			perpwalldist = fabs((mapx-ray.posx+(1-stepx)/2)/ray.dirx);
		}
		else
		{
			perpwalldist = fabs((mapy-ray.posy+(1-stepy)/2)/ray.diry);
		}
		//Calcule la hauteur de la ligne à tracer
		int hauteurLigne = fabs(data->map->res_y / perpwalldist);
		
		//Calcule les pixels max haut et max bas de la colonne à tracer
		int drawStart = -hauteurLigne/2+data->map->res_y/2;
		int drawEnd = hauteurLigne/2+data->map->res_y/2;
		
		// limite les zones de tracé à l'écran uniquement
		if (drawStart < 0)
		{
			drawStart = 0;
		}
		if (drawEnd >= data->map->res_y)
		{
			drawEnd = data->map->res_y-1;
		}
		// tracer la colonne
		y=drawStart;
		
		while (y < drawEnd)
		{
			if (side == 1) {
				mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y, 0xcccccc);
			}
			else
				mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y, 0xf2f2f2);
			y++;// incrémente la position Y du prochain pixel à tracer
		}
		// si la fin du mur est < 0 alors on la replace en bas
		if (drawEnd < 0) {
			drawEnd = data->map->res_y;
		}
		
		//trace le sol de la fin du mur au bas de l'écran
		y=drawEnd;
		while (y < data->map->res_y) {
		
			mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y, 0x006666);// trace le pixel du sol
			mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, data->map->res_y-y-1, 0xcc0000);
			++y;
		}
		++x;
	}
}

int expose_hook(void *param)
{
	t_data *data;

	printf("expose\n");
	data = param;
	return (1);
}

int key_hook(int keycode, void *param)
{
	t_data *data;
	double oldDirX;
	double oldPlaneX;

	printf("keycode = %d\n", keycode);
	data = param;
	if (keycode == 53)
		exit(1);
	if (keycode == 126)
	{
		if (data->map->map[(int)(data->pos_x + data->dir_x * 0.2)][(int)(data->pos_y)] == 0) {
			data->pos_x += data->dir_x * 0.2;// on avance sur X
		}
		if (data->map->map[(int)(data->pos_x)][(int)(data->pos_y + data->dir_y * 0.2)] == 0) {
			data->pos_y += data->dir_y * 0.2;// on avance sur Y
		}
	}
	if (keycode == 125)
	{
		if (data->map->map[(int)(data->pos_x - data->dir_x * 0.2)][(int)(data->pos_y)] == 0) {
			data->pos_x -= data->dir_x * 0.2;
		}
		if (data->map->map[(int)(data->pos_x)][(int)(data->pos_y - data->dir_y * 0.2)] == 0) {
			data->pos_y -= data->dir_y * 0.2;
		}
	}
	if (keycode == 124)
	{
		oldDirX = data->dir_x;
		data->dir_x = data->dir_x * cos(-0.2) - data->dir_y * sin(-0.2);
		data->dir_y = oldDirX * sin(-0.2) + data->dir_y * cos(-0.2);
		oldPlaneX = data->plan_x;
		data->plan_x = data->plan_x * cos(-0.2) - data->plan_y * sin(-0.2);
		data->plan_y = oldPlaneX * sin(-0.2) + data->plan_y * cos(-0.2);
 
	}
	if (keycode == 123)
	{
		oldDirX = data->dir_x;
		data->dir_x = data->dir_x * cos(0.2) - data->dir_y * sin(0.2);
		data->dir_y = oldDirX * sin(0.2) + data->dir_y * cos(0.2);
		oldPlaneX = data->plan_x;
		data->plan_x = data->plan_x * cos(0.2) - data->plan_y * sin(0.2);
		data->plan_y = oldPlaneX * sin(0.2) + data->plan_y * cos(0.2);
	}

	render(data);
	return (1);
}

int mouse_hook(int button, int x, int y, void *param)
{
	t_data *data;

	printf("clic\n");
	data = param;
	return (1);
}

int loop_hook(void *param)
{
	//render(param);
	//printf("render ok\n");
	return (1);
}

int	main(int ac, char **av)
{
	t_data	data;
	t_map	*map;
	int i, j;

	data.dir_x = -1;
	data.dir_y = 0;
	data.plan_x = 0;
	data.plan_y = 1;

	i  = j = 0;
	(void)ac;
	map = get_map(av[1]);
	i = 0;
	while(i < map->map_y_len)
	{
		j = 0;
		while(j < map->map_x_len)
		{
			printf("%d", map->map[i][j]);
			++j;
		}
		printf("\n");
		++i;
	}

	if ((data.mlx_ptr = mlx_init()) == 0)
		return (1);
	if ((data.win_ptr = mlx_new_window(data.mlx_ptr, map->res_x, map->res_y, "mlx test")) == 0)
		return (1);
	data.pos_x = map->start_pos.pos_x;
	data.pos_y = map->start_pos.pos_y;
	data.map = map;
	render(&data);
	mlx_expose_hook(data.win_ptr, &expose_hook, &data);
	mlx_key_hook(data.win_ptr, &key_hook, &data);
	mlx_mouse_hook(data.win_ptr, &mouse_hook, &data);
	mlx_loop_hook(data.mlx_ptr, &loop_hook, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
