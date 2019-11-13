/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_paths.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bford <bford@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 14:49:25 by bford             #+#    #+#             */
/*   Updated: 2019/11/13 22:27:04 by bford            ###   ########.fr       */
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
				//printf("ar1[%d] = %d | ar2[%d] = %d\n",
				//len1, ar1[len1], len2, ar2[len2]);
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
/*
	printf("DelCopy\n");
	ft_print_itog(copy);
	printf("DelItog\n");
	ft_print_itog(itog);
*/
	free(copy->way);
	copy->way = NULL;
	free(copy);
	copy = NULL;
	if (prev)
		prev->next = NULL;
	/*
	printf("Prev\n");
	ft_print_itog(prev);
	printf("PrevItog\n");
	ft_print_itog(*itog);
	*/

}

int		ft_rec_find(t_path **itog, t_path *answer, int ant, int limit)
{
	t_path	*copy;

	copy = answer;
	if (ft_len_path(*itog) == limit)
		return (1);
/*
	printf("Copy\n");
	ft_print_itog(copy);
	printf("Itog\n");
	ft_print_itog(*itog);
*/
	while (copy)
	{
		if (!ft_different(*itog, copy))
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
	if (!ft_rec_find(&itog, answer, ant, limit)) // && ft_len_path(itog) < limit)
		return (NULL);

	printf("Final itog\n");
	ft_print_itog(itog);

	return (itog);
}














static void		ft_print_itog(t_path *itog)
{
	int j;
	t_path *copy;

	copy = itog;
	if (!itog)
		ft_putstr("No itog!\n");
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
        copy = copy->next;
    }
}