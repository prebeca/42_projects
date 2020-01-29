/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prebeca <prebeca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 01:55:55 by prebeca           #+#    #+#             */
/*   Updated: 2020/01/14 20:38:06 by prebeca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

#include "get_next_line.h"
#include <fcntl.h>
#include "libft.h"

typedef struct	s_pos
{
	double		pos_x;
	double		pos_y;
	char		orient;
}				t_pos;

typedef struct	s_rgb
{
	int 		red;
	int 		green;
	int			blue;
}				t_rgb;

typedef struct	s_map
{
	int 	res_x;
	int 	res_y;
	int		wall;
	int		empty;
	int		item;
	t_pos	start_pos;
	char	*texture_no;
	char	*texture_so;
	char	*texture_we;
	char	*texture_ea;
	char	*sprite;
	t_rgb	floor;
	t_rgb	ceiling;
	int 	**map;
	int		map_y_len;
	int		map_x_len;
} 				t_map;

int	*ft_map(char **tab, int length, int (*f)(const char*));
int	get_split_len(char **split);
int get_map_len(char *path);
t_map	*get_map(char *path);

#endif