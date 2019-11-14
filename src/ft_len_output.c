/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_len_output.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bford <bford@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 13:08:18 by bford             #+#    #+#             */
/*   Updated: 2019/11/14 14:00:52 by bford            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		ft_len_output(t_path *answer, int ant, int dop)
{
	t_path	*copy;
	int		max;
	int		paths;

	paths = (dop > 0 ? 1 : 0);
	copy = answer;
	max = -1;
	while (copy && ++paths)
		copy = copy->next;
	copy = answer;
	while (copy)
	{
		max = (max < copy->len ? copy->len : max);
		copy = copy->next;
	}
	max = (max > dop ? max : dop);
	ant -= (ant - max + 1 > 0 ? max - 1 : ant);
	copy = answer;
	while (copy)
	{
		ant -= (max - copy->len ? max - copy->len - 1 : 0);
		copy = copy->next;
	}
	if (dop > 0)
		ant -= (max - dop ? max - dop : 0);
	return (max - 1 + ant / paths + !!(ant % paths));
}
