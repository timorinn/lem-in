/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_rooms.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bford <bford@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 18:53:52 by bford             #+#    #+#             */
/*   Updated: 2019/11/11 15:04:40 by bford            ###   ########.fr       */
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

static t_room	*ft_make_room_list(char *s, t_room *room, t_params *par)
{
	t_room	*copy;
	char	**array;

	copy = room;
	if (!(array = ft_strsplit(s, ' ')))
		return (NULL);
	if (ft_array_size((void **)array) == 1 && ((*par).links = 1))
		return(ft_delstr_arr(array) + room);
	if (ft_array_size((void **)array) != 3 || array[0][0] == 'L'
	|| array[0][0] == '#' || !ft_isint(array[1], 0, 0, 1) ||
	!ft_isint(array[2], 0, 0, 1))
		return (NULL + ft_delstr_arr(array) + ft_del_all(NULL, room));
	if (!room)
		return ((room = ft_lstnew_room(array[0], ft_atoi(array[1]),
		ft_atoi(array[2]), par)) ? room + ft_delstr_arr(array) :
		ft_delstr_arr(array) + NULL);
	while (copy->next)
		if (!ft_strcmp(copy->name, array[0]) || !(copy = copy->next))
			return (ft_del_all(NULL, room) + ft_delstr_arr(array) + NULL);
	return ((copy->next = ft_lstnew_room(array[0], ft_atoi(array[1]),
	ft_atoi(array[2]), par)) ? room + ft_delstr_arr(array) :
	NULL + ft_delstr_arr(array) + ft_del_all(NULL, room));
}

static t_params		ft_init_room_param(char *ant)
{
	t_params	par;

	par.ants = ft_atoi(ant);
	par.num = 0;
	par.startend = 0;
	par.links = 0;
	return (par);
}

t_room			*ft_make_rooms(const t_input *input)
{
	t_room		*room;
	t_params	par;

	room = NULL;
	if (!input || !ft_isint(input->s, 1, 1, 1))
		return (NULL);
	par = ft_init_room_param(input->s);
	input = input->next;
	while (input)
	{
		if ((input->s)[0] == '#' &&
		!(ft_check_startend(input->s, &(par.startend))))
			return (NULL + ft_del_all(NULL, room));
		if ((input->s)[0] != '#')
		{
			if (!par.links)
			{
				if (!(room = ft_make_room_list(input->s, room, &par)))
					return (NULL);
			}
			/*
			if (par.links)
			{
				if 
			}
			*/
		}
		input = input->next;
	}
	return (room);
}
