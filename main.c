/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bford <bford@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 13:17:03 by bford             #+#    #+#             */
/*   Updated: 2019/11/08 20:05:53 by bford            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	ft_print_input(t_input *input);
void	ft_print_ants(t_ant *ant);
void	ft_print_rooms(t_room *room);

int		main(int argc, char **argv)
{
	t_input		*input;
	t_ant		*ant;
	t_room		*room;

	input = ft_analize_input(argc, argv);
	ant = ft_make_ants(input);
	room = ft_make_rooms(input, ant);
	if (!input || !ant || !room)
		ft_putstr("ERROR\n");
	else
	{
		ft_print_input(input);
		ft_print_ants(ant);
		ft_print_rooms(room);
	}
	return (ft_del_all(input, ant, room));
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

void	ft_print_ants(t_ant *ant)
{
	t_ant	*copy;

	copy = ant;
	ft_putstr("\n******** PRINT ANTS *********\n");
	while (copy)
	{
		ft_putstr("LEM_");
		ft_putnbr(copy->num);
		ft_putchar(' ');
		ft_putnbr(copy->room);
		ft_putchar('\n');
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
		ft_putstr("ROOM_");
		ft_putstr(copy->name);
		ft_putstr(" | x = ");
		ft_putnbr(copy->x);
		ft_putstr(" | y = ");
		ft_putnbr(copy->y);
		ft_putstr(" | start = ");
		ft_putnbr(copy->start);
		ft_putstr(" | end = ");
		ft_putnbr(copy->end);
		ft_putchar('\n');
		copy = copy->next;
	}
}