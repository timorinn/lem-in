/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swedde <swedde@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 13:17:03 by bford             #+#    #+#             */
/*   Updated: 2019/11/21 12:49:04 by swedde           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		ft_print_input(t_input *input);
void		ft_print_rooms(t_room *room);

void	sort_path(t_path **answer)
{
	t_path	*tmp;
	t_path	*buf;

	if (!(*answer)->next)
		return ;
	if ((*answer)->len > (*answer)->next->len)
	{
		tmp = (*answer)->next;
		(*answer)->next = (*answer)->next->next;
		tmp->next = *answer;
		*answer = tmp;
	}
	tmp = *answer;
	while (tmp->next->next)
	{
		if (tmp->next->len > tmp->next->next->len)
		{
			buf = tmp->next->next;
			tmp->next->next = buf->next;
			buf->next = tmp->next;
			tmp->next = buf;
			tmp = (*answer);
			continue;
		}
		tmp = tmp->next;
	}
}

int		main(int argc, char **argv)
{
	t_input		*input;
	t_room		*room;
	t_path		*path;

	path = NULL;
	input = ft_analize_input(argc, argv);
	room = ft_make_rooms(input);

	search_path(room, &path);
//	ft_print_path(path, "CREATE\n");
	sort_path(&path);
//	ft_print_path(path, "SORT\n");
	reposition_path(&path);
//	ft_print_path(path, "REPOSITION\n");
	
	if (!input || !room  || !path )
		ft_putstr("ERROR\n");
	else
		steps_print(path, room);
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
