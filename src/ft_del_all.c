/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_del_all.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bford <bford@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 14:03:16 by bford             #+#    #+#             */
/*   Updated: 2019/11/11 15:56:42 by bford            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void	ft_del_input(t_input *input)
{
	t_input	*copy;

	while (input)
	{
		if (input->s)
			ft_strdel(&(input->s));
		copy = input->next;
		free(input);
		input = copy;
	}
}

static void	ft_del_room(t_room *room)
{
	t_room	*copy;

	while (room)
	{
		ft_strdel(&(room->name));
		copy = room->next;
		free(room);
		room = copy;
	}
}

int			ft_del_all(t_input *input, t_room *room)
{
	ft_del_input(input);
	ft_del_room(room);
	return (0);
}
