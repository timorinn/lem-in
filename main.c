/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swedde <swedde@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 13:17:03 by bford             #+#    #+#             */
/*   Updated: 2019/11/14 15:53:36 by swedde           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void		ft_print_input(t_input *input);
static void		ft_print_rooms(t_room *room);
static void		ft_print_limit(int limit);

int		length_path(t_path *l)
{
	int i;

	i = 0;
	while (l)
	{
		l = l->next;
		i++;
	}
	return (i);
}

int		delta_len(t_path *a)
{
	int		l1;
	int		l2;
	int		l;

	l1 = a->len - 1;
	l = 0;
	a = a->next;
	while (a)
	{
		l2 = a->len - 1;
		l = l + l2 - l1;
		a = a->next;
	}
	return (l);
}

t_room	*get_room(t_room *room, int num)
{
	while (room->num != num)
		room = room->next;
	return (room);
}

void	step_do_one(t_path *buf, t_room *room, int num)
{
	t_room	*cur;
	t_room	*cont;

	cur = get_room(room, buf->way[num]);
	if (cur->end)
		return ;
	step_do_one(buf, room, num + 1);
	if (cur->start && buf->step_ants <= 0)
		return ;
	if (cur->ant)
	{
		cont = get_room(room, buf->way[num + 1]);
		cur->ant--;
		cont->ant++;
		ft_putnbr(cur->num);
		ft_putstr("->");
		ft_putnbr(cont->num);
		ft_putstr(" ");
	}
}

void	steps_print(t_path *path, t_room *room)
{
	int		x1;
	int		ants;
	int		total;
	t_path	*buf;

	ants = room->ant;
	x1 = (ants + delta_len(path)) / length_path(path);
//	ft_putnbr(x1);
//	ft_putchar('\n');
	total = path->len - 1 + x1 - 1;
	path->step_ants = 9;
	path->next->step_ants = 7;
	path->next->next->step_ants = 5;
	while (total)
	{
		buf = path;
		while (buf)
		{
			step_do_one(buf, room, 0);
			buf->step_ants--;
			buf = buf->next;
		}
		ft_putstr("\n");
		total--;
	}
}

int		main(int argc, char **argv)
{
	t_input		*input;
	t_room		*room;
	t_path		*path;

	input = ft_analize_input(argc, argv);
	room = ft_make_rooms(input);
	room->next->ant = 0;
	if (!input || !room)
		ft_putstr("ERROR\n");
	else
	{
		ft_print_input(input);
		ft_print_rooms(room);
		ft_print_limit(ft_limit_path(room));
		path = get_path(room, ft_limit_path(room));
	}
	steps_print(path, room);
	return (ft_del_all(input, room));
}




/***********************************/
/*		FUNCTIONS FOR CHECK		   */
/***********************************/

static void		ft_print_input(t_input *input)
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

static void		ft_print_rooms(t_room *room)
{
	t_room	*copy;
	t_link	*link;
	int		i;

	copy = room;
	ft_putstr("\n******** PRINT ROOMS ********\n");
	while (copy)
	{
		i = 0;

		printf("Room_%8s | num = %2d | ants = %4d | start = %3d | end = %3d | ",
		copy->name, copy->num, copy->ant, copy->start, copy->end);
		link = copy->link;
		while (link)
		{
			printf("link_%2d = %s | ", i++, link->room->name);
			link = link->next;
		}
		printf("\n");
		copy = copy->next;
	}
}

static void		ft_print_limit(int	limit)
{
	ft_putstr("\n******** PRINT LIMIT ********\n");
	printf("Limit = %d\n", limit);
}
