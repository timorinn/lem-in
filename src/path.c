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

void	ft_null_room(t_room *room)
{
	while (room)
	{
		room->visit = 0;
		room = room->next;
	}
}

t_path	*set_new_pattern(t_path **l, int i)
{
	t_path *a;

	if (i == 0)
		return (*l);
	a = (t_path*)malloc(sizeof(t_path));
	a->next = NULL;
	a->len = i;
	a->way = (int*)malloc(sizeof(int) * i);
	while (i - 1 > -1)
	{
		a->way[i - 1] = (*l)->way[i - 1];
		i--;
	}
	return (a);
}

int		get_path(t_room *room, t_path **answer, t_path *pattern, int i, int end)
{
	t_path	*path;
	t_path  *buf;
	t_link  *buf_child;

	path = NULL;
	if (i != 0)
	{
		if (pattern->len <= i)
			return (0);
		get_room(room, pattern->way[i])->bad_pos = i;
		buf = set_new_pattern(&pattern, i);
		push_bottom_path(&path, &buf);
	//	ft_print_path(path, "path\n");
	//	printf("bad pos start = %d\n", pattern->way[i]);
	}
	else
	{
		path = pattern;
	}
	while (path)
	{
		buf = pop_path(&path);
		if (buf && ended_path(&buf, end))
		{
			buf->next = NULL;
		//	ft_print_path(buf, "pushim\n");
			push_bottom_path(answer, &buf);
			ft_null_room(room);
			get_room(room, buf->way[i])->bad_pos = i;
		//	printf("bad pos end = %d\n", buf->way[i]);
			return (1);
		}
		if (!buf)
			break;
		buf_child = get_link(room, buf);
		while (buf_child)
		{
		//	printf("buf child bad pos = %d, room = %d\n", buf_child->room->bad_pos, buf_child->room->num);
			if (no_dublicate(buf, buf_child) && buf_child->room->bad_pos != buf->len)
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
	ft_null_room(room);
	return (0);
}

int		check_dif(t_path *one, t_path *two)
{
	int i;
	int j;

	i = 1;
	while (i < one->len - 1)
	{
		j = 1;
		while (j < two->len - 1)
		{
			if (one->way[i] == two->way[j])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int		stop_search(t_path *answer, int limit)
{
	t_path	*tmp;
	t_path	*buf;
	int		z;

	tmp = answer;
	while (tmp)
	{
		buf = answer;
		z = 0;
		while (buf)
		{
			if (check_dif(tmp, buf))
				z++;
			buf = buf->next;
		}
		if (z >= limit)
			return (z);
		tmp = tmp->next;
	}
	return (0);
}

int		stop_cycle(t_path *answer, int i)
{
	int j;

	j = 0;
	while (answer)
	{
		if (i < answer->len)
			j++;
		answer = answer->next;
	}
	return (j);
}

void	create_path(t_room *room, t_path **answer)
{
	t_path	*path;
	t_path  *buf;
//	t_link  *tmp;
	t_room	*clean;
	int		end;
	int		i;
	int		j;
	int		limit;

	limit = ft_limit_path(room) + 5;
	printf("limit = %d\n", limit);
	end = get_end(room);
	path = NULL;
	push_tail(&path, NULL, get_start(room));
	get_path(room, answer, path, 0, end);
	i = 1;
/*	j = -1;
	tmp = get_room(room, get_start(room))->link;
	while (tmp)
	{
		j++;
		tmp = tmp->next;
	}*/
	j = 1;
//	printf("i = %d, j = %d\n", 0, j);
	while (!stop_search(*answer, limit) && stop_cycle(*answer, i))
	{
		buf = *answer;
		while (j)
		{
		//	printf("i = %d, j = %d\n", i, j);
			while (get_path(room, answer, buf, i, end))
				;
			j--;
		//	ft_print_path(*answer, "cicle end\n");
		//	printf("z = %d\n", stop_search(*answer, limit));
			clean = room;
			while (clean)
			{
				clean->bad_pos = 0;
				clean = clean->next;
			}
			buf = buf->next;
		}
		j = ft_len_path(*answer);
		i++;
	}
}