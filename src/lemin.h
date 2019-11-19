/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsheev <nsheev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 17:54:19 by bford             #+#    #+#             */
/*   Updated: 2019/11/19 16:04:23 by nsheev           ###   ########.fr       */
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
	int				bad_pos;
	int				visit;
	char			*name;
	int				x;
	int				y;
	int				num;
	int				ant;
	int				ant_num;
	int				start;
	int				end;
	int				num_links;
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
	int				len;
	int				num;
	int				*way;
	int				step_ants;
	struct s_path	*next;
}					t_path;


t_input		*ft_analize_input(int argc, char **argv);
t_input		*ft_lstnew_input(char *s);
t_link		*ft_lstnew_link(t_room *room);
int			ft_lstdel_input(t_input *list);
int			ft_del_all(t_input *input, t_room *room);

t_room		*ft_make_rooms(t_input *input);
t_room		*ft_lstnew_room(char *name, int x, int y, t_params *par);
void		ft_del_dead_end(t_room **room);

int			ft_limit_path(t_room *room);
int			ft_get_ant(t_room *room);
t_path		*ft_sort_paths(t_path *answer, int ant, int limit);
int			ft_len_output(t_path *answer, int ant, int dop);
int			ft_lstdel_path(t_path *path);
void		create_path(t_room *room, t_path **answer);


void		steps_print(t_path *path, t_room *room);

/* DOP FUNC */

void		ft_print_path(t_path *path, char *s);

#endif