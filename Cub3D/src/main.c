/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 18:50:22 by user42            #+#    #+#             */
/*   Updated: 2020/05/20 23:30:20 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_data data;

	init_data(&data);
	if (argc < 2 || argc > 3)
		free_exit(&data, put_error("Usage : ./Cub3D <map_file.cub>", -1));
	manage_arg(&data, argc, argv);
	if ((data.mlx.mlx_ptr = mlx_init()) == 0)
		free_exit(&data, put_error("Minilibx failed to initialize", -1));
	parse_file(&data);
	setup_window(&data);
	mlx_loop(data.mlx.mlx_ptr);
	free_exit(&data, EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
