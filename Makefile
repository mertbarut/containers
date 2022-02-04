# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbarut <mbarut@student.42wolfsburg.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/21 15:55:20 by mbarut            #+#    #+#              #
#    Updated: 2022/02/04 19:55:28 by mbarut           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_VECTOR=ft_vector
NAME_MAP=ft_map

DRIVER_STD_VECTOR=drivers/std_vector_main.cpp
DRIVER_STD_MAP=drivers/std_map_main.cpp

DRIVER_FT_VECTOR=drivers/ft_vector_main.cpp
DRIVER_FT_MAP=drivers/ft_map_main.cpp

CC=clang++

CFLAGS= -Wall -Werror -Wextra -std=c++98 -g -o

all: $(NAME_VECTOR) $(NAME_MAP)

$(NAME_VECTOR):
	$(CC) $(DRIVER_FT_VECTOR) $(CFLAGS) ft_vector
	$(CC) $(DRIVER_STD_VECTOR) $(CFLAGS) std_vector

$(NAME_MAP):
	$(CC) $(DRIVER_FT_MAP) $(CFLAGS) ft_map
	$(CC) $(DRIVER_STD_MAP) $(CFLAGS) std_map

clean:
	@rm -rf ./ft_vector.dSYM
	@rm -rf ./ft_map.dSYM
	@rm -rf ./std_vector.dSYM
	@rm -rf ./std_map.dSYM

fclean: clean
	@rm -f ft_vector
	@rm -f std_vector
	@rm -f ft_map
	@rm -f std_map

re: fclean all

.PHONY: all clean fclean re