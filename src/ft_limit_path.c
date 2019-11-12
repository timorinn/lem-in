/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_limit_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bford <bford@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 15:27:33 by bford             #+#    #+#             */
/*   Updated: 2019/11/12 15:54:24 by bford            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int	ft_exits(t_link *link)
{
	int		exits;

	exits = 0;
	while (link && ++exits)
		link = link->next;
	return (exits);
}

int		ft_limit_path(t_room *room)
{
	int		limit[3];
	int		min;
	t_room	*copy;

	copy = room;
	while (copy)
	{
		if (copy->start && (limit[0] = copy->ant))
			limit[1] = ft_exits(copy->link);
		else if (copy->end)
			limit[2] = ft_exits(copy->link);
		copy = copy->next;
	}
	min = (limit[0] < limit[1] ? limit[0] : limit[1]);
	return (limit[2] < min ? limit[2] : min);
}
