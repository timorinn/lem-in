/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reposition_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swedde <swedde@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 23:08:29 by swedde            #+#    #+#             */
/*   Updated: 2019/11/20 23:49:56 by swedde           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		have_conflict(t_path *answer)
{
	while (answer)
	{
		if (answer->conflict)
			return (1);
		answer = answer->next;
	}
	return (0);
}

t_vertex	*new_vertex(int num)
{
	t_vertex *a;

	a = (t_vertex*)malloc(sizeof(t_vertex));
	if (!a)
		return (NULL);
	a->next = NULL;
	a->num = num;
	a->op = -1;
	return (a);
}

void		increase_vertex(t_vertex **vertex, int num)
{
	t_vertex *l;

	if (!*vertex)
		*vertex = new_vertex(num);
	l = *vertex;
	while (l->next)
	{
		if (l->num == num)
			break;
		l = l->next;
	}
	if (l->num != num)
	{
		l->next = new_vertex(num);
		l = l->next;
	}
	l->op++;
}

t_vertex	*get_vertex(t_vertex *vertex, int num)
{
	while (vertex->num != num)
		vertex = vertex->next;
	return (vertex);
}

void		set_way_conflict(t_path *answer, t_vertex *vertex)
{
	int i;

	while (answer)
	{
		answer->conflict = 0;
		i = 1;
		while (i < answer->len - 1)
		{
			answer->conflict += get_vertex(vertex, answer->way[i])->op;
			i++;
		}
		answer = answer->next;
	}
}

void		del_conflict_path(t_path **answer, int max, int pos)
{
	t_path	*buf;
	t_path	*tmp;
	
	while (pos > -1)
	{
		if ((*answer)->conflict == max)
		{
			if (pos == 0)
			{
				buf = *answer;
				*answer = (*answer)->next;
				free(buf->way);
				free(buf);
			}
			else
				(*answer)->conflict--;
		}
		else
		{
			tmp = *answer;
			while (tmp->next->conflict != max)
				tmp = tmp->next;
			if (pos == 0)
			{
				buf = tmp->next;
				tmp->next = tmp->next->next;
				free(buf->way);
				free(buf);
			}
			else
				tmp->next->conflict--;
		}
		pos--;
	}
}

void		delete_max_conflict(t_path **answer)
{
	int		max;
	t_path	*buf;
	int pos;

	max = -1;
	pos = 0;
	buf = *answer;
	while (buf)
	{

		if (buf->conflict == max)
			pos++;
		if (buf->conflict > max)
		{
			pos = 0;
			max = buf->conflict;
		}
		buf = buf->next;
	}
	if (max == 0)
		return ;
	del_conflict_path(answer, max, pos);
}

void		set_default_vertex(t_vertex *vertex)
{
	while (vertex)
	{
		vertex->op = -1;
		vertex = vertex->next;
	}
}

void		vertex_lst_del(t_vertex **vertex)
{
	t_vertex	*buf;

	while (*vertex)
	{
		buf = *vertex;
		*vertex = (*vertex)->next;
		free(buf);
	}
}

void		reposition_path(t_path **answer)
{
	t_vertex	*vertex;
	t_path		*buf;
	int			i;

	vertex = NULL;
	(*answer)->conflict = -1;
	while (have_conflict(*answer))
	{
		buf = *answer;
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
		set_way_conflict(*answer, vertex);
		delete_max_conflict(answer);
		set_default_vertex(vertex);
	}
	vertex_lst_del(&vertex);
}
