#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dle-blon <dle-blon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/06/21 22:18:13 by dle-blon          #+#    #+#              #
#    Updated: 2015/06/21 22:18:17 by dle-blon         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME =	ft_retro
C_SRC = main.cpp AStuff.class.cpp AUnit.class.cpp Player.class.cpp Enemy.class.cpp Missile.class.cpp Obstacle.class.cpp promptUser.cpp framePrint.cpp gameLoop.cpp checkAllCollisions.cpp moveAll.cpp
# INC = AStuff.class.hpp Enemy.class.hpp Obstacle.class.hpp retro.hpp AUnit.class.hpp Missile.class.hpp Player.class.hpp
I_DIR = inc
O_DIR =	obj
VPATH =	src
SRCC = 	$(C_SRC:%.cpp=$(VPATH)/%.cpp)
SRCO =	$(C_SRC:%.cpp=$(O_DIR)/%.o)
CC =	clang++
RM =	rm -rf
MKDIR = mkdir -p
CFLAGS = -Wall -Werror -Wextra -Wpedantic -Wold-style-cast -Woverloaded-virtual -Wfloat-equal -Wwrite-strings -Wcast-qual -Wcast-align -Wconversion -Wshadow -Weffc++ -Wredundant-decls -Winit-self -Wswitch-default -Wswitch-enum -Wundef -Winline -O2
CURSES = -lncurses

COLOR_WHITE = \033[37;01m
COLOR_RED = \033[31;01m
COLOR_GREEN =  \033[32;01m
COLOR_BLUE =  \033[34;01m
COLOR_OFF = \033[0m

.PHONY: all lib soft clean fclean re

all: 
	@$(MKDIR) $(O_DIR)
	@$(MAKE) $(NAME)

$(NAME): $(SRCO) # $(INC)
	@$(CC) $(CFLAGS) -I $(I_DIR) $(SRCO) $(CURSES) -o $@
	@echo "$(COLOR_BLUE)$(SRCO) $(COLOR_WHITE)->$(COLOR_RED) $@ $(COLOR_OFF)"
#	@echo "\n$(COLOR_WHITE)flags:$(COLOR_OFF) $(CFLAGS)"
#	@echo "$(COLOR_WHITE)compi:$(COLOR_OFF) $(CC)"

$(O_DIR)/%.o: %.cpp
	@$(RM) $(NAME)
	@$(CC) $(CFLAGS) -I $(I_DIR) -c $^ -o $@
	@echo "$(COLOR_WHITE)$^\t->$(COLOR_BLUE) $@ $(COLOR_OFF)"

soft:
	@$(RM) $(NAME)
	@$(CC) -I $(I_DIR) $(SRCC) -o $(NAME) $(CURSES)

clean:
	@$(RM) $(O_DIR)

fclean: clean
	@$(RM) $(NAME)

re: fclean all
