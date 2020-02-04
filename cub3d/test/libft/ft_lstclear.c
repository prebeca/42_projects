/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prebeca <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 17:15:55 by prebeca           #+#    #+#             */
/*   Updated: 2019/11/15 16:11:19 by prebeca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*todel;

	if (!lst || !del)
		return ;
	todel = *lst;
	while (todel)
	{
		*lst = (*lst)->next;
		del(todel->content);
		free(todel);
		todel = *lst;
	}
}
