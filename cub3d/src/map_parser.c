/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prebeca <prebeca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 06:12:27 by prebeca           #+#    #+#             */
/*   Updated: 2020/01/29 16:57:16 by prebeca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line.h"
#include "libft.h"

int tab_len(char **tab)
{
    int i;

    i = 0;
    while (tab[i])
        ++i;
    return (i);
}

int get_color(t_data *data, char **data_line)
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
    if (ft_strncmp(data_line[0], "F", ft_strlen("F")) == 0)
        data->map.texture_no = ft_strdup(data_line[1]);
    else if (ft_strncmp(data_line[0], "C", ft_strlen("C")) == 0)
        data->map.texture_so = ft_strdup(data_line[1]);
    free(color_split);
    return (rgb);
}

int texture_switch(t_data *data, char **data_line)
{
    if (tab_len(data_line) != 2)
        return (-1);
    if (ft_strncmp(data_line[0], "NO", ft_strlen("NO")) == 0)
        data->map.texture_no = get_texture(data, data_line);
    else if (ft_strncmp(data_line[0], "SO", ft_strlen("SO")) == 0)
        data->map.texture_so = get_texture(data, data_line);
    else if (ft_strncmp(data_line[0], "EA", ft_strlen("EA")) == 0)
        data->map.texture_ea = get_texture(data, data_line);
    else if (ft_strncmp(data_line[0], "WE", ft_strlen("WE")) == 0)
        data->map.texture_we = get_texture(data, data_line);
    else if (ft_strncmp(data_line[0], "S", ft_strlen("S")) == 0)
        data->map.sprite = get_texture(data, data_line);
    else if (ft_strncmp(data_line[0], "F", ft_strlen("F")) == 0)
        data->map.floor_color = get_color(data, data_line);
    else if (ft_strncmp(data_line[0], "C", ft_strlen("C")) == 0)
        data->map.ceiling_color = get_color(data, data_line);
    return (0);
}



void *get_texture(t_data *data, char **data_line)
{
    void *img;
    int w;
    int h;

    h = 0;
    w = 0;
    img = mlx_xpm_file_to_image(data->mlx.mlx_ptr, data_line[1], &w, &h);
    return (img);
}

int get_res(t_data *data, char **data_line)
{
    if (tab_len(data_line) != 3)
        return (-1);
    data->map.w = ft_atoi(data_line[1]);
    data->map.h = ft_atoi(data_line[2]);
    data->cam.screen_h = data->map.h;
    data->cam.screen_w = data->map.w;
    return (0);
}

void get_start_pos(char c, int x, int y, t_data *data)
{
    data->cam.x = x;
    data->cam.y = y;
    if (c == 'N')
    {
        data->cam.dir_x = -1;
        data->cam.dir_y = 0;
        data->cam.screen_dir_x = 0;
        data->cam.screen_dir_y = 1;
    }
}

int get_map(t_data *data, t_list *file_lines)
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
            //printf("%d", data->map.map[i][j]);
            ++j;
        }
        ++i;
        file_lines = file_lines->next;
    }
    return (1);
}

int parse_data(t_data *data, t_flag **flags_table, t_list *file_lines)
{
    char **split;
    int i;

    split = 0;
	if (!file_lines)
		return (-1);
	while (file_lines)
	{
        if ((split = ft_split(file_lines->content, ' ')) == 0)
            return (-1);
        i = 0;
        if (tab_len(split) >= 1)
            while (i < NB_FLAGS)
            {
                if (ft_strncmp(split[0], flags_table[i]->flag, ft_strlen(flags_table[i]->flag)) == 0)
                {
                        if (flags_table[i]->fct(data, split) == -1)
                        {
                            printf("flag error : bad data (%s)\n", flags_table[i]->flag);
                            free(split);
                            return (-1);
                        }
                }
                else if (ft_strncmp(split[0], "1", ft_strlen("1")) == 0)
                {
                    free(split);
                    if ((get_map(data, file_lines)) == -1)
                        return (-1);
                    return (0);
                }
                ++i;
            }
        free(split);
		file_lines = file_lines->next;
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
        return (-1);
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
    t_flag *flag_table[NB_FLAGS + 1];

    if (init_flag_table(flag_table) == -1)
        return (-1);
    if (get_file_data(path, &file_lines) == -1)
        return (-1);
    if (parse_data(data, flag_table, file_lines) == -1)
        return (-1);
    return (1);
}