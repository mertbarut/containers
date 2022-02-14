# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbarut <mbarut@student.42wolfsburg.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/21 15:55:20 by mbarut            #+#    #+#              #
#    Updated: 2022/02/14 18:18:11 by mbarut           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_VECTOR=ft_vector
NAME_MAP=ft_map
NAME_STACK=ft_stack
NAME_SET=ft_set

DRIVER_FT_VECTOR=drivers/ft_vector_main.cpp
DRIVER_FT_MAP=drivers/ft_map_main.cpp
DRIVER_FT_STACK=drivers/ft_stack_main.cpp
DRIVER_FT_SET=drivers/ft_set_main.cpp

CC=clang++

CFLAGS= -Wall -Werror -Wextra -std=c++98 -g -o

all: $(NAME_VECTOR) $(NAME_MAP) $(NAME_STACK) $(NAME_SET)

$(NAME_VECTOR):
	$(CC) $(DRIVER_FT_VECTOR) $(CFLAGS) $(NAME_VECTOR)

$(NAME_MAP):
	$(CC) $(DRIVER_FT_MAP) $(CFLAGS) $(NAME_MAP)

$(NAME_STACK):
	$(CC) $(DRIVER_FT_STACK) $(CFLAGS) $(NAME_STACK)

$(NAME_SET):
	$(CC) $(DRIVER_FT_SET) $(CFLAGS) $(NAME_SET)

inf:
	clang++ -ftemplate-depth=100000 -ftemplate-backtrace-limit=0 -ferror-limit=0 ft/inf.cpp -o this_executable_is_never_created

clean:
	@rm -rf ./ft_vector.dSYM
	@rm -rf ./ft_map.dSYM
	@rm -rf ./ft_stack.dSYM
	@rm -rf ./ft_set.dSYM
	@rm -f error

fclean: clean
	@rm -f ft_vector
	@rm -f ft_map
	@rm -f ft_stack
	@rm -f ft_set

re: fclean all

.PHONY: all clean fclean re