# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbarut <mbarut@student.42wolfsburg.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/21 15:55:20 by mbarut            #+#    #+#              #
#    Updated: 2021/12/26 16:38:20 by mbarut           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=ft_containers

DRIVER=driver/main.cpp
ENABLE_IF=driver/main_enable_if.cpp

SRC=src/test.cpp

CC=clang++

CFLAGS= -Wall -Werror -Wextra -std=c++98 -g -o

all: $(NAME)

$(NAME):
	$(CC) $(SRC) $(CFLAGS) $(NAME)

clean:
	@rm -f ./*.o

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re