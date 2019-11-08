/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_room.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bford <bford@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 17:03:06 by bford             #+#    #+#             */
/*   Updated: 2019/11/08 17:37:56 by bford            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_room	*ft_lstnew_room(char *name, int x, int y, int *startend)
{
	t_room	*room;

	if (!name || !(room = (t_room *)malloc(sizeof(t_room))))
		return (NULL);
	if (!(room->name = ft_strdup(name)))
	{
		free(room);
		return (NULL);
	}
	room->next = NULL;
	room->num = 0;
	room->ant = 0;
	room->x = x;
	room->y = y;
	if (*startend % 10 == 1)
	{
		room->start = 1;
		*startend += 1;
	}
	else
		room->start = 0;
	if (*startend / 10 == 1)
	{
		room->end = 1;
		*startend += 10;
	}
	else
		room->end = 0;
	return (room);
}
