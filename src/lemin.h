/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swedde <swedde@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 17:54:19 by bford             #+#    #+#             */
/*   Updated: 2019/11/23 21:12:19 by swedde           ###   ########.fr       */
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
	int				suur;
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
	int				conflict;
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
	int				status;
	int				conflict;
	int				len;
	int				num;
	t_room			**way;
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

//algos

typedef struct s_vertex
{
	int				num;
	int				op;
	struct s_vertex	*next;
}				t_vertex;


void		reposition_path(t_path **answer);
void		steps_print(t_path *path, t_room *room);
int			length_path(t_path *l);
void		sort_path(t_path **answer);
t_vertex	*get_vertex(t_vertex *vertex, int num);
void		increase_vertex(t_vertex **vertex, int num);
void		set_default_vertex(t_vertex *vertex);
void		vertex_lst_del(t_vertex **vertex);
t_room		*get_room(t_room *room, int num);
int			get_start(t_room *room);
int			get_end(t_room *room);
void		search_path(t_room *room, t_path **answer);
void		path_lst_del(t_path **path);





/* DOP FUNC */

void		ft_print_path(t_path *path, char *s);
void		ft_print_rooms(t_room *room);

#endif
