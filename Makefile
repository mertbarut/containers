# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbarut <mbarut@student.42wolfsburg.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/21 15:55:20 by mbarut            #+#    #+#              #
#    Updated: 2022/02/14 22:07:25 by mbarut           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=ft_containers

DRIVER=main.cpp

CC=clang++

CFLAGS= -Wall -Werror -Wextra -std=c++98 -g -o

all: $(NAME)

$(NAME):
	$(CC) $(DRIVER) $(CFLAGS) $(NAME)

inf:
	clang++ -ftemplate-depth=100000 -ftemplate-backtrace-limit=0 -ferror-limit=0 ft/inf.cpp -o this_executable_is_never_created

clean:
	@rm -rf ./ft_containers.dSYM
	@rm -f error

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re