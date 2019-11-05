# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bford <bford@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/05 13:27:38 by bford             #+#    #+#              #
#    Updated: 2019/11/05 15:41:53 by bford            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC =	ft_putstr.c		\
		ft_strlen.c

OBJ = $(SRC:%.c=%.o)

HEAD =	libft.h

NAME =	libft.a

.PHONY:	all clean fclean re

all:		$(NAME)

$(NAME):	$(OBJ)
			ar -rcs $(NAME) $(OBJ)

%.o:		%.c $(HEAD)
			gcc -I $(HEAD) -Wall -Wextra -Werror -c $< -o $@

clean:
			rm -f $(OBJ)

fclean:		clean
			rm -f $(NAME)

re:			fclean all
