/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swedde <swedde@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 02:27:16 by swedde            #+#    #+#             */
/*   Updated: 2019/11/23 21:52:42 by swedde           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_room	**concat_way(t_path **buf, t_room *num)
{
	t_room	**array;
	int		i;

	if (!(array = (t_room**)malloc(sizeof(t_room*) * (*buf)->len + 1)))
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

t_path	*new_lst_path(t_path **buf, t_room *num, int status)
{
	t_path	*l;

	l = (t_path *)malloc(sizeof(t_path));
	l->way = concat_way(buf, num);
	l->next = NULL;
	l->len = (*buf)->len + 1;
	l->status = status;
	return (l);
}

int		push_tail(t_path **start, t_path **buf, t_room *num, int status)
{
	t_path	*temp;

	if (!buf)
	{
		*start = (t_path *)malloc(sizeof(t_path));
		(*start)->way = (t_room**)malloc(sizeof(t_room*));
		(*start)->next = NULL;
		(*start)->len = 1;
		(*start)->way[0] = num;
		(*start)->status = 0;
	}
	else if (!*start && *buf)
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

	if (!*start)
		return (NULL);
	l = *start;
	*start = (*start)->next;
	l->next = NULL;
	return (l);
}

void	push_bottom_path(t_path **start, t_path **buf)
{
	t_path *l;

	l = *start;
	if (!*start)
		*start = *buf;
	else
	{
		while (l->next)
			l = l->next;
		l->next = *buf;
	}
}

t_link	*get_link(t_room *room, t_path *l)
{
	if (l->way[l->len - 1]->visit)
		return (NULL);
	l->way[l->len - 1]->visit = 1;
	return (l->way[l->len - 1]->link);
}

int		get_end(t_room *room)
{
	while (!room->end)
		room = room->next;
	return (room->num);
}

int		no_dublicate(t_path *buf, int num)
{
	int		i;

	i = 0;
	while (i < buf->len - 1)
	{
		if (num == buf->way[i]->num)
			return (0);
		i++;
	}
	return (1);
}

int		get_start(t_room *room)
{
	while (!room->start)
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

void		path_lst_del(t_path **path)
{
	t_path	*buf;

	while (*path)
	{
		buf = *path;
		*path = (*path)->next;
		free(buf->way);
		free(buf);
	}
}

int		get_path(t_room *room, t_path **answer)
{
	t_path	*path;
	t_path  *buf;
	t_link  *buf_child;

	path = NULL;
	push_tail(&path, NULL, get_room(room, get_start(room)), 0);
	while (path)
	{
		buf = pop_path(&path);
		if (buf->way[buf->len - 1]->end)
		{
			push_bottom_path(answer, &buf);
			ft_null_room(room);
			path_lst_del(&path);
			return (1);
		}
		buf_child = get_link(room, buf);
		while (buf_child)
		{
			if (buf_child->conflict && no_dublicate(buf, buf_child->room->num))
			{
				if (buf->status == 0 && buf_child->room->suur == 0)
					push_tail(&path, &buf, buf_child->room, 0);
				else if (buf->status == 0 && buf_child->room->suur == 1)
					push_tail(&path, &buf, buf_child->room, 1);
				else if (buf->status == 1 && buf_child->room->suur == 1)
					push_tail(&path, &buf, buf_child->room, 2);
				else if (buf->status == 2 && buf_child->room->suur == 1)
					push_tail(&path, &buf, buf_child->room, 2);
				else if (buf->status == 2 && buf_child->room->suur == 0)
					push_tail(&path, &buf, buf_child->room, 0);
			}
			buf_child = buf_child->next;
		}
		free(buf->way);
		free(buf);
	}
	ft_null_room(room);
	path_lst_del(&path);
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
			buf = tmp->way[i]->link;
			while (buf->room->num != tmp->way[i + 1]->num)
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

void	set_room_sur(t_room *room, t_path *tmp)
{
	int		i;

	while (tmp)
	{
		i = 0;
		while (i < tmp->len)
		{
			tmp->way[i]->suur = 1;
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
			increase_vertex(&vertex, buf->way[i]->num);
			i++;
		}
		buf = buf->next;
	}
	while (answer)
	{
		i = 1;
		while (i < answer->len - 2)
		{
			if (get_vertex(vertex, answer->way[i]->num)->op > 0 &&
				get_vertex(vertex, answer->way[i + 1]->num)->op > 0)
			{
				tmp = answer->way[i]->link;
				while (tmp && tmp->room->num != answer->way[i + 1]->num)
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
			answer->way[i]->visit = 1;
			i++;
		}
		answer = answer->next;
	}
}

void	search_path(t_room *room, t_path **answer)
{
	t_path	*tmp;
	int		j;

	get_path(room, answer);
	while (length_path(*answer) < ft_limit_path(room))
	{
		tmp = *answer;
		delete_links(room, tmp, 0);
		set_room_sur(room, tmp);
		if (!get_path(room, answer))
			break;
		set_def_links(room);
		if (!build_new_links(*answer, room))
		{
			set_def_links(room);
			continue;
		}
		j = length_path(*answer);
		path_lst_del(answer);
		while (j)
		{
			if (!get_path(room, answer))
				return ;
			set_visit_path(room, *answer);
			j--;
		}
		set_def_links(room);
	}
}
