/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bford <bford@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 17:54:19 by bford             #+#    #+#             */
/*   Updated: 2019/11/10 20:12:47 by bford            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include <fcntl.h>
# include "../libft/libft.h"

#include <stdio.h>

typedef struct		s_input
{
	char			*s;
	struct s_input	*next;
}					t_input;

typedef struct		s_room
{
	char			*name;
	int				x;
	int				y;
	int				num;
	int				ant;
	int				start;
	int				end;
	struct s_room	*next;
}					t_room;

typedef struct		s_params
{
	int		num;
	int		startend;
	int		ants;
	int		links;
	char	*name;
}					t_params;


t_input		*ft_analize_input(int argc, char **argv);
t_input		*ft_lstnew_input(char *s);
int			ft_lstdel_input(t_input *list);
int			ft_del_all(t_input *input, t_room *room);
t_room		*ft_make_rooms(const t_input *input);
t_room		*ft_lstnew_room(char *name, int x, int y, t_params *par);

#endif