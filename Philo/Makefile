# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lugoncal <lugoncal@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/18 10:40:57 by lugoncal          #+#    #+#              #
#    Updated: 2023/09/18 12:26:34 by lugoncal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread #-fsanitize=thread
RM = rm -rf

SRC =	main.c utils.c create.c control.c living.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME):	$(OBJ)
			$(CC) -g $(CFLAGS) $(OBJ) -o philo

clean:
		$(RM) $(OBJ)

fclean: clean
		$(RM) $(NAME) 

re: fclean all
