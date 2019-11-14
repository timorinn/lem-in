/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swedde <swedde@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 13:17:03 by bford             #+#    #+#             */
/*   Updated: 2019/11/15 02:28:55 by swedde           ###   ########.fr       */
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

void	step_do_one(t_path *buf, t_room *room, int num, int *ant_num)
{
	t_room	*cur;
	t_room	*cont;
	char	*s;
	char	*s1;
	char	*s2;
	char	*s3;

	cur = get_room(room, buf->way[num]);
	if (cur->end)
		return ;
	step_do_one(buf, room, num + 1, ant_num);
	if (cur->start && buf->step_ants <= 0)
		return ;
	if (cur->ant)
	{
		cont = get_room(room, buf->way[num + 1]);
		cur->ant--;
		cont->ant++;
		
		if (cur->start)
		{
			(*ant_num)++;
			cont->ant_num = *ant_num;
		}
		else
			cont->ant_num = cur->ant_num;
		s1 = ft_strjoin("L", ft_itoa(cont->ant_num));
		s2 = ft_strjoin(cont->name, " ");
		s3 = ft_strjoin("-", s2);
		s = ft_strjoin(s1, s3);
		ft_putstr(s);
		free(s);
		free(s1);
		free(s2);
		free(s3);
	/*	ft_putchar('L');
		ft_putnbr(cont->ant_num);
		ft_putchar('-');
		ft_putstr(cont->name);
		ft_putchar(' ');*/


	/*	ft_putnbr(cur->num);
		ft_putstr("->");
		ft_putnbr(cont->num);
		ft_putstr(" ");*/
	}
}

void	set_step_ants(t_path *path, int x1, int l, int ants)
{
	if (path == NULL)
		return ;
	if (path->next == NULL)
	{
		path->step_ants = ants;
		return ;
	}
	path->step_ants = x1 - (path->len - 1 - l);
	set_step_ants(path->next, x1, l, ants - path->step_ants);
}

void	steps_print(t_path *path, t_room *room)
{
	int		x1;
	int		ants;
	int		total;
	t_path	*buf;
	int		ant_num;
	t_room	*buf1;

	ant_num = 0;
	ants = room->ant;
	x1 = (ants + delta_len(path) + length_path(path) - 1) / length_path(path);
	total = path->len - 1 + x1 - 1;
	path->step_ants = x1;
	set_step_ants(path->next, x1, path->len - 1, ants - x1);

////
	int i = 1;
	buf = path;
	while (buf)
	{
		printf("a%d = %d ", i, buf->step_ants);
		buf = buf->next;
		i++;
	}
	printf("total = %d\n", total);
////

	while (total)
	{
		buf = path;
		while (buf)
		{
			step_do_one(buf, room, 0, &ant_num);
			buf->step_ants--;
			buf = buf->next;
		}
		ft_putstr("\n");
		total--;
	}

////
	buf1 = room;
	while (buf1->end == 0)
		buf1 = buf1->next;
	printf("END ANTS = %d\n", buf1->ant);
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
