# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zminhas <zminhas@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/06 19:06:08 by zminhas           #+#    #+#              #
#    Updated: 2022/09/06 19:36:16 by zminhas          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CXX = 		c++

CFLAGS =	-Wall -Wextra -Werror -std=c++98

FT_NAME =		ft_container
STD_NAME =		std_container

FT = -D NAMESPACE=ft
STD = -D NAMESPACE=std

SRCS =		main.cpp		\

OBJS =		$(SRCS:.cpp=.o)

.cpp.o:
			$(CXX) $(CFLAGS) $(FT) -c -I ./ $< -o $(<:.cpp=.o)

all : 		$(FT_NAME) $(STD_NAME)

$(FT_NAME):	$(OBJS)
			$(CXX) $(CFLAGS) $(FT) -o $(FT_NAME) $(OBJS)

$(STD_NAME):	$(OBJS)
			$(CXX) $(CFLAGS) $(STD) -o $(STD_NAME) $(OBJS)

clean:
			rm -f $(OBJS)

fclean: 	clean
			rm -f $(FT_NAME)
			rm -f $(STD_NAME)

re: 		fclean all

.PHONY:		all clean fclean re
