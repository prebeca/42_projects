/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prebeca <prebeca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 21:12:39 by prebeca           #+#    #+#             */
/*   Updated: 2020/01/14 21:27:34 by prebeca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include "map.h"

typedef struct	s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	int	plan_x;
	int		plan_y;
	t_map	*map;
}				t_data;

#endif