# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbarut <mbarut@student.42wolfsburg.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/21 15:55:20 by mbarut            #+#    #+#              #
#    Updated: 2021/12/23 14:30:34 by mbarut           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=ft_containers

DRIVER=driver/main.cpp

#SRC=

CC=clang++

CFLAGS= -Wall -Werror -Wextra -std=c++98 -o

all: $(NAME)

$(NAME):
	$(CC) $(DRIVER) $(CFLAGS) $(NAME)

clean:
	@rm -f ./*.o

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re