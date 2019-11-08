/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_input.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bford <bford@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 12:48:42 by bford             #+#    #+#             */
/*   Updated: 2019/11/07 15:30:52 by bford            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_input		*ft_lstnew_input(char *s)
{
	t_input		*list_input;

	if (!s || !(list_input = (t_input *)malloc(sizeof(t_input))))
		return (NULL);
	list_input->s = s;
	list_input->next = NULL;
	return (list_input);
}
