/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bford <bford@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 13:10:48 by bford             #+#    #+#             */
/*   Updated: 2019/11/14 14:43:01 by bford            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		ft_print_path(t_path *path, char *s)
{
	int j;
	t_path *copy;

	copy = path;
	if (!path)
		return ;
	ft_putstr(s);
	while (copy)
	{
   		j = 0;
		if (copy->way)
		{
			while (j < copy->len)
			{
				ft_putnbr(copy->way[j]);
				ft_putstr(" ");
				j++;
			}
			ft_putstr("\n");
		}
        copy = copy->next;
    }
}