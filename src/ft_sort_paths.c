/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_paths.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsheev <nsheev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 14:49:25 by bford             #+#    #+#             */
/*   Updated: 2019/11/19 19:23:53 by nsheev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_path		*ft_copy_path(t_path *answer);
static int	ft_len_path(t_path *itog);
static int	ft_different(t_path *path1, t_path *path2);
int			ft_add_last_path(t_path **itog, t_path *last);
t_path		*ft_copy_path(t_path *answer);

int	ft_max_len(t_path *answer)
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
/*
if (!(*itog) ||
		(ft_len_output(*itog, ant, 0) >=
		ft_len_output(*itog, ant, copy->len) &&
		!ft_different(*itog, copy)))
*/
int		ft_rec_find(t_path **itog, t_path *answer, int ant, int limit, int min)
{
	t_path	*copy;

	if (ft_len_path(*itog) == limit)
	{
		printf("САКСЕС<ёт\n");
		return (1);
	}
	copy = answer;
	while (copy)
	{
		if (*itog)
		{
			ft_print_path(*itog, "ITOG !\n");
			printf("Lo 1 = %d | Lo 2 = %d | Dif = %d\n", ft_len_output(*itog, ant, 0),
				ft_len_output(*itog, ant, copy->len), ft_different(*itog, copy));
		}
		ft_print_path(copy, "COPY!\n");
		if (!(*itog) ||
		(ft_len_output(*itog, ant, 0) >=
		ft_len_output(*itog, ant, copy->len) &&
		!ft_different(*itog, copy)))
		{
			if (!ft_add_last_path(itog, copy))
				return (0);
			//if (ft_len_output(*itog, ant, 0) > min)
			//	return (0);
			//min = ft_len_output(*itog, ant, 0);
			if (ft_rec_find(itog, answer, ant, limit, min))
				return (1);
			ft_del_last_path(itog);
		}
		copy = copy->next;
	}
	printf("{ end }\n");
	return (0);
}

t_path		*ft_sort_paths(t_path *answer, int ant, int limit)
{
	int		min;
	t_path	*itog;

	min = 2000000000;
	itog = NULL;
	printf("\nSTART RECURSION!\n\n");

	ft_rec_find(&itog, answer, ant, limit, min);
	printf("\nEND RECURSION!\n\n");
	return (itog);
}
