#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dle-blon <dle-blon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/06/24 22:14:34 by dle-blon          #+#    #+#              #
#    Updated: 2015/06/24 22:14:47 by dle-blon         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = ./convert

FILES = ./Convert.cpp ./main.cpp

OBJ = $(FILES:.cpp=.o)

FLAGS = -Wall -Wextra -Werror -O

all : $(NAME)

$(NAME): $(OBJ)
	clang++ $(FLAGS) $(OBJ) -o $(NAME)

%.o: %.cpp
	clang++ $(FLAGS) -o $@ -c $<

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all