/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 12:38:29 by user42            #+#    #+#             */
/*   Updated: 2020/09/03 10:54:19 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_cam_start(t_data *data, int x, int y)
{
	if (data->cam.x != 0 || data->cam.y != 0)
		return (put_error("duplicate start position", -1));
	data->cam.x = x + 0.51;
	data->cam.y = y + 0.51;
	if (data->map.tile_map[y][x] == 'N')
		set_cam_dir(data, 0, -1);
	else if (data->map.tile_map[y][x] == 'S')
		set_cam_dir(data, 0, 1);
	else if (data->map.tile_map[y][x] == 'E')
		set_cam_dir(data, 1, 0);
	else
		set_cam_dir(data, -1, 0);
	return (0);
}

int	get_sprite(t_data *data, int x, int y)
{
	t_point *sprite;

	if ((sprite = malloc(sizeof(t_point))) == 0)
		return (put_error("failed to allocate memory for sprite", -1));
	sprite->x = x + 0.5;
	sprite->y = y + 0.5;
	ft_lstadd_back(&data->map.sprite_list, ft_lstnew(sprite));
	return (0);
}

int	get_map_data(t_data *data, t_list *map_lines)
{
	int		tm_width;
	int		tm_height;
	int		i;

	if (alloc_map(data, map_lines, &tm_width, &tm_height) == -1)
		return (-1);
	ft_memset(data->map.tile_map[0], ' ', tm_width - 1);
	ft_memset(data->map.tile_map[tm_height - 2], ' ', tm_width - 1);
	i = 0;
	while (map_lines && ++i)
	{
		ft_memset(data->map.tile_map[i], ' ', tm_width - 1);
		ft_memcpy(data->map.tile_map[i] + 1, map_lines->content,
		ft_strlen(map_lines->content));
		map_lines = map_lines->next;
	}
	if (check_map(data) == -1)
		return (-1);
	if (data->cam.x == 0 || data->cam.y == 0)
		return (put_error("no start position for player", -1));
	return (0);
}

int	get_map(t_data *data, int file_descriptor)
{
	char	*line;
	int		gnl_return;
	int		error;
	t_list	*map_lines;

	map_lines = 0;
	gnl_return = 1;
	if ((error = pass_empty_line(&line, file_descriptor)) == -1)
		return (-1);
	error = 0;
	while (error == 0 && gnl_return)
	{
		ft_lstadd_back(&map_lines, ft_lstnew(line));
		gnl_return = get_next_line(file_descriptor, &line);
		if (ft_strlen(line) == 0 && gnl_return)
			error = put_error("empty line in map", -1);
		if (gnl_return == -1)
			error = put_error("error while reading map file", -1);
	}
	ft_lstadd_back(&map_lines, ft_lstnew(line));
	if (error == 0)
		error = get_map_data(data, map_lines);
	ft_lstclear(&map_lines, &free);
	return (error);
}
