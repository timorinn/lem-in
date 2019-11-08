/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_ant.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bford <bford@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 20:41:26 by bford             #+#    #+#             */
/*   Updated: 2019/11/06 20:45:58 by bford            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_ant		*ft_lstnew_ant(int i)
{
	t_ant		*ant;

	if (!(ant = (t_ant *)malloc(sizeof(t_ant))))
		return (NULL);
	ant->num = i;
	ant->room = -1;
	ant->next = NULL;
	return (ant);
}
