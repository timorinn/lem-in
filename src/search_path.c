/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swedde <swedde@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 02:27:16 by swedde            #+#    #+#             */
/*   Updated: 2019/11/21 12:49:16 by swedde           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		*concat_way(t_path **buf, int num)
{
	int		*array;
	int		i;

	if (!(array = (int *)malloc(sizeof(int) * (*buf)->len + 1)))
		return (NULL);
	i = 0;
	while (i < (*buf)->len)
	{
		array[i] = (*buf)->way[i];
		i++;
	}
	array[i] = num;
	return (array);
}

t_path	*new_lst_path(t_path **buf, int num, int status)
{
	t_path	*new;

	new = (t_path *)malloc(sizeof(t_path));
	new->way = concat_way(buf, num);
	new->next = NULL;
	new->len = (*buf)->len + 1;
	new->status = status;
	return (new);
}

int		push_tail(t_path **start, t_path **buf, int num, int status)
{
	t_path	*temp;

	if (buf == NULL)
	{
		*start = (t_path *)malloc(sizeof(t_path));
		(*start)->way = (int *)malloc(sizeof(int));
		(*start)->next = NULL;
		(*start)->len = 1;
		(*start)->way[0] = num;
		(*start)->status = 0;
	}
	else if (*start == NULL && *buf != NULL)
	{
		*start = new_lst_path(buf, num, status);
	}
	else
	{
		temp = *start;
		while (temp->next)
			temp = temp->next;
		temp->next = new_lst_path(buf, num, status);
	}
	return (1);
}

t_path	*pop_path(t_path **start)
{
	t_path	*l;

	if (*start == NULL)
		return (NULL);
	l = *start;
	*start = (*start)->next;
	return (l);
}

int		ended_path(t_path **l, int end)
{
	if (*l)
	{
		if ((*l)->way[(*l)->len - 1] == end)
			return (1);
		return (0);
	}
	return (0);
}

void	push_bottom_path(t_path **start, t_path **buf)
{
	t_path *l;

	l = *start;
	if (*start == NULL)
		*start = *buf;
	else
	{
		while (l->next)
			l = l->next;
		l->next = *buf;
	}
}

int lenfth(t_path *l)
{
	int i;

	i = 0;
	while (l)
	{
		i++;
		l = l->next;
	}
	return (i);
}

t_link	*get_link(t_room *room, t_path *l)
{
	while (l && room->num != l->way[l->len - 1])
		room = room->next;
	if (room->visit)
		return (NULL);
	room->visit = 1;
	return (room->link);
}

int		get_end(t_room *room)
{
	while (room->end == 0)
		room = room->next;
	return (room->num);
}

int		no_dublicate(t_path *buf, t_link *buf_child)
{
	int		i;

	i = 0;
	while (i < buf->len)
	{
		if (buf_child->room->num == buf->way[i])
			return (0);
		i++;
	}
	return (1);
}

int		get_start(t_room *room)
{
	while (room->start == 0)
		room = room->next;
	return (room->num);
}

void	ft_null_room(t_room *room)
{
	while (room)
	{
		room->visit = 0;
		room = room->next;
	}
}

int		get_path(t_room *room, t_path **answer, int end)
{
	t_path	*path;
	t_path  *buf;
	t_link  *buf_child;

	path = NULL;
	push_tail(&path, NULL, get_start(room), 0);
	while (path)
	{
	//	ft_print_path(path, "PATH\n");
		buf = pop_path(&path);
		if (buf && ended_path(&buf, end))
		{
			buf->next = NULL;
			push_bottom_path(answer, &buf);
			ft_null_room(room);
			return (1);
		}
		if (!buf)
			break;
		buf_child = get_link(room, buf);
		while (buf_child)
		{
			if (no_dublicate(buf, buf_child) && buf_child->conflict)
			{
			//	printf("buf->st = %d sur = %d\n", buf->status, buf_child->room->suur);
				if (buf->status == 0 && buf_child->room->suur == 0)
					push_tail(&path, &buf, buf_child->room->num, 0);
				else if (buf->status == 0 && buf_child->room->suur == 1)
					push_tail(&path, &buf, buf_child->room->num, 1);
				else if (buf->status == 1 && buf_child->room->suur == 1)
					push_tail(&path, &buf, buf_child->room->num, 2);
				else if (buf->status == 2 && buf_child->room->suur == 1)
					push_tail(&path, &buf, buf_child->room->num, 2);
				else if (buf->status == 2 && buf_child->room->suur == 0)
					push_tail(&path, &buf, buf_child->room->num, 0);
			}
			buf_child = buf_child->next;
		}
		if (buf)
		{
			free(buf->way);
			free(buf);
		}
	}
	ft_null_room(room);
	return (0);
}

void	delete_links(t_room *room, t_path *tmp, int a)
{
	int		i;
	t_link	*buf;
	
	while (tmp)
	{
		i = 0;
		while (i < tmp->len - 1)
		{
			buf = get_room(room, tmp->way[i])->link;
			while (buf->room->num != tmp->way[i + 1])
				buf = buf->next;
			buf->conflict = a;
			i++;
		}
		tmp = tmp->next;
	}
}

void	set_def_links(t_room *room)
{
	t_link *link;

	while (room)
	{
		room->suur = 0;
		room->visit = 0;
		link = room->link;
		while (link)
		{
			link->conflict = 1;
			link = link->next;
		}
		room = room->next;
	}
}

void	set_vertex_sur(t_room *room, t_path *tmp)
{
	int		i;

	while (tmp)
	{
		i = 0;
		while (i < tmp->len)
		{
			get_room(room, tmp->way[i])->suur = 1;
			i++;
		}
		tmp = tmp->next;
	}
}

int			build_new_links(t_path *answer, t_room *room)
{
	t_path		*buf;
	t_link		*tmp;
	t_vertex	*vertex;
	int			i;
	int			j;

	j = 0;
	vertex = NULL;
	buf = answer;
	while (buf)
	{
		i = 1;
		while (i < buf->len - 1)
		{
			increase_vertex(&vertex, buf->way[i]);
			i++;
		}
		buf = buf->next;
	}
	while (answer)
	{
		i = 1;
		while (i < answer->len - 2)
		{
			if (get_vertex(vertex, answer->way[i])->op > 0 && get_vertex(vertex, answer->way[i + 1])->op > 0)
			{
				tmp = get_room(room, answer->way[i])->link;
				while (tmp->room->num != answer->way[i + 1])
					tmp = tmp->next;
				if (tmp)
				{
					tmp->conflict = 0;
					j++;
				}
			}
			i++;
		}
		answer = answer->next;
	}
	vertex_lst_del(&vertex);
	return (j);
}

void	set_visit_path(t_room *room, t_path *answer)
{
	int i;

	while (answer)
	{
		i = 1;
		while (i < answer->len - 1)
		{
			get_room(room, answer->way[i])->visit = 1;
			i++;
		}
		answer = answer->next;
	}
}

void	search_path(t_room *room, t_path **answer)
{
	int		end;
	t_path	*tmp;
	int		j;

	end = get_end(room);

	set_def_links(room);
	get_path(room, answer, end);
	while (length_path(*answer) < ft_limit_path(room))
	{
		tmp = *answer;
		delete_links(room, tmp, 0);
		set_vertex_sur(room, tmp);
		if (!get_path(room, answer, end))
			break;
		set_def_links(room);
		if (!build_new_links(*answer, room))
		{
			set_def_links(room);
		//	ft_print_path(*answer, "CONTINE\n");
			continue;
		}
		j = length_path(*answer);

		*answer = NULL;

		while (j)
		{
			get_path(room, answer, end);
			set_visit_path(room, *answer);
			j--;
		}
		set_def_links(room);
	//	ft_print_path(*answer, "ITOG\n");
	}
}