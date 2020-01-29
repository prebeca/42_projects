/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prebeca <prebeca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 05:17:54 by prebeca           #+#    #+#             */
/*   Updated: 2020/01/08 06:38:50 by prebeca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

int	search_start_pos(t_map *map, int y_pos, char **line)
{
	int i;

	i= -1;
	while(line[++i])
		if (line[i][0] == 'N' || line[i][0] == 'S' || line[i][0] == 'E' || line[i][0] == 'W')
		{
			map->start_pos.orient = line[i][0];
			return (i);
		}
	return (0);
}

int	*ft_map(char **tab, int length, int (*f)(const char*))
{
	int *res_tab;
	int i;

	i = -1;
	res_tab = 0;
	if (!(res_tab = malloc(length * sizeof(int))))
		return (0);
	while (++i < length)
		res_tab[i] = (*f)(tab[i]);
	return (res_tab);
}

int	get_split_len(char **split)
{
	int i;

	i = 0;
	while(split[i])
		++i;
	return (i);
}

int get_map_len(char *path)
{
	int fd;
	int size;
	char *line;

	if ((fd = open(path, O_RDONLY)) == -1)
		return (0);
	size = 1;
	while(get_next_line(fd, &line) > 0)
	{
		free(line);
		++size;
	}
	close(fd);
	return (size - 10);
}

t_map	*get_map(char *path)
{
	int fd;
	char *line;
	t_map *map;
	char **split;
	int i;

	if (!(map = malloc(sizeof(t_map))))
		return (0);
	if ((fd = open(path, O_RDONLY)) == -1)
		return (0);
	
	//get res
	if (get_next_line(fd, &line) <= 0)
		return (0);
	split = ft_split(line, ' ');
	map->res_x = ft_atoi(split[1]);
	map->res_y = ft_atoi(split[2]);
	//get texture path
	//no
	if (get_next_line(fd, &line) <= 0)
		return (0);
	split = ft_split(line, ' ');
	map->texture_no = split[1];
	//so
	if (get_next_line(fd, &line) <= 0)
		return (0);
	split = ft_split(line, ' ');
	map->texture_so = split[1];
	//we
	if (get_next_line(fd, &line) <= 0)
		return (0);
	split = ft_split(line, ' ');
	map->texture_we = split[1];
	//ea
	if (get_next_line(fd, &line) <= 0)
		return (0);
	split = ft_split(line, ' ');
	map->texture_ea = split[1];
	//newline
	if (get_next_line(fd, &line) <= 0)
		return (0);
	//sprite texture
		//so
	if (get_next_line(fd, &line) <= 0)
		return (0);
	split = ft_split(line, ' ');
	map->sprite = split[1];
	//floor
	if (get_next_line(fd, &line) <= 0)
		return (0);
	split = ft_split(line, ' ');
	split = ft_split(split[1], ',');
	map->floor.red = ft_atoi(split[0]);
	map->floor.green = ft_atoi(split[1]);
	map->floor.blue = ft_atoi(split[2]);
	//ceiling
	if (get_next_line(fd, &line) <= 0)
		return (0);
	split = ft_split(line, ' ');
	split = ft_split(split[1], ',');
	map->ceiling.red = ft_atoi(split[0]);
	map->ceiling.green = ft_atoi(split[1]);
	map->ceiling.blue = ft_atoi(split[2]);
	//newline
	if (get_next_line(fd, &line) <= 0)
		return (0);
	//map
	map->map_y_len = get_map_len(path);
	map->map = malloc(sizeof(int*) * map->map_y_len);
	i = 0;
	while (i < map->map_y_len)
	{
		if (get_next_line(fd, &line) < 0)
			return (0);
		split = ft_split(line,  ' ');
		if (map->map_x_len == 0)
			map->map_x_len = get_split_len(split);
		if (map->start_pos.pos_x == 0)
		{
			if ((map->start_pos.pos_x = search_start_pos(map, i, split)) > 0)
				map->start_pos.pos_y = i;
		}
		map->map[i] = ft_map(split, get_split_len(split), &ft_atoi);
		++i;
	}
	close(fd);
	return (map);
}
