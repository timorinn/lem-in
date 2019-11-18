/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsheev <nsheev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 13:17:03 by bford             #+#    #+#             */
/*   Updated: 2019/11/18 19:32:51 by nsheev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		ft_print_input(t_input *input);
void		ft_print_rooms(t_room *room);

static int	ft_len_path(t_path *itog)
{
	int		len;

	len = 0;
	while (itog && ++len)
		itog = itog->next;
	return (len);
}

int		main(int argc, char **argv)
{
	t_input		*input;
	t_room		*room;
	t_path		*path;
	int			limit;

	path = NULL;
	input = ft_analize_input(argc, argv);
	room = ft_make_rooms(input);
	limit = ft_limit_path(room);
	while (get_path(room, &path) && limit > ft_len_path(path))
		;
	ft_print_path(path, "RESULT\n");
	if (!input || !room  || !path )
		ft_putstr("ERROR\n");
	else
	{
		//ft_print_input(input);
		//ft_print_rooms(room);
		//ft_print_path(path, "\nuTor\n");
		steps_print(path, room);
	}
	return (ft_del_all(input, room) + ft_lstdel_path(path));
}




/***********************************/
/*		FUNCTIONS FOR CHECK		   */
/***********************************/

void		ft_print_input(t_input *input)
{
	t_input		*copy;

	copy = input;
	ft_putstr("\n******** PRINT INPUT ********\n");
	while (copy)
	{
		ft_putendl(copy->s);
		copy = copy->next;
	}
}

void		ft_print_rooms(t_room *room)
{
	t_room	*copy;
	t_link	*link;
	int		i;

	copy = room;
	ft_putstr("\n******** PRINT ROOMS ********\n");
	while (copy)
	{
		i = 0;

		printf("Room_%8s | num = %2d | ants = %4d | start = %3d | end = %3d | num_links = %2d | ",
		copy->name, copy->num, copy->ant, copy->start, copy->end, copy->num_links);
		link = copy->link;
		while (link)
		{
			printf("link_%2d = %2s | ", i++, link->room->name);
			link = link->next;
		}
		printf("\n");
		copy = copy->next;
	}
}
