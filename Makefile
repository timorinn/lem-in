# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bford <bford@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/05 13:37:52 by bford             #+#    #+#              #
#    Updated: 2019/11/05 16:13:05 by bford            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		lem-in

SRC =		main.c

LIBFT = 	./libft

OBJ = $(SRC:.c=.o)

.PHONY: 	all clean fclean re

all:		lib $(NAME)

%.o:		%.c
			gcc -I $(LIBFT) -o $@ -c $<

$(NAME):	$(OBJ) ./libft/libft.a
			gcc -o lem-in $(OBJ) -L ./libft -lft


lib:
			make -C ./libft

clean:
			rm -f main.o
			make clean -C ./libft

fclean:		clean
			rm -f $(NAME)
			make fclean -C ./libft

re:			fclean all
