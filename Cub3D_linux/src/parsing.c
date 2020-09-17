/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 00:30:54 by user42            #+#    #+#             */
/*   Updated: 2020/09/15 13:39:10 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_file(t_data *data)
{
	int		file_descriptor;
	int		error;

	error = 0;
	if ((file_descriptor = open(data->map.map_path, O_RDONLY)) == -1)
		free_exit(data, put_error(strerror(errno), -1));
	error = get_data(data, file_descriptor);
	if (error == 0 && check_data(data) == -1)
		error = put_error("missing data", -1);
	if (error == 0)
		error = get_map(data, file_descriptor);
	close(file_descriptor);
	if (error == -1)
		free_exit(data, -1);
}

int		check_data(t_data *data)
{
	if (data->map.ceiling_color == -1 || data->map.floor_color == -1)
		return (-1);
	if (data->map.width == -1 || data->map.height == -1)
		return (-1);
	if (data->map.texture_no == 0 || data->map.texture_so == 0 ||
	data->map.texture_ea == 0 || data->map.texture_we == 0 ||
	data->map.texture_sprite == 0)
		return (-1);
	return (0);
}
