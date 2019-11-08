/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isint.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bford <bford@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 16:28:32 by bford             #+#    #+#             */
/*   Updated: 2019/11/07 15:39:57 by bford            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check_last(const char *s, int last)
{
	if (last == 1)
	{
		while (*s == ' ' || (*s >= 9 && *s <= 13))
			s++;
		return (*s ? 1 : 0);
	}
	else if (last == 2)
	{
		return (*s ? 1 : 0);
	}
	return (0);
}

int			ft_isint(const char *s, int sign, int first, int last)
{
	int		len;
	int		znak;

	znak = 0;
	len = 0;
	if (!s)
		return (0);
	if (first && !(ft_isdigit(*s) || *s == '-'))
		return (0);
	while (*s == ' ' || (*s >= 9 && *s <= 13))
		s++;
	if ((sign == -1 && *s != '-') || (sign == 1 && *s == '-'))
		return (0);
	if (*s == '-' || *s == '+')
		znak += *s++ == '-' ? 1 : 0;
	if (*s == '0' && len++)
		while (*s == '0')
			s++;
	if (ft_isdigit(*s) && s++)
		len += (!len ? 1 + znak : znak);
	while (*s && ft_isdigit(*s) && len++)
		s++;
	if (last && ft_check_last(s, last))
		return (0);
	return (len == ft_nbr_len(ft_atoi(s - len)));
}
