# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lcuevas- <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/21 11:02:38 by lcuevas-          #+#    #+#              #
#    Updated: 2024/08/22 15:59:43 by lcuevas-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = gcc
CFLAGS = -Wall -Wextra -Werror #-g3 -pthread  -fsanitize=thread
RM = rm -rf

SRC = src/philo.c \
		src/check_arguments.c \
		src/routine.c \
		src/utils.c

OBJ = $(SRC:src/%.c=obj/%.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

obj/%.o: src/%.c
	mkdir -p obj
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) obj

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: re all clean fclean

