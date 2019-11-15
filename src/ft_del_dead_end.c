/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_del_dead_end.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bford <bford@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 12:49:49 by bford             #+#    #+#             */
/*   Updated: 2019/11/15 14:13:17 by bford            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void	ft_del_first(t_room **room)
{
	t_room	*copy;
	t_link	*link;
	t_link	*link2;

	copy = *room;
	*room = (*room)->next;
	link2 = copy->link;
	while (link2)
	{
		link = link2->next;
		free(link2);
		link2 = link;
	}
	ft_strdel(&copy->name);
	free(copy);
}

void		ft_del_dead_end(t_room **room)
{
	//t_room	*copy;
	t_room	*prev;

	if (!room || !(*room))
		return ;
	prev = NULL;
	if ((*room)->num_links < 2)
	{
		ft_del_first(room);
	}
	while (*room)
	{
		prev = (*room);
		(*room) = (*room)->next;
	}
}
