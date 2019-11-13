/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_len_output.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bford <bford@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 13:08:18 by bford             #+#    #+#             */
/*   Updated: 2019/11/13 17:36:25 by bford            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

#include "stdio.h" //

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
		if (max < copy->len)
			max = copy->len;
		copy = copy->next;
	}
	max = (max > dop ? max : dop);
	ant -= max;
	copy = answer;
	while (copy)
	{
		ant -= (max - copy->len ? max - copy->len : 1);
		copy = copy->next;
	}
	if (dop > 0)
		ant -= (max - dop ? max - dop : 1);
	return (max + ant / paths + !!(ant % paths));
}
