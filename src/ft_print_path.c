/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swedde <swedde@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 13:10:48 by bford             #+#    #+#             */
/*   Updated: 2019/11/23 21:34:17 by swedde           ###   ########.fr       */
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
				ft_putnbr(copy->way[j]->num);
				ft_putstr(" ");
				j++;
			}
			ft_putstr("\n");
		}
        copy = copy->next;
    }
}