/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 11:53:55 by user42            #+#    #+#             */
/*   Updated: 2020/05/21 11:57:51 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	lst_swap(t_list *a, t_list *b)
{
	void *tmp;

	tmp = a->content;
	a->content = b->content;
	b->content = tmp;
}

void	sort_sprites(t_list *lst, t_data *data)
{
	t_list *tmp;
	double sprite_dst;
	double tmp_dst;

	while (lst)
	{
		tmp = lst->next;
		while (tmp)
		{
			sprite_dst = (
			(data->cam.x - ((t_point*)(lst->content))->x) *
			(data->cam.x - ((t_point*)(lst->content))->x) +
			(data->cam.y - ((t_point*)(lst->content))->y) *
			(data->cam.y - ((t_point*)(lst->content))->y));
			tmp_dst = (
			(data->cam.x - ((t_point*)(lst->content))->x) *
			(data->cam.x - ((t_point*)(tmp->content))->x) +
			(data->cam.y - ((t_point*)(tmp->content))->y) *
			(data->cam.y - ((t_point*)(tmp->content))->y));
			if (tmp_dst > sprite_dst)
				lst_swap(lst, tmp);
			tmp = tmp->next;
		}
		lst = lst->next;
	}
}
