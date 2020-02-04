/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prebeca <prebeca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 23:52:12 by prebeca           #+#    #+#             */
/*   Updated: 2020/02/04 05:30:25 by prebeca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int tab_len(char **tab)
{
    int i;

    i = 0;
    while (tab[i])
        ++i;
    return (i);
}

static int get_res(t_data *data, char **data_line)
{
    if (tab_len(data_line) != 3)
        return (-1);
	data->map.res_w = ft_atoi(data_line[1]);
	data->map.res_h = ft_atoi(data_line[2]);
    return (0);
}

static t_img *get_img(t_data *data, char **data_line)
{
    t_img *t;
    char *join;

	if ((t = malloc(sizeof(t_img))) == 0)
		return (0);
    if ((t->img_ptr = mlx_xpm_file_to_image(data->mlx.mlx_ptr, data_line[1], &t->res_w, &t->res_h)) == 0)
        return (0);
	t->buffer = mlx_get_data_addr(t->img_ptr, &t->bpp, &t->line_size, &t->endian);
    return (t);
}

static int get_color(char **data_line)
{
    char **color_split;
    int rgb;
    if (tab_len(data_line) != 2)
        return (-1);
    color_split = ft_split(data_line[1], ',');
    if (tab_len(color_split) != 3)
        return (-1);
    rgb = 0;
    rgb += ft_atoi(color_split[0]) << 16;
    rgb += ft_atoi(color_split[1]) << 8;
    rgb += ft_atoi(color_split[2]);
    free(color_split);
    return (rgb);
}

static void get_start_pos(char orient, int x, int y, t_data *data)
{
    data->player.pos_x = (double)x;
    data->player.pos_y = (double)y;
    if (orient == 'N')
    {
        data->player.dir_x = (double)-1;
        data->player.dir_y = (double)0;
        data->cam.screen_dir_x = (double)0;
        data->cam.screen_dir_y = (double)1;
    }
}

static int get_map(t_data *data, t_list *file_lines)
{
    char **split;
    int i;
    int j;
    int len;

    len = 0;
    if (!(data->map.map = malloc((ft_lstsize(file_lines)) * sizeof(int*))))
        return (-1);
    i = 0;
    while (file_lines)
    {
        if (!(split = ft_split(file_lines->content, ' ')))
            return (-1);
        len = tab_len(split);
        if (!(data->map.map[i] = malloc(len * sizeof(int))))
            return (-1);
        j = 0;
        while (j < len)
        {
            if (split[j][0] == 'N' || split[j][0] == 'S' || split[j][0] == 'E' || split[j][0] == 'W')
            {
                get_start_pos(split[j][0], i, j, data);
                data->map.map[i][j] = 0;
            }
            else
                data->map.map[i][j] = ft_atoi(split[j]);
            ++j;
        }
        ++i;
        file_lines = file_lines->next;
    }
    return (0);
}

static int data_switch(t_data *data, char **data_line)
{
	if (ft_strncmp(data_line[0], "R", ft_strlen("R")) == 0)
		return (get_res(data, data_line));
    else if (ft_strncmp(data_line[0], "NO", ft_strlen("NO")) == 0)
        data->map.texture_no = get_img(data, data_line);
    else if (ft_strncmp(data_line[0], "SO", ft_strlen("SO")) == 0)
        data->map.texture_so = get_img(data, data_line);
    else if (ft_strncmp(data_line[0], "EA", ft_strlen("EA")) == 0)
        data->map.texture_ea = get_img(data, data_line);
    else if (ft_strncmp(data_line[0], "WE", ft_strlen("WE")) == 0)
        data->map.texture_we = get_img(data, data_line);
    else if (ft_strncmp(data_line[0], "S", ft_strlen("S")) == 0)
        data->map.sprite = get_img(data, data_line);
    else if (ft_strncmp(data_line[0], "F", ft_strlen("F")) == 0)
        data->map.floor_color = get_color(data_line);
    else if (ft_strncmp(data_line[0], "C", ft_strlen("C")) == 0)
        data->map.ceiling_color = get_color(data_line);
	else 
		return (-1);
    return (0);
}

static int parse_data(t_data *data, t_list *line)
{
	char **split;
	
	while(line)
	{
		if ((split = ft_split(line->content, ' ')) == 0)
			return (-1);
		if (tab_len(split) > 1)
        {
			if (data_switch(data, split) == -1)
			{
				if (ft_strncmp(split[0], "1", ft_strlen("1")) == 0)
				{
					if (get_map(data, line) == -1)
						return (-1);
					else
						return (0);
				}
				else
					return (-1);
			}
        }
		line = line->next;
	}
	return (0);
}

static int get_file_data(char *path, t_list **file_lines)
{
    char *line;
    int ret;
    int fd;
    t_list *cur_line;

    if ((fd = open(path, O_RDONLY)) == -1)
        return (printerr("file error"));
    line = 0;
    ret = 1;
    while (ret > 0)
    {
        if ((ret = get_next_line(fd, &line)) == -1)
            return (-1);
        if ((cur_line = ft_lstnew(line)) == 0)
        {
            ft_lstclear(file_lines, &free);
            return (-1);
        }
        ft_lstadd_back(file_lines, cur_line);
    }
    close(fd);
    return (0);
}

int map_parser(char *path, t_data *data)
{
    t_list *file_lines;

    if (get_file_data(path, &file_lines) == -1)
        return (-1);
    if (parse_data(data, file_lines) == -1)
        return (-1);
	ft_lstclear(&file_lines, &free);
    return (0);
}