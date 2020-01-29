/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prebeca <prebeca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 00:15:30 by prebeca           #+#    #+#             */
/*   Updated: 2020/01/29 15:35:35 by prebeca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include "libft.h"
# include "mlx.h"

# define NB_FLAGS 8

typedef struct	s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
}           t_mlx;

typedef	struct	s_move
{
	int			up;
	int			down;
	int			right;
	int			left;
	double		rot_speed;
}				t_move;

typedef struct	s_img
{
	void		*img_ptr;
	int			width;
	int			height;
	char		*buffer;
	int			bpp;
	int			line_size;
}				t_img;

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
	double			step_x;
	double			step_y;
	int			face;
	double		len;
	double			wall_h;
	double			draw_start;
	double			draw_end;
}				t_ray;

typedef struct	s_cam
{
	double		screen_h;
	double		screen_w;
	double		screen_dir_x;
	double		screen_dir_y;
	double		x;
	double		y;
	double		height;
	double		dir_x;
	double		dir_y;
	double		fov;
	double		camtoscreen_dist;
	double		speed;
}				t_cam;

typedef struct	s_map
{
	void		*texture_no;
	void		*texture_so;
	void		*texture_ea;
	void		*texture_we;
	void		*sprite;
	int			floor_color;
	int			ceiling_color;
	int			**map;
	int 		h;
	int			w;
}				t_map;

typedef struct	s_data
{
	t_mlx		mlx;
	t_cam		cam;
	t_map		map;
	t_move		move;
	t_img		img;
}				t_data;

typedef struct	s_flag
{
	char *flag;
	int (*fct)(t_data*, char**);
}				t_flag;


void    raycast(t_data *data);
int	map_parser(char *path, t_data *data);
int key_press(int keycode, t_data *data);
int key_release(int keycode, t_data *data);
int move(t_data *data);
int init_flag_table(t_flag **flag_table);
t_flag *new_flag(char *flag_name, int (*fct)(t_data*, char**));
void *get_texture(t_data *, char **);
int get_color(t_data *data, char **data_line);
int tab_len(char **tab);
int get_res(t_data *data, char **);
int texture_switch(t_data *, char **);



#endif