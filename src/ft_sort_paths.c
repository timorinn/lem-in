/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_paths.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bford <bford@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 14:49:25 by bford             #+#    #+#             */
/*   Updated: 2019/11/14 17:56:18 by bford            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_path		*ft_copy_path(t_path *answer);
static int	ft_max_len(t_path *answer);
static int	ft_len_path(t_path *itog);
static int	ft_different(t_path *path1, t_path *path2);
int			ft_add_last_path(t_path **itog, t_path *last);
t_path		*ft_copy_path(t_path *answer);
int			ft_rec_find(t_path **itog, t_path *answer, int ant, int limit);

static int	ft_max_len(t_path *answer)
{
	int		max;

	max = -1;
	while (answer)
	{
		if (max < answer->len)
			max = answer->len;
		answer = answer->next;
	}
	return (max);
}

static int	ft_len_path(t_path *itog)
{
	int		len;

	len = 0;
	while (itog && ++len)
		itog = itog->next;
	return (len);
}

static int	ft_different(t_path *path1, t_path *path2)
{
	int		len1;
	int		len2;
	int		*ar1;
	int		*ar2;
	int		copy;

	len2 = path2->len - 1;
	ar2 = path2->way;
	copy = len2;
	while (path1)
	{
		len1 = path1->len - 1;
		ar1 = path1->way;
		while (--len1 > 0)
		{
			len2 = copy;
			while (--len2 > 0)
			{
				if (ar1[len1] == ar2[len2])
					return (1);
			}
		}
		path1 = path1->next;
	}
	return (0);
}

int			ft_add_last_path(t_path **itog, t_path *last)
{
	t_path	*copy;

	copy = *itog;
	if (!(*itog))
		return ((*itog = ft_copy_path(last)) ? 1 : 0);
	while (copy->next)
		copy = copy->next;
	return ((copy->next = ft_copy_path(last)) ? 1 : 0);
}

t_path		*ft_copy_path(t_path *answer)
{
	t_path	*itog;
	int		len;
	int		i;

	i = 0;
	len = answer->len;
	if (!(itog = (t_path *)malloc(sizeof(t_path))))
		return (NULL);
	if (!(itog->way = (int *)malloc(sizeof(int) * answer->len)))
		return (NULL);
	while (i < len)
	{
		itog->way[i] = answer->way[i];
		i++;
	}
	itog->num = answer->num;
	itog->len = answer->len;
	itog->next = NULL;
	return (itog);
}

void		ft_del_last_path(t_path **itog)
{
	t_path	*copy;
	t_path	*prev;

	prev = NULL;
	copy = *itog;
	if (!itog || !copy)
		return ;
	if (ft_len_path(*itog) == 1)
	{
		free((*itog)->way);
		(*itog)->way = NULL;
		free(*itog);
		*itog = NULL;
		itog = NULL;
		return ;
	}
	while (copy->next)
	{
		prev = copy;
		copy = copy->next;
	}
	free(copy->way);
	copy->way = NULL;
	free(copy);
	copy = NULL;
	if (prev)
		prev->next = NULL;
}

int		ft_rec_find(t_path **itog, t_path *answer, int ant, int limit)
{
	t_path	*copy;

	copy = answer;
	if (ft_len_path(*itog) == limit)
		return (1);
	while (copy)
	{
		/*
		if (*itog)
			printf("WHILE : LO_1 = %d | LO_2 = %d\n",
			ft_len_output(*itog, ant, 0),
			ft_len_output(*itog, ant, copy->len));
		*/

		/*
		if (*itog)
			ft_print_path(*itog, "While itog\n");
		*/


		if (
			
		!(*itog) ||
		(ft_len_output(*itog, ant, 0) >
		ft_len_output(*itog, ant, copy->len) &&
			
		!ft_different(*itog, copy) )
		)
		{
			if (!ft_add_last_path(itog, copy))
				return (0);
			if (ft_rec_find(itog, answer, ant, limit))
				return (1);
			ft_del_last_path(itog);
		}
		copy = copy->next;
	}
	return (0);
}

t_path		*ft_sort_paths(t_path *answer, int ant, int limit)
{
	int		max;
	t_path	*itog;

	itog = NULL;
	max = ft_max_len(answer);
	printf("START RECURSION!\n");
	if (!ft_rec_find(&itog, answer, ant, limit) ||
	(ft_len_path(itog) < limit &&
	ft_len_output(itog, ant, 0) > ft_len_output(itog, ant, max)))
	{
		ft_lstdel_path(itog);
		return (NULL);
	}

	ft_print_path(itog, "___final_itog\n");
	//printf("LO_1 = %d | LO_2 = %d\n",
	//ft_len_output(itog, 2, 0), ft_len_output(itog, 2, 0));

	printf("\n******** OUTPUT_LEN *********\n"); 
	printf("Len_output = %d\n\n", ft_len_output(itog, ant, 0));

	return (itog);
}
