/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_analize_input.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsheev <nsheev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 15:35:06 by bford             #+#    #+#             */
/*   Updated: 2019/11/18 19:57:59 by nsheev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static t_input	*ft_make_list_input(int fd)
{
	t_input		*input;
	t_input		*copy;
	char		*line;

	input = NULL;
	while (get_next_line(fd, &line, 0))
	{
		if (!input)
		{
			if ((!(input = ft_lstnew_input(line)) &&
			get_next_line(0, NULL, 1)) ||
			!(copy = input))
				return (NULL);
		}
		else
		{
			if ((!(copy->next = ft_lstnew_input(line)) &&
			get_next_line(0, NULL, 1)) ||
			!(copy = copy->next))
				return (NULL);
		}
	}
	get_next_line(0, NULL, 1);
	//close (fd);
	return (input);
}

t_input		*ft_analize_input(int argc, char **argv)
{
	t_input		*input;
	int			fd;

	//if (argc != 2 || (fd = open(argv[1], O_RDONLY)) == -1)
	//	return (NULL);
	argc+=0;argv+=0;
	fd = 0;
	input = ft_make_list_input(fd);
	return (input);
}
