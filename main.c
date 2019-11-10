/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bford <bford@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 13:17:03 by bford             #+#    #+#             */
/*   Updated: 2019/11/10 20:21:01 by bford            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	ft_print_input(t_input *input);
void	ft_print_rooms(t_room *room);

int		main(int argc, char **argv)
{
	t_input		*input;
	t_room		*room;

	input = ft_analize_input(argc, argv);
	room = ft_make_rooms(input);
	if (!input || !room)
		ft_putstr("ERROR\n");
	else
	{
		ft_print_input(input);
		ft_print_rooms(room);
	}
	return (ft_del_all(input, room));
}





















/***********************************/
/*		FUNCTIONS FOR CHECK		   */
/***********************************/

void	ft_print_input(t_input *input)
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

void	ft_print_rooms(t_room *room)
{
	t_room	*copy;

	copy = room;
	ft_putstr("\n******** PRINT ROOMS ********\n");
	while (copy)
	{
		/*
		ft_putstr("ROOM_");
		ft_putstr(copy->name);
		ft_putstr(" | num = ");
		ft_putnbr(copy->num);
		ft_putstr(" | x = ");
		ft_putnbr(copy->x);
		ft_putstr(" | y = ");
		ft_putnbr(copy->y);
		ft_putstr(" | start = ");
		ft_putnbr(copy->start);
		ft_putstr(" | end = ");
		ft_putnbr(copy->end);
		ft_putstr(" | ant = ");
		ft_putnbr(copy->ant);
		ft_putchar('\n');
		*/
		printf("Room_%8s | num = %2d | ants = %4d | start = %3d | end = %3d\n",
		copy->name, copy->num, copy->ant, copy->start, copy->end);
		copy = copy->next;
	}
}