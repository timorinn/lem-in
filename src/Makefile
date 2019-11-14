# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: swedde <swedde@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/05 17:55:08 by bford             #+#    #+#              #
#    Updated: 2019/11/13 23:24:44 by swedde           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC =		ft_analize_input.c		\
			ft_lstdel_input.c		\
			ft_lstnew_input.c		\
			ft_make_rooms.c			\
			ft_lstnew_room.c		\
			ft_lstnew_link.c		\
			ft_limit_path.c			\
			ft_len_output.c			\
			ft_get_ant.c			\
			ft_sort_paths.c			\
			path.c					\
			ft_del_all.c

OBJ =		$(SRC:.c=.o)

HEAD =		./

NAME =		liblemin.a

all:		$(NAME)

$(NAME):	$(SRC)
			gcc -I./ -c *.c
			ar -rcs $(NAME) $(OBJ)

%.o:		%.c $(HEAD)
			gcc -I $(HEAD) -c $< -o $@

clean:
			rm -f $(OBJ)

fclean:		clean
			rm -f $(NAME)

re:			fclean all
