/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_window.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 15:26:56 by user42            #+#    #+#             */
/*   Updated: 2020/06/16 13:10:21 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		on_exit_hook(t_data *data)
{
	free_exit(data, 0);
	return (0);
}

int		on_loop(t_data *data)
{
	if (data->cam.forward == true || data->cam.backward == true ||
	data->cam.right == true || data->cam.left == true ||
	data->cam.rot_right == true || data->cam.rot_left == true)
	{
		move(data);
		draw(data);
		mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.win_ptr,
		data->image.img_ptr, 0, 0);
	}
	return (0);
}

int		on_update(t_data *data)
{
	draw(data);
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.win_ptr,
	data->image.img_ptr, 0, 0);
	return (0);
}

void	setup_window(t_data *data)
{
	if ((data->wall_dist = malloc(data->map.width * sizeof(double))) == 0)
		free_exit(data, put_error("memory alloc failed in setup_window", -1));
	draw(data);
	if (data->save)
	{
		if (img_to_bmp(&data->image) == -1)
			free_exit(data, put_error("img to bmp error", -1));
		free_exit(data, 0);
	}
	if ((data->mlx.win_ptr = mlx_new_window(data->mlx.mlx_ptr,
	data->map.width, data->map.height, "Cub3D")) == 0)
		free_exit(data, put_error("mlx_new_window failed", -1));
	mlx_hook(data->mlx.win_ptr, DestroyNotify,
	StructureNotifyMask, &on_exit_hook, data);
	mlx_expose_hook(data->mlx.win_ptr, &on_update, data);
	mlx_hook(data->mlx.win_ptr, KeyPress, KeyPressMask, &on_key_press, data);
	mlx_hook(data->mlx.win_ptr, KeyRelease,
	KeyReleaseMask, &on_key_release, data);
	mlx_loop_hook(data->mlx.mlx_ptr, &on_loop, data);
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.win_ptr,
	data->image.img_ptr, 0, 0);
}
