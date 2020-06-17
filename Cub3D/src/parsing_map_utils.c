/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 12:39:56 by user42            #+#    #+#             */
/*   Updated: 2020/06/16 10:40:25 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_closed_map(t_data *data, int x, int y)
{
	if (data->map.tile_map[y - 1][x - 1] == ' ')
		return (put_error("map is not closed", -1));
	if (data->map.tile_map[y - 1][x] == ' ')
		return (put_error("map is not closed", -1));
	if (data->map.tile_map[y - 1][x + 1] == ' ')
		return (put_error("map is not closed", -1));
	if (data->map.tile_map[y][x - 1] == ' ')
		return (put_error("map is not closed", -1));
	if (data->map.tile_map[y][x + 1] == ' ')
		return (put_error("map is not closed", -1));
	if (data->map.tile_map[y + 1][x - 1] == ' ')
		return (put_error("map is not closed", -1));
	if (data->map.tile_map[y + 1][x] == ' ')
		return (put_error("map is not closed", -1));
	if (data->map.tile_map[y + 1][x + 1] == ' ')
		return (put_error("map is not closed", -1));
	return (0);
}

int	get_map_max_width(t_list *file_lines)
{
	int len;
	int max_len;

	max_len = 0;
	while (file_lines)
	{
		len = ft_strlen(file_lines->content);
		if (len > max_len)
			max_len = len;
		file_lines = file_lines->next;
	}
	return (max_len);
}

int	alloc_map(t_data *data, t_list *map_lines, int *tm_width, int *tm_height)
{
	int	i;

	*tm_width = get_map_max_width(map_lines) + 3;
	*tm_height = ft_lstsize(map_lines) + 3;
	if ((data->map.tile_map = malloc(*tm_height * sizeof(char*))) == 0)
	{
		free(data->map.tile_map);
		return (put_error("failed to allocate memory for map", -1));
	}
	i = 0;
	while (i < *tm_height - 1)
	{
		if ((data->map.tile_map[i] = malloc(*tm_width * sizeof(char))) == 0)
		{
			free_table(data->map.tile_map);
			return (put_error("failed to allocate memory for map", -1));
		}
		ft_memset(data->map.tile_map[i++], 0, *tm_width * sizeof(char));
	}
	data->map.tile_map[i] = 0;
	return (0);
}

int	pass_empty_line(char **line, int file_descriptor)
{
	int		gnl_return;
	int		error;

	*line = 0;
	error = 0;
	gnl_return = 1;
	while (error == 0 && gnl_return)
	{
		free(*line);
		gnl_return = get_next_line(file_descriptor, line);
		if (gnl_return == -1)
			error = put_error("error while reading map file", -1);
		if (ft_strlen(*line) != 0)
			error = 1;
	}
	return (error);
}

int	check_map(t_data *data)
{
	int y;
	int x;
	int error;
	int width;

	error = 0;
	width = ft_strlen(data->map.tile_map[0]);
	y = -1;
	while (error == 0 && data->map.tile_map[++y])
	{
		x = 0;
		while (error == 0 && ++x < width - 1 && data->map.tile_map[y][x])
		{
			if (ft_ischarset(data->map.tile_map[y][x], " 012NSEW") == false)
				return (put_error("map must contain only ' 012NSEW'", -1));
			if (ft_ischarset(data->map.tile_map[y][x], "NSEW") == true)
				error = get_cam_start(data, x, y);
			else if (data->map.tile_map[y][x] == '2')
				error = get_sprite(data, x, y);
			if (error == 0 && ft_ischarset(data->map.tile_map[y][x],
			"02NSEW") == true)
				error = check_closed_map(data, x, y);
		}
	}
	return (error);
}
