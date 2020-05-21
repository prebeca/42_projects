/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_data_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 12:33:15 by user42            #+#    #+#             */
/*   Updated: 2020/05/18 13:34:43 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		check_data(t_data *data)
{
	if (data->map.ceiling_color == -1 || data->map.ceiling_color == -1)
		return (-1);
	if (data->map.width == -1 || data->map.height == -1)
		return (-1);
	if (data->map.texture_no == 0 || data->map.texture_so == 0 ||
	data->map.texture_ea == 0 || data->map.texture_we == 0 ||
	data->map.texture_sprite == 0)
		return (-1);
	return (0);
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
	if (ft_strncmp(line_split[0], "R", ft_strlen(line_split[0])) == 0)
		error = get_r_data(data, line_split);
	else if (ft_strncmp(line_split[0], "S", ft_strlen(line_split[0])) == 0)
		error = get_img_data(data, line_split, &(data->map.texture_sprite));
	else if (ft_strncmp(line_split[0], "NO", ft_strlen(line_split[0])) == 0)
		error = get_img_data(data, line_split, &(data->map.texture_no));
	else if (ft_strncmp(line_split[0], "SO", ft_strlen(line_split[0])) == 0)
		error = get_img_data(data, line_split, &(data->map.texture_so));
	else if (ft_strncmp(line_split[0], "EA", ft_strlen(line_split[0])) == 0)
		error = get_img_data(data, line_split, &(data->map.texture_ea));
	else if (ft_strncmp(line_split[0], "WE", ft_strlen(line_split[0])) == 0)
		error = get_img_data(data, line_split, &(data->map.texture_we));
	else if (ft_strncmp(line_split[0], "F", ft_strlen(line_split[0])) == 0)
		data_switch_color(data, line_split, &error);
	else if (ft_strncmp(line_split[0], "C", ft_strlen(line_split[0])) == 0)
		data_switch_color(data, line_split, &error);
	else
		error = put_error("unknown or missing data", -1);
	free_table(line_split);
	return (error);
}
