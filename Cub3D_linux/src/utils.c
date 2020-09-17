/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 18:58:26 by user42            #+#    #+#             */
/*   Updated: 2020/05/18 13:26:49 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		put_error(char *error_msg, int return_value)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	ft_putendl_fd(error_msg, STDERR_FILENO);
	return (return_value);
}

int		ft_ischarset(char c, char *charset)
{
	int i;

	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}

char	**free_table(char **table)
{
	int i;

	if (table == 0)
		return (0);
	i = -1;
	while (table[++i])
		free(table[i]);
	free(table);
	return (0);
}

int		table_len(char **table)
{
	int i;

	if (table == 0)
		return (0);
	i = 0;
	while (table[i])
		++i;
	return (i);
}

void	set_cam_dir(t_data *data, double dx, double dy)
{
	data->cam.dx = dx;
	data->cam.dy = dy;
	data->cam.px = dy * -1;
	data->cam.py = dx;
}
