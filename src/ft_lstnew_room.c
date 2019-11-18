/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_room.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsheev <nsheev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 17:03:06 by bford             #+#    #+#             */
/*   Updated: 2019/11/18 17:37:18 by nsheev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_room	*ft_lstnew_room(char *name, int x, int y, t_params *par)
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
	room->num = (*par).num++;
	room->x = x;
	room->y = y;
	room->num_links = 0;
	room->visit = 0;
	room->link = NULL;
	if ((*par).startend % 10 == 1 && (room->start = 1))
	{
		(*par).startend += 1;
		room->ant = (*par).ants;
	}
	else
		room->start = 0;
	if ((*par).startend / 10 == 1 && (room->end = 1))
		(*par).startend += 10;
	else
		room->end = 0;
	return (room);
}
