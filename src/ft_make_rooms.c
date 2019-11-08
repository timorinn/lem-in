/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_rooms.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bford <bford@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 18:53:52 by bford             #+#    #+#             */
/*   Updated: 2019/11/08 20:08:04 by bford            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int		ft_check_startend(char *s, int *startend)
{
	if (!strcmp(s, "##start"))
	{
		if (*startend % 10)
			return (0);
		*startend += 1;
	}
	else if (!strcmp(s, "##end"))
	{
		if (*startend / 10)
			return (0);
		*startend += 10;
	}

	return (1);
}

static t_room	*ft_make_room_list(char *s, t_room *room, int *startend, int *links)
{
	t_room	*copy;
	char	**array;
	int		word;

	word = 0;
	copy = room;
	if (!(array = ft_strsplit(s, ' ')))
		return (NULL);
	while (array[word])
		word++;
	if (word == 1 && (*links = 1))
		return(ft_delstr_arr(array) + room);
	else if (word == 3)
	{
		if (array[0][0] == 'L' || array[0][0] == '#' ||
		!ft_isint(array[1], 0, 0, 0) || !ft_isint(array[2], 0, 0, 0))
			return (NULL + ft_del_all(NULL, NULL, room));
		if (!room)
		{
			if (!(room = ft_lstnew_room(array[0], ft_atoi(array[1]), ft_atoi(array[2]), startend)))
				return (ft_delstr_arr(array) + NULL);
		}
		else
		{
			while (copy->next)
			{
				if (!ft_strcmp(copy->name, array[0]))
				{
					ft_putstr("{ 1 }\n");
					return (ft_del_all(NULL, NULL, room) + ft_delstr_arr(array) + NULL);
				}
				copy = copy->next;
			}
			if (!(copy->next = ft_lstnew_room(array[0], ft_atoi(array[1]), ft_atoi(array[2]), startend)))
				return (NULL + ft_delstr_arr(array) + ft_del_all(NULL, NULL, room));
		}
	}
	return (room + ft_delstr_arr(array));
}

t_room			*ft_make_rooms(const t_input *input, t_ant *ant)
{
	t_room	*room;
	int		startend;
	int		links;

	startend = 0;
	links = 0;
	room = NULL;
	if (!ant || !input)
		return (NULL);
	input = input->next;
	while (input)
	{
		if ((input->s)[0] == '#')
		{
			if (!(ft_check_startend(input->s, &startend)))
				return (NULL + ft_del_all(NULL, NULL, room));
		}
		else
		{
			if (!links)
			{
				if (!(room = ft_make_room_list(input->s, room, &startend, &links)))
					return (NULL);
			}
			/*
			if (links)
			else
			{
				
			}
			*/
		}
		input = input->next;
	}
	return (room);
}
