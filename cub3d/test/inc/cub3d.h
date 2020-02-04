/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prebeca <prebeca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 00:15:30 by prebeca           #+#    #+#             */
/*   Updated: 2020/02/04 05:04:38 by prebeca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <math.h>
# include "libft.h"
# include "mlx.h"
# include "get_next_line.h"
# include "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/System/Library/Frameworks/Tk.framework/Versions/8.5/Headers/X11/X.h"

# define NB_FLAGS 8

typedef struct	s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
}           t_mlx;

typedef struct s_img
{
	void	*img_ptr;
	char	*buffer;
	int		line_size;
	int		bpp;
	int		endian;
	int		res_w;
	int		res_h;
}			t_img;

typedef struct s_cam
{
	double	screen_dir_x;
	double	screen_dir_y;
}	t_cam;

typedef	struct	s_move
{
	int			up;
	int			down;
	int			right;
	int			left;
	double		rot_speed;
	double		speed;
	double		sprint;
}				t_move;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double 	dir_y;
	t_move 	move;
	
}		t_player;


typedef struct	s_map
{
	t_img	*texture_no;
	t_img	*texture_so;
	t_img	*texture_ea;
	t_img	*texture_we;
	t_img	*sprite;
	int	floor_color;
	int		ceiling_color;
	int		**map;
	double 		res_h;
	double			res_w;
}				t_map;

typedef struct	s_data
{
	t_mlx		mlx;
	t_map 		map;
	t_player 	player;
	t_cam		cam;
	t_img		buffer;
}           t_data;

typedef struct	s_ray
{
	double		center_x;
	double		x;
	double		y;
	int			map_x;
	int			map_y;
	double		dir_x;
	double		dir_y;
	int			hit;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		step_x;
	double		step_y;
	int			face;
	double		len;
	double		wall_h;
	int		draw_start;
	int		draw_end;
}				t_ray;

int	init_data(t_data *data);
int map_parser(char *path, t_data *data);
int raycast(t_data *data);
int move(t_data *data);
int printerr(char *err);
int check_data(t_data *data);

/*
 *	HOOK 
 */
int	exit_hook(t_data *);
int loop_hook(t_data *data);
int key_press(int keycode, t_data *data);
int key_release(int keycode, t_data *data);

#endif