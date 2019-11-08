/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel_input.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bford <bford@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 12:52:53 by bford             #+#    #+#             */
/*   Updated: 2019/11/06 14:39:04 by bford            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		ft_lstdel_input(t_input *list)
{
	t_input		*next;
	while (list)
	{
		if (list->s)
			ft_strdel(&(list->s));
		next = list->next;
		free(list);
		list = next;
	}
	return (0);
}
