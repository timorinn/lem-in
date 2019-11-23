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

	new = (t_path *)malloc(sizeof(t_path));
	new->way = concat_way(buf, num);
	new->next = NULL;
	new->len = (*buf)->len + 1;
	return (new);
}

int		push_tail(t_path **start, t_path **buf, int num)
{
	t_path	*temp;

	if (*start == NULL && buf == NULL)
	{
		*start = (t_path *)malloc(sizeof(t_path));
		(*start)->way = (int *)malloc(sizeof(int));
		(*start)->next = NULL;
		(*start)->len = 1;
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

t_link	*get_link(t_room *room, t_path *l)
{
	write(1, "01\n", 3);
	while (room->num != l->way[l->len - 1])
		room = room->next;
	if (room->visit)
	{
		write(1, "01\n", 3);
		return (NULL);
	}
	room->visit = 1;
	write(1, "01\n", 3);
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

static int		get_path(t_room *room, t_path **answer, t_path *pattern, int i, int end)
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
			push_bottom_path(answer, &buf);
			ft_null_room(room);
			get_room(room, buf->way[i])->bad_pos = i;
			return (1);
		}
		if (!buf)
			break;
		buf_child = get_link(room, buf->way[buf->len - 1]);
		while (buf_child)
		{
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

t_path	*mal_newlst_path(t_path *answer)
{
	t_path	*l;
	int		i;

	l = (t_path*)malloc(sizeof(t_path));
	l->next = NULL;
	l->len = answer->len;
	l->way = (int*)malloc(sizeof(int) * answer->len);
	i = 0;
	while (i < l->len)
	{
		l->way[i] = answer->way[i];
		i++;
	}
	return (l);
}

void	mal_copy_path(t_path **buf, t_path *answer)
{
	t_path	*tmp;

	if (!*buf)
	{
		*buf = mal_newlst_path(answer);
	}
	else
	{
		tmp = *buf;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = mal_newlst_path(answer);
	}
}

void		set_default_conflict(t_path *vertex)
{
	while (vertex)
	{
		vertex->conflict = 0;
		vertex = vertex->next;
	}
}

int		light_have_conflict(t_path *answer, t_vertex *vertex)
{
	int i;
	int j;

	j = 0;
	while (answer)
	{
		i = 1;
		while (i < answer->len - 1)
		{
			if (get_vertex(vertex, answer->way[i])->op == 0)
				break;
			if (i + 1 == answer->len - 1)
			{
				answer->conflict = 1;
				j++;
			}
			i++;
		}
		answer = answer->next;
	}
	return (j);
}

void		light_delete_max_conflict(t_path **answer, int pos)
{
	t_path	*buf;
	t_path	*tmp;
	
	while (pos > 0)
	{
		if ((*answer)->conflict == 1)
		{
			if (pos == 1)
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
			while (tmp->next->conflict != 1)
				tmp = tmp->next;
			if (pos == 1)
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

void		light_reposition_path(t_path **answer)
{
	t_vertex	*vertex;
	t_path		*buf;
	int			i;
	int			j;

	vertex = NULL;
	set_default_vertex(vertex);
	buf = *answer;
	set_default_conflict(buf);
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
	while (j = light_have_conflict(*answer, vertex))
	{
		light_delete_max_conflict(answer, j);
		set_default_vertex(vertex);
		buf = *answer;
		set_default_conflict(buf);
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
	}
	vertex_lst_del(&vertex);
}

int		stop_search(t_path **path, int limit)
{
	t_path	*buf;
	t_path	*answer;

	sort_path(path);
	light_reposition_path(path);
	buf = NULL;
	answer = *path;
	while (answer)
	{
		mal_copy_path(&buf, answer);
		answer = answer->next;
	}
	reposition_path(&buf);
	printf("len = %d\n", length_path(buf));
	if (length_path(buf) >= limit)
		return (1);
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
	t_room	*clean;
	int		end;
	int		i;
	int		j;
	int		limit;

	limit = ft_limit_path(room);
	end = get_end(room);
	path = NULL;
	push_tail(&path, NULL, get_start(room));
	get_path(room, answer, path, 0, end);
	i = 1;\
	while (stop_cycle(*answer, i) && limit > 1)
	{
	//	if (stop_search(answer, limit))
	//		break;
		j = length_path(*answer);
		buf = *answer;
		while (j)
		{
			while (get_path(room, answer, buf, i, end))
				;
			ft_print_path(*answer, "end cycle\n");
			j--;
			clean = room;
			while (clean)
			{
				clean->bad_pos = 0;
				clean = clean->next;
			}
			buf = buf->next;
		}
		printf("BIG CYCLE EBD\n");\
		i++;
	}
}
