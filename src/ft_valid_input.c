/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_valid_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bford <bford@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 17:52:58 by bford             #+#    #+#             */
/*   Updated: 2019/11/05 20:09:12 by bford            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

static int	ft_valid_rooms(char **array)
{
	int		i;

	i = 0;
	
	array+=0;
	return (1);
}

char		*ft_valid_input(int argc, char **argv)
{
	char	**array;

	if (argc != 2)
	{
		ft_putstr("Error in argc!\n");
		return (NULL);
	}
	if (!(array = ft_strsplit(argv[1], '\n')))
	{
		ft_putstr("Error in memory!\n");
		return (NULL);
	}
	if (!ft_is_int(array[0]))
	{
		ft_putstr("Error in number of ants!\n");
		free (array);
		return (NULL);
	}
	if (!ft_valid_rooms(array))
	{
		ft_putstr("Error in rooms!\n");
		free (array);
		return (NULL);
	}

	ft_putstr("BCE OK!.... uJlu HeT? . . .\n");
	free(array);
	return ("ok\n");
}
