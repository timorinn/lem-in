/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_len_output.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bford <bford@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 13:08:18 by bford             #+#    #+#             */
/*   Updated: 2019/11/14 17:02:07 by bford            ###   ########.fr       */
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
	ant -= paths;
	while (copy)
	{
		max = (max < copy->len - 1 ? copy->len - 1 : max);
		copy = copy->next;
	}

	max = (max > dop - 1 ? max : dop - 1);

	//printf("Max = %d \n", max);

	//ant -= (ant - max > 0 ? max : ant);

	//printf("Ant 1 = %d\n", ant);

	copy = answer;
	while (copy)
	{
		ant -= (max + 1 - copy->len ? max + 1 - copy->len : 0);
		copy = copy->next;
	}

	//printf("Ant 2 = %d\n", ant);

	if (dop > 0)
		ant -= (max + 1 - dop ? max + 1 - dop : 0);
	ant = (ant < 0 ? 0 : ant);

	//printf("Max = %d | Ant = %d\n\n", max, ant);

	return (max + ant / paths + !!(ant % paths));
}
