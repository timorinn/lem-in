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

t_path	*new_lst_path(t_path **buf, int num)
{
	t_path	*new;

	if (!(new = (t_path *)malloc(sizeof(t_path))))
		return (NULL);
	if (!(new->way = concat_way(buf, num)))
		return (NULL + ft_lstdel_path(new));
	new->next = NULL;
	new->len = (*buf)->len + 1;
	return (new);
}

int		push_tail(t_path **start, t_path **buf, int num)
{
	t_path	*temp;

	if (*start == NULL && buf == NULL)
	{
		if (!(*start = (t_path *)malloc(sizeof(t_path))))
			return (ft_lstdel_path(*buf));
		if (!((*start)->way = (int *)malloc(sizeof(int))))
			return (ft_lstdel_path(*start) + ft_lstdel_path(*buf));
		(*start)->next = NULL;
		(*start)->len = 1;
		(*start)->way[0] = num;
	}
	else if (*start == NULL && *buf != NULL)
	{
		if (!(*start = new_lst_path(buf, num)))
			return (ft_lstdel_path(*start) + ft_lstdel_path(*buf));
	}
	else
	{
		temp = *start;
		while (temp->next)
			temp = temp->next;
		if (!(temp->next = new_lst_path(buf, num)))
			return (ft_lstdel_path(*start) + ft_lstdel_path(*buf));
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
	return (*l && (*l)->way[(*l)->len - 1] == end ? 1 : 0);
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

int	ft_len_path(t_path *itog)
{
	int		len;

	len = 0;
	while (itog && ++len)
		itog = itog->next;
	return (len);
}

static t_room	*get_room(t_room *room, int num)
{
	while (room->num != num)
		room = room->next;
	return (room);
}

void	ft_null_room(t_room *room, t_path *answer)
{
	int i;
	t_room	*copy;

	copy = room;
	while (room)
	{
		room->visit = 0;
		room = room->next;
	}
	while (answer)
	{
		i = 1;
		while (i < answer->len - 1)
		{
			get_room(copy, answer->way[i])->visit = 1;
			i++;
		}
		answer = answer->next;
	}
}

int		get_path(t_room *room, t_path **answer)
{
	t_path	*path;
	t_path  *buf;
	t_link  *buf_child;
	int		end;
	int		start;
	int		ant;

	start = get_start(room);
	ant = ft_get_ant(room);
	end = get_end(room);
	path = NULL;

	push_tail(&path, NULL, start);
	while (path)
	{
/*		while (1)
		{*/
			buf = pop_path(&path);
			if (buf && ended_path(&buf, end))
			{
				buf->next = NULL;
				push_bottom_path(answer, &buf);
				ft_null_room(room, *answer);
				return (1);
			//	continue;
			}
/*			break;
		}*/
		if (!buf)
			break;
		buf_child = get_link(room, buf);
		while (buf_child)
		{
			if (no_dublicate(buf, buf_child))
			{
				push_tail(&path, &buf, buf_child->room->num);
			}
			buf_child = buf_child->next;
		}
		if (buf)
		{
			free(buf->way);
			free(buf);
		}
	}
	return (0);
}
