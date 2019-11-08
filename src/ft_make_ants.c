/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_ants.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bford <bford@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 15:04:25 by bford             #+#    #+#             */
/*   Updated: 2019/11/08 15:04:35 by bford            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_ant	*ft_make_ants(t_input *input)
{
	t_ant	*ant;
	t_ant	*copy;
	int		num;
	int		i;

	i = 1;
	if (!input || !(ft_isint(input->s, 1, 1, 2) && ft_atoi(input->s)) ||
	!(ant = ft_lstnew_ant(0)))
		return (NULL);
	copy = ant;
	num = ft_atoi(input->s) - 1;
	while (num--)
	{
		if (!(ant->next = ft_lstnew_ant(i++)))
		{
			ft_del_all(NULL, copy, NULL);
			return (NULL);
		}
		ant = ant->next;
	}
	ant = copy;
	return (ant);
}
