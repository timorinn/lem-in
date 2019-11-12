#include "lemin.h"

int		*concat_way(t_path **l, int num)
{
	int		*a;
	int		i;

	a = (int*)malloc(sizeof(int) * (*l)->len + 1);
	i = 0;
	while (i < (*l)->len)
	{
		a[i] = (*l)->way[i];
		i++;
	}
	a[i] = num;
	return (a);
}

t_path	*new_lst_path(t_path **buf, int num)
{
	t_path	*l;

	l = (t_path*)malloc(sizeof(t_path));
	l->next = NULL;
	l->len = (*buf)->len + 1;
	l->way = concat_way(buf, num);
	return (l);
}

void	push_tail(t_path **start, t_path **buf, int num)
{
	t_path	*temp;

	if (*start == NULL && buf == NULL)
	{
		*start = (t_path*)malloc(sizeof(t_path));
		(*start)->next = NULL;
		(*start)->len = 1;
		(*start)->way = (int*)malloc(sizeof(int));
		(*start)->way[0] = num;
	}
	else if (*start == NULL && *buf != NULL)
	{
		*start = new_lst_path(buf, num);
	}
	else
	{
		temp = *start;
		while (temp->next)
			temp = temp->next;
		temp->next = new_lst_path(buf, num);
	}
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
	if (*l && (*l)->way[(*l)->len - 1] == end)
		return (1);
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
	while(i < buf->len)
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

t_path  *get_path(t_room *room, int limit)
{
	t_path	*path;
	t_path  *buf;
	t_link  *buf_child;
	int		i;
	t_path	*answer;
	int		end;
	int		start;

	int j;

	limit += 0;

	start = get_start(room);
	end = get_end(room);
	path = NULL;
	answer = NULL;
	push_tail(&path, NULL, start);
	while (path)
	{
		while (1)
		{
			buf = pop_path(&path);
			if (buf && ended_path(&buf, end))
			{
				buf->next = NULL;
				push_bottom_path(&answer, &buf);
				continue;
			}
			break;
		}
		if (!buf)
			break;
		buf_child = get_link(room, buf);
		while(buf_child)
		{
			if (no_dublicate(buf, buf_child))
				push_tail(&path, &buf, buf_child->room->num);
			buf_child = buf_child->next;
		}
	}
    i = 1;
    path = answer;
    while (answer)
    {
        answer->num = i;
		j = 0;
		while (j < answer->len)
		{
			ft_putnbr(answer->way[j]);
			ft_putstr(" ");
			j++;
		}
		ft_putstr("\n");
        i++;
        answer = answer->next;
    }
	return (path);
}
