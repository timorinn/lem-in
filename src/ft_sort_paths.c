/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_paths.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bford <bford@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 14:49:25 by bford             #+#    #+#             */
/*   Updated: 2019/11/13 19:23:19 by bford            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_path		*ft_copy_path(t_path *answer);
static int	ft_max_len(t_path *answer);
static int	ft_len_path(t_path *itog);
static int	ft_different(t_path *path1, t_path *path2);
int			ft_add_last_path(t_path *itog, t_path *last);
t_path		*ft_copy_path(t_path *answer);
t_path		*ft_rec_find(t_path *itog, t_path *answer, int ant, int limit);
static void	ft_print_itog(t_path *itog);

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

	len2 = path2->len;
	ar2 = path2->way;
	while (path1)
	{
		len1 = path1->len;
		ar1 = path1->way;
		copy = len2;
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

int			ft_add_last_path(t_path *itog, t_path *last)
{
	while (itog->next)
		itog = itog->next;
	return (!(itog->next = ft_copy_path(last)) ? 0 : 1);
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

t_path		*ft_rec_find(t_path *itog, t_path *answer, int ant, int limit)
{
	if (ft_len_path(itog) == limit)
		return (itog);
	while (answer)
	{
		if (!itog && !(itog = ft_copy_path(answer)))
			return (NULL);
		if (!ft_different(itog, answer))
		{
			if (!ft_add_last_path(itog, answer))
				return (NULL);
			//if (ft_len_path(itog) == limit)
			//	return (itog);
			if (!(itog = ft_rec_find(itog, answer, ant, limit)))
				return (NULL);
		}
		answer = answer->next;
	}
	return (itog);
}

t_path		*ft_sort_paths(t_path *answer, int ant, int limit)
{
	int		max;
	t_path	*itog;

	itog = NULL;
	max = ft_max_len(answer);
	//printf("SORT | ant = %d | max = %d | limit = %d\n", ant, max, limit);
	if ((itog = ft_rec_find(itog, answer, ant, limit)) && ft_len_path(itog) < limit)
	{
		//if (ft_len_output(itog, ant, 0) < ft_len_output(itog, ant, max))
		//	return (NULL);
		itog+=0;
	}
	ft_print_itog(itog);
	return (itog);
}














static void		ft_print_itog(t_path *itog)
{
	int j;
	int i = 1;
	t_path *copy;

	copy = itog;
	ft_putstr("\nI T O G ! \n");
	while (copy)
	{
   		j = 0;
		while (j < copy->len)
		{
			ft_putnbr(copy->way[j]);
			ft_putstr(" ");
			j++;
		}
		ft_putstr("\n");
        i++;
        copy = copy->next;
    }
}