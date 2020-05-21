/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_window_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 12:00:56 by user42            #+#    #+#             */
/*   Updated: 2020/05/21 12:01:19 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		on_key_press(int keycode, t_data *data)
{
	if (keycode == ESCAPE)
		free_exit(data, 0);
	else if (keycode == FORWARD)
		data->cam.forward = true;
	else if (keycode == BACKWARD)
		data->cam.backward = true;
	else if (keycode == RIGHT)
		data->cam.right = true;
	else if (keycode == LEFT)
		data->cam.left = true;
	else if (keycode == ROT_RIGHT)
		data->cam.rot_right = true;
	else if (keycode == ROT_LEFT)
		data->cam.rot_left = true;
	return (0);
}

int		on_key_release(int keycode, t_data *data)
{
	if (keycode == FORWARD)
		data->cam.forward = false;
	else if (keycode == BACKWARD)
		data->cam.backward = false;
	else if (keycode == RIGHT)
		data->cam.right = false;
	else if (keycode == LEFT)
		data->cam.left = false;
	else if (keycode == ROT_RIGHT)
		data->cam.rot_right = false;
	else if (keycode == ROT_LEFT)
		data->cam.rot_left = false;
	return (0);
}
