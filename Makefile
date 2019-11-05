# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bford <bford@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/05 13:37:52 by bford             #+#    #+#              #
#    Updated: 2019/11/05 20:21:32 by bford            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		lem-in

SRC =		main.c

LIBFT = 	./libft

LEMIN =		./src

OBJ = $(SRC:.c=.o)

.PHONY: 	all clean fclean re

all:		lib lemin $(NAME)

%.o:		%.c
			gcc -I $(LIBFT) -I $(LEMIN) -o $@ -c $<

$(NAME):	$(OBJ) ./libft/libft.a ./src/liblemin.a 
			gcc -o lem-in $(OBJ) -L ./libft -lft -L ./src -llemin

lemin:
			make -C ./src

lib:
			make -C ./libft

clean:
			rm -f main.o
			make clean -C ./libft
			make clean -C ./src

fclean:		clean
			rm -f $(NAME)
			make fclean -C ./libft
			make fclean -C ./src

re:			fclean all

val:
			valgrind 