/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_analize_input.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bford <bford@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 15:35:06 by bford             #+#    #+#             */
/*   Updated: 2019/11/11 19:24:21 by bford            ###   ########.fr       */
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
		if (!input)
		{
			if ((!(input = ft_lstnew_input(line)) &&
			get_next_line(0, NULL, 1) && close(fd) + 10) ||
			!(copy = input))
				return (NULL);
		}
		else
		{
			if ((!(copy->next = ft_lstnew_input(line)) &&
			get_next_line(0, NULL, 1) && close(fd) + 10) ||
			!(copy = copy->next))
				return (NULL);
		}
	get_next_line(0, NULL, 1);
	close (fd);
	return (input);
}

t_input		*ft_analize_input(int argc, char **argv)
{
	t_input		*input;
	int			fd;

	fd = open(argv[1], O_RDONLY);
	if (argc != 2)
		return (NULL);
	input = ft_make_list_input(fd);
	close(fd);
	return (input);
}
