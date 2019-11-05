/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bford <bford@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 13:24:49 by bford             #+#    #+#             */
/*   Updated: 2019/11/05 17:23:20 by bford            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>

typedef struct		s_rooms
{
	int				lemn;
	int				roomn;
	struct s_rooms	*next;
}					t_rooms;

int				ft_putstr(const char *s);
size_t			ft_strlen(const char *s);

#endif