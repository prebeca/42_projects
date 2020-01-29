/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prebeca <prebeca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 00:11:38 by prebeca           #+#    #+#             */
/*   Updated: 2020/01/29 17:05:56 by prebeca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/System/Library/Frameworks/Tk.framework/Versions/8.5/Headers/X11/X.h"

int loop_hook(t_data *data)
{
	if (data->move.up == 1 || data->move.down == 1 || data->move.right == 1 || data->move.left == 1 || data->move.rot_speed != 0)
		move(data);
	return (0);
}

int safe_quit()
{
	exit(0);
}

int main(int ac, char **av)
{
	t_data data;

	(void)ac;

	data.move.up = 0;
	data.move.down = 0;
	data.move.right = 0;
	data.move.left = 0;
	data.move.rot_speed = 0;
	data.cam.speed = 0.2;

	if ((data.mlx.mlx_ptr = mlx_init()) == 0)
		return (1);
	if ((map_parser(av[1], &data)) == -1)
		return (-1);
	if ((data.mlx.win_ptr = mlx_new_window(data.mlx.mlx_ptr, data.map.w, data.map.h, "cub3d")) == 0)
		return (1);
	mlx_hook(data.mlx.win_ptr, 17, 1L << 17, &exit, 0);
	mlx_hook(data.mlx.win_ptr, KeyPress, KeyPressMask, &key_press, &data);
	mlx_hook(data.mlx.win_ptr, KeyRelease, KeyReleaseMask, &key_release, &data);
	mlx_loop_hook(data.mlx.mlx_ptr,&loop_hook, &data);
	raycast(&data);
	mlx_loop(data.mlx.mlx_ptr);


	// int i = 0;
	// int j = 0;
	// while (i < 10)
	// {
	// 	while(j < 10)
	// 	{
	// 		printf("%d", data.map.map[i][j]);
	// 		++j;
	// 	}
	// 	j = 0;
	// 	printf("\n");
	// 	++i;
	// }

	
	// printf("w = %d\n", data.map.w);
	// printf("h = %d\n", data.map.h);
	// printf("c = %d\n", data.map.ceiling_color);
	// printf("f = %d\n", data.map.floor_color);
	return (0);
}