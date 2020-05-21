/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 19:36:51 by user42            #+#    #+#             */
/*   Updated: 2020/05/21 12:10:41 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_movement(t_data *data)
{
	data->cam.forward = false;
	data->cam.backward = false;
	data->cam.right = false;
	data->cam.left = false;
	data->cam.rot_right = false;
	data->cam.rot_left = false;
}

void	init_data(t_data *data)
{
	data->mlx.mlx_ptr = 0;
	data->mlx.win_ptr = 0;
	data->image.img_ptr = 0;
	data->cam.x = 0;
	data->cam.y = 0;
	data->cam.dx = 0;
	data->cam.dy = 0;
	init_movement(data);
	data->map.map_path = 0;
	data->map.tile_map = 0;
	data->map.width = -1;
	data->map.height = -1;
	data->map.texture_no = 0;
	data->map.texture_so = 0;
	data->map.texture_ea = 0;
	data->map.texture_we = 0;
	data->map.texture_sprite = 0;
	data->map.sprite_list = 0;
	data->map.ceiling_color = -1;
	data->map.floor_color = -1;
	data->save = false;
	data->wall_dist = 0;
}

void	destroy_image(void *mlx_ptr, t_img *img)
{
	if (img && mlx_ptr)
	{
		mlx_destroy_image(mlx_ptr, img->img_ptr);
		free(img);
	}
}

void	free_exit(t_data *data, int exit_value)
{
	if (data->mlx.win_ptr != 0)
		mlx_destroy_window(data->mlx.mlx_ptr, data->mlx.win_ptr);
	free(data->map.map_path);
	if (data->image.img_ptr)
		mlx_destroy_image(data->mlx.mlx_ptr, data->image.img_ptr);
	free_table(data->map.tile_map);
	ft_lstclear(&data->map.sprite_list, &free);
	if (data->wall_dist)
		free(data->wall_dist);
	destroy_image(data->mlx.mlx_ptr, data->map.texture_no);
	destroy_image(data->mlx.mlx_ptr, data->map.texture_so);
	destroy_image(data->mlx.mlx_ptr, data->map.texture_ea);
	destroy_image(data->mlx.mlx_ptr, data->map.texture_we);
	destroy_image(data->mlx.mlx_ptr, data->map.texture_sprite);
	exit(exit_value);
}

void	manage_arg(t_data *data, int argc, char **argv)
{
	char	**split_path;
	int		error;

	split_path = 0;
	error = 0;
	if ((data->map.map_path = ft_strdup(argv[1])) == 0)
		free_exit(data, put_error("malloc error while parsing map path", -1));
	if (error == 0 && (split_path = ft_split(data->map.map_path, '.')) == 0)
		error = put_error("malloc error while parsing map path", -1);
	if (error == 0 && ft_strncmp(split_path[table_len(split_path) - 1],
	MAP_EXTENSION, ft_strlen(split_path[table_len(split_path) - 1])) != 0)
		error = put_error("unknown map format", -1);
	free_table(split_path);
	if (error == -1)
		free_exit(data, error);
	if (argc == 3)
	{
		if (ft_strncmp(argv[2], ARG_SAVE, ft_strlen(argv[2])) != 0)
			free_exit(data, put_error("unknown option", -1));
		data->save = true;
	}
}
