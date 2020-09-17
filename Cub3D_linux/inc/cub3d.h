/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 18:45:19 by user42            #+#    #+#             */
/*   Updated: 2020/09/17 23:51:27 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <math.h>
# include <string.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include <X11/X.h>

# include "libft.h"
# include "get_next_line.h"
# include "mlx.h"

# define ARG_SAVE "--save"
# define MAP_EXTENSION "cub"

# define WALKABLE "0NSEW"

# define MIN_WIDTH 100

# define SPEED 0.1
# define ROT_SPEED 0.1
# define ESCAPE 65307
# define FORWARD 119
# define BACKWARD 115
# define RIGHT 100
# define LEFT 97
# define ROT_RIGHT 65363
# define ROT_LEFT 65361

# define BMP_HEADER_OFFSET 54
# define BMP_DIBHEADER_SIZE 40
# define BMP_COLOR_PLANE 1

typedef enum	e_bool
{
	false,
	true
}				t_bool;

/*
** Structures
*/
typedef struct	s_point
{
	double	x;
	double	y;
}				t_point;

typedef struct	s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
}				t_mlx;

typedef struct	s_img
{
	void	*img_ptr;
	char	*data_address;
	int		line_size;
	int		bpp;
	int		endian;
	int		width;
	int		height;
}				t_img;

typedef struct	s_ray
{
	double	center_x_offset;
	double	x;
	double	y;
	int		map_x;
	int		map_y;
	double	dx;
	double	dy;
	double	len_x;
	double	len_y;
	double	dlen_x;
	double	dlen_y;
	double	step_x;
	double	step_y;
	double	wall_dist;
	double	wall_side;
	double	wall_x;
	t_img	*texture;
	int		text_x;
	int		text_y;
}				t_ray;

typedef struct	s_sprite_ray
{
	double	x;
	double	y;
	double	inv_det;
	double	tx;
	double	ty;
	int		screen_x;
	int		height;
	int		width;
	int		draw_start_y;
	int		draw_end_y;
	int		draw_start_x;
	int		draw_end_x;
}				t_sprite_ray;

typedef struct	s_map
{
	char	*map_path;
	char	**tile_map;
	double	width;
	double	height;
	t_img	*texture_no;
	t_img	*texture_so;
	t_img	*texture_ea;
	t_img	*texture_we;
	t_img	*texture_sprite;
	t_list	*sprite_list;
	int		ceiling_color;
	int		floor_color;
}				t_map;

typedef struct	s_cam
{
	double		x;
	double		y;
	double		dx;
	double		dy;
	double		px;
	double		py;
	t_bool		forward;
	t_bool		backward;
	t_bool		right;
	t_bool		left;
	t_bool		rot_right;
	t_bool		rot_left;
}				t_cam;

typedef struct	s_data
{
	t_mlx	mlx;
	t_map	map;
	t_cam	cam;
	t_bool	save;
	t_img	image;
	double	*wall_dist;
}				t_data;

/*
** Window management
*/
void			setup_window(t_data *data);
int				on_key_press(int keycode, t_data *data);
int				on_key_release(int keycode, t_data *data);

/*
** Drawing
*/
void			draw(t_data *data);
void			draw_sprites(t_data *data);
void			set_pixel_color(int x, int y, int color, t_data *data);
void			rectify_wall_dist(t_ray *ray);
void			get_step_and_dlen(t_ray *ray);
void			set_pixel_color(int x, int y, int color, t_data *data);
void			init_ray(t_data *data, t_ray *ray, int x);
void			sort_sprites(t_list *lst, t_data *data);

/*
** Movement
*/
void			move(t_data *data);

/*
** Data management
*/
void			init_data(t_data *data);
void			free_exit(t_data *data, int exit_value);
void			manage_arg(t_data *data, int argc, char **argv);
void			destroy_image(void *mlx_ptr, t_img *img);

/*
** Parsing
*/
void			parse_file(t_data *data);

int				get_data(t_data *data, int file_descriptor);
int				data_switch(t_data *data, char **line_split);
int				get_r_data(t_data *data, char **line_split);
void			check_r_data(t_data *data);
int				get_img_data(t_data *data, char **line_split, t_img **img);
int				wall_texture_switch(t_data *data, char **line_split);
void			data_switch_color(t_data *data, char **line_split, int *error);
int				get_color_data(char **line_split, int *rgb_value);
int				check_data(t_data *data);

int				pass_empty_line(char **line, int file_descriptor);

int				get_map(t_data *data, int file_descriptor);
int				get_map_max_width(t_list *file_lines);
int				alloc_map(t_data *data, t_list *map_lines, int *tm_width,
int *tm_height);
int				get_sprite(t_data *data, int x, int y);
int				get_cam_start(t_data *data, int x, int y);
int				check_map(t_data *data);
int				check_closed_map(t_data *data, int x, int y);

/*
** .bmp
*/
int				img_to_bmp(t_img *img);

/*
**  Utils
*/
void			set_cam_dir(t_data *data, double dx, double dy);
int				ft_ischarset(char c, char *charset);

char			**free_table(char **table);
int				table_len(char **tab);
int				put_error(char *error_msg, int return_value);

#endif
