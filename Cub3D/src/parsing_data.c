/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 12:31:19 by user42            #+#    #+#             */
/*   Updated: 2020/05/18 14:46:12 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_r_data(t_data *data, char **line_split)
{
	int	i;
	int j;
	int	max_width;
	int max_height;

	if (table_len(line_split) != 3)
		return (put_error("wrong window resolution data", -1));
	if (data->map.height != -1 || data->map.height != -1)
		return (put_error("duplicate window resolution data", -1));
	mlx_get_screen_size(data->mlx.mlx_ptr, &max_width, &max_height);
	i = 0;
	while (line_split[++i])
	{
		j = 0;
		while (line_split[i][j])
			if (!ft_isdigit(line_split[i][j++]))
				return (put_error("wrong window resolution data", -1));
		if (i == 1 && (data->map.width = ft_atoi(line_split[1])) > max_width)
			data->map.width = max_width;
		else if ((data->map.height = ft_atoi(line_split[2])) > max_height)
			data->map.height = max_height;
	}
	return (0);
}

int	get_img_data(t_data *data, char **line_split, t_img **img)
{
	if (*img != 0)
		return (put_error("duplicate texture data", -1));
	if (table_len(line_split) != 2)
		return (put_error("wrong texture data", -1));
	if ((*img = malloc(sizeof(t_img))) == 0)
		return (put_error("failed to allocate memory for texture", -1));
	if (((*img)->img_ptr = mlx_xpm_file_to_image(data->mlx.mlx_ptr,
	line_split[1], &((*img)->width), &((*img)->height))) == 0)
	{
		free(*img);
		return (put_error("failed to load textures", -1));
	}
	if (((*img)->data_address = mlx_get_data_addr((*img)->img_ptr,
	&((*img)->bpp), &((*img)->line_size), &((*img)->endian))) == 0)
	{
		destroy_image(data->mlx.mlx_ptr, *img);
		return (put_error("failed to get texture data addresse", -1));
	}
	return (0);
}

int	get_color_data(char **line_split, int *rgb_value)
{
	char	**rbg_split;
	int		i;
	int		j;
	int		error;

	error = 0;
	if (table_len(line_split) != 2)
		return (put_error("wrong ceilling/floor color data", -1));
	if ((rbg_split = ft_split(line_split[1], ',')) == 0 ||
	table_len(rbg_split) != 3)
		return (put_error("failed to get rbg values for ceilling/floor", -1));
	i = -1;
	while (error == 0 && rbg_split[++i])
	{
		j = 0;
		while (error == 0 && rbg_split[i][j])
			if (!ft_isdigit(rbg_split[1][j++]))
				error = put_error("wrong ceilling/floor rgb data", -1);
		j = ft_atoi(rbg_split[i]);
		if (j < 0 || j > 255)
			return (put_error("RGB value must be [0-255]", -1));
		*rgb_value += pow(256, 2 - i) * j;
	}
	free_table(rbg_split);
	return (error);
}

int	get_data(t_data *data, int file_descriptor)
{
	char	*line;
	int		gnl_return;
	char	**line_split;
	int		error;

	error = 0;
	gnl_return = 1;
	while (error == 0 && gnl_return && check_data(data) == -1)
	{
		gnl_return = get_next_line(file_descriptor, &line);
		if (gnl_return == -1)
			error = put_error("error while reading map file", -1);
		else if (ft_strlen(line))
		{
			if ((line_split = ft_split(line, ' ')) == 0)
				error = put_error("malloc error while parsing file", -1);
			if (error == 0)
				error = data_switch(data, line_split);
		}
		free(line);
	}
	return (error);
}
