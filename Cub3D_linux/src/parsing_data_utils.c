/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_data_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 12:33:15 by user42            #+#    #+#             */
/*   Updated: 2020/09/15 14:13:39 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_r_data(t_data *data)
{
	int	max_width;
	int	max_height;

	mlx_get_screen_size(data->mlx.mlx_ptr, &max_width, &max_height);
	if (data->map.width > max_width)
		data->map.width = max_width;
	else if (data->map.width < MIN_WIDTH)
		data->map.width = MIN_WIDTH;
	if (data->map.height > max_height)
		data->map.height = max_height;
	else if (data->map.height < MIN_WIDTH)
		data->map.height = MIN_WIDTH;
}

void	data_switch_color(t_data *data, char **line_split, int *error)
{
	if (ft_strncmp(line_split[0], "C", ft_strlen(line_split[0])) == 0)
	{
		if (data->map.ceiling_color == -1)
		{
			data->map.ceiling_color = 0;
			*error = get_color_data(line_split, &data->map.ceiling_color);
		}
		else
			*error = put_error("duplicate ceiling color data", -1);
	}
	if (ft_strncmp(line_split[0], "F", ft_strlen(line_split[0])) == 0)
	{
		if (data->map.floor_color == -1)
		{
			data->map.floor_color = 0;
			*error = get_color_data(line_split, &data->map.floor_color);
		}
		else
			*error = put_error("duplicate floor color data", -1);
	}
}

int		data_switch(t_data *data, char **line_split)
{
	int		error;

	error = 0;
	if (ft_strlen(line_split[0]) == 1)
	{
		if (ft_strncmp(line_split[0], "R", 1) == 0)
			error = get_r_data(data, line_split);
		else if (ft_strncmp(line_split[0], "S", 1) == 0)
			error = get_img_data(data, line_split,
			&(data->map.texture_sprite));
		else if (ft_strncmp(line_split[0], "F", 1) == 0)
			data_switch_color(data, line_split, &error);
		else if (ft_strncmp(line_split[0], "C", 1) == 0)
			data_switch_color(data, line_split, &error);
		else
			error = put_error("unknown or missing data", -1);
	}
	else if (ft_strlen(line_split[0]) == 2)
		error = wall_texture_switch(data, line_split);
	else
		error = put_error("unknown or missing data", -1);
	free_table(line_split);
	return (error);
}

int		wall_texture_switch(t_data *data, char **line_split)
{
	int error;

	error = 1;
	if (ft_strncmp(line_split[0], "NO", 2) == 0)
		error = get_img_data(data, line_split, &(data->map.texture_no));
	else if (ft_strncmp(line_split[0], "SO", 2) == 0)
		error = get_img_data(data, line_split, &(data->map.texture_so));
	else if (ft_strncmp(line_split[0], "EA", 2) == 0)
		error = get_img_data(data, line_split, &(data->map.texture_ea));
	else if (ft_strncmp(line_split[0], "WE", 2) == 0)
		error = get_img_data(data, line_split, &(data->map.texture_we));
	else
		error = put_error("unknown or missing data", -1);
	return (error);
}
