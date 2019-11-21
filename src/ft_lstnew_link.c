/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_link.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swedde <swedde@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 19:19:31 by bford             #+#    #+#             */
/*   Updated: 2019/11/21 19:14:49 by swedde           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_link		*ft_lstnew_link(t_room *room)
{
	t_link		*link;

	if (!room || !(link = (t_link *)malloc(sizeof(t_link))))
		return (NULL);
	link->room = room;
	link->conflict = 1;
	link->next = NULL;
	return (link);
}
