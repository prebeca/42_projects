/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 00:30:54 by user42            #+#    #+#             */
/*   Updated: 2020/05/16 16:21:40 by user42           ###   ########.fr       */
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
