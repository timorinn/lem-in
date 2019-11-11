/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_link.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bford <bford@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 19:19:31 by bford             #+#    #+#             */
/*   Updated: 2019/11/11 19:21:32 by bford            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_link		*ft_lstnew_link(t_room *room)
{
	t_link		*link;

	if (!room || !(link = (t_link *)malloc(sizeof(t_link))))
		return (NULL);
	link->room = room;
	link->next = NULL;
	return (link);
}
