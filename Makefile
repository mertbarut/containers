# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbarut <mbarut@student.42wolfsburg.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/21 15:55:20 by mbarut            #+#    #+#              #
#    Updated: 2022/02/01 22:26:05 by mbarut           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=ft_containers

STDNAME=std_containers

DRIVER=driver/main.cpp

STD=src/std_main.cpp

FT=src/ft_main.cpp

CC=clang++

CFLAGS_11= -Wall -Werror -Wextra -std=c++11 -g -o

CFLAGS_98= -Wall -Werror -Wextra -std=c++98 -g -o

all: $(NAME)

$(NAME):
	$(CC) $(FT) $(CFLAGS_98) $(NAME)
	$(CC) $(STD) $(CFLAGS_98) $(STDNAME)

c11:
	$(CC) $(STD) $(CFLAGS_11) $(NAME)

c98:
	$(CC) $(STD) $(CFLAGS_98) $(NAME)

clean:
	@rm -rf ./*.o ./ft_containers.dSYM
	@rm -rf ./*.o ./std_containers.dSYM

fclean: clean
	@rm -f $(NAME)
	@rm -f $(STDNAME)

re: fclean all

.PHONY: all clean fclean re