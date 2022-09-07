# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zminhas <zminhas@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/06 19:06:08 by zminhas           #+#    #+#              #
#    Updated: 2022/09/07 15:43:16 by zminhas          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CXX = 		c++

CFLAGS =	-Wall -Wextra -Werror -std=c++98

FT_NAME =		ft_container
STD_NAME =		std_container

FT_SRCS =		ft_main.cpp
STD_SRCS =		std_main.cpp

FT_OBJS =		$(FT_SRCS:.cpp=.o)
STD_OBJS =		$(STD_SRCS:.cpp=.o)

.cpp.o:
			$(CXX) $(CFLAGS) -c -I ./ $< -o $(<:.cpp=.o)

all : 		$(FT_NAME) $(STD_NAME)

$(FT_NAME):	$(FT_OBJS)
			$(CXX) $(CFLAGS) -o $(FT_NAME) $(FT_OBJS)

$(STD_NAME):	$(STD_OBJS)
			$(CXX) $(CFLAGS) -o $(STD_NAME) $(STD_OBJS)

clean:
			rm -f $(FT_OBJS)
			rm -f $(STD_OBJS)

fclean: 	clean
			rm -f $(FT_NAME)
			rm -f $(STD_NAME)

re: 		fclean all

.PHONY:		all clean fclean re
