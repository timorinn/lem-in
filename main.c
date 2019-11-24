/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swedde <swedde@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 13:17:03 by bford             #+#    #+#             */
/*   Updated: 2019/11/25 01:23:38 by swedde           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

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

	input = ft_analize_input(argc, argv);
	room = ft_make_rooms(input);
	if (!input || !room)
	{
		ft_putstr("ERROR\n");
		ft_del_all(input, room);
		return (0);
	}
	path = NULL;
	search_path(room, &path);
//	ft_print_path(path, "CREATE\n");
//	sort_path(&path);
//	ft_print_path(path, "SORT\n");
//	reposition_path(&path);
//	ft_print_path(path, "REPOSITION\n");
	if (path)
	{
		steps_print(path, room);
		path_lst_del(&path);
	}
	return (0);
}
