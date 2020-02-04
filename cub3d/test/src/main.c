/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prebeca <prebeca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 22:59:08 by prebeca           #+#    #+#             */
/*   Updated: 2020/02/04 05:20:52 by prebeca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_data data;
	
	if (ac > 3 || ac < 2)
		return (printerr("wrong number of arguments"));
	if ((data.mlx.mlx_ptr = mlx_init()) == 0)
		return (printerr("mlx init failed"));
	if (map_parser(av[1], &data) == -1)
		return (-1);
	if (check_data(&data) == -1)
		return (-1);
	if (init_data(&data) == -1)
		return (-1);
	raycast(&data);
	if (mlx_loop(data.mlx.mlx_ptr) == -1)
		return (-1);
	return (0);
}