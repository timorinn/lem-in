/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swedde <swedde@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 17:54:19 by bford             #+#    #+#             */
/*   Updated: 2019/11/15 00:14:54 by swedde           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include <fcntl.h>
# include "../libft/libft.h"

#include <stdio.h> // DE LE T E !

struct		t_link;
struct		s_input;
struct		s_room;
struct		s_params;

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
	int				ant_num;
	struct s_link	*link;
	struct s_room	*next;
}					t_room;

typedef struct		s_link
{
	struct s_room	*room;
	struct s_link	*next;
}					t_link;

typedef struct		s_params
{
	int				num;
	int				startend;
	int				ants;
	int				links;
	char			*name;
}					t_params;

typedef struct		s_path
{
	int				step_ants;
	int				len;
	int				num;
	int				*way;
	struct s_path	*next;
}					t_path;


t_input		*ft_analize_input(int argc, char **argv);
t_input		*ft_lstnew_input(char *s);
t_link		*ft_lstnew_link(t_room *room);
int			ft_lstdel_input(t_input *list);
int			ft_del_all(t_input *input, t_room *room);
t_room		*ft_make_rooms(t_input *input);
t_room		*ft_lstnew_room(char *name, int x, int y, t_params *par);
int			ft_limit_path(t_room *room);

t_path		*get_path(t_room *room, int limit);
int			ft_get_ant(t_room *room);
t_path		*ft_sort_paths(t_path *answer, int ant, int limit);
int			ft_len_output(t_path *answer, int ant, int dop);

#endif