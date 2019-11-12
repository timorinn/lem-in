/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_rooms.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsheev <nsheev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 18:53:52 by bford             #+#    #+#             */
/*   Updated: 2019/11/12 20:27:15 by nsheev           ###   ########.fr       */
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
		return ((*par).startend == 22 ? ft_delstr_arr(array) + room :
		NULL + ft_delstr_arr(array) + ft_del_all(NULL, room));
	if (ft_array_size((void **)array) != 3 || array[0][0] == 'L'
	|| array[0][0] == '#' || !ft_isint(array[1], 0, 0, 1) ||
	!ft_isint(array[2], 0, 0, 1) || ft_strchr(array[0], '-'))
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

static int		ft_make_links_3(t_room *room_1, t_room *room_2)
{
	t_link	*link;

	if (!(link = room_1->link))
		return ((room_1->link = ft_lstnew_link(room_2)) ? 1 : 0);
	if (!ft_strcmp(link->room->name, room_1->name) ||
	!ft_strcmp(link->room->name, room_2->name))
		return (1);
	while (link->next)
	{
		if (!ft_strcmp(link->next->room->name, room_1->name) ||
		!ft_strcmp(link->next->room->name, room_2->name))
			return (0);
		link = link->next;
	}
	return ((link->next = ft_lstnew_link(room_2)) ? 1 : 0);
}

static int		ft_make_links_2(t_room *room, const char *s1,
const char *s2)
{
	t_room	*rcopy;
	t_room	*room_1;
	t_room	*room_2;

	room_1 = NULL;
	room_2 = NULL;
	rcopy = room;
	while (rcopy && (!room_1 || !room_2))
	{
		if (!ft_strcmp(rcopy->name, s1))
			room_1 = rcopy;
		else if (!ft_strcmp(rcopy->name, s2))
			room_2 = rcopy;
		rcopy = rcopy->next;
	}
	if (!room_1 || !room_2)
		return (0);
	return (ft_make_links_3(room_1, room_2) &&
	ft_make_links_3(room_2, room_1) ? 1 : 0);
}

static int		ft_make_links(t_room *room, const char *s)
{
	int		i;
	char	*name1;
	char	*name2;

	i = 0;
	if (!room || !s)
		return (0);
	while (s[i] && s[i] != '-' && ++i)
		;
	if (!s[i] || s[i] != '-' || !s[i + 1] || ft_strchr(s + i + 1, '-') ||
	!(name1 = ft_strndup(s, i)))
		return (0);
	s += i + 1;
	i = 0;
	while (s[i] && !ft_isspace(s[i]) && ++i)
		;
	if (s[i] || !(name2 = ft_strndup(s, i)) || !ft_strcmp(name1, name2))
		return (ft_strdel(&name1) + ft_strdel(&name2));
	return ((ft_make_links_2(room, name1, name2) ? 1 : 0) +
	ft_strdel(&name1) + ft_strdel(&name2));
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
			if (!par.links && !(room = ft_make_room_list(input->s, room, &par)))
				return (NULL);
			if (par.links && !ft_make_links(room, input->s))
				return (NULL + ft_del_all(NULL, room));
		}
		input = input->next;
	}
	return (room);
}
