# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: swedde <swedde@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/05 13:37:52 by bford             #+#    #+#              #
#    Updated: 2019/11/13 23:30:04 by swedde           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		lem-in

SRC =		main.c

LIBFT = 	./libft

LEMIN =		./src

LIBFTA =	./libft/libft.a

LEMINA =	./src/liblemin.a

OBJ = $(SRC:.c=.o)

.PHONY: 	all clean fclean re

all:		$(NAME)

%.o:		%.c
			gcc -I $(LIBFT) -I $(LEMIN) -o $@ -c $<

$(NAME):	$(LIBFTA) $(LEMINA) $(OBJ) ./libft/libft.a ./src/liblemin.a
			gcc -o lem-in main.c ./src/liblemin.a ./libft/libft.a -I./src

FORCE:		;

$(LEMINA):	FORCE
			make -C ./src

$(LIBFTA):	FORCE
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