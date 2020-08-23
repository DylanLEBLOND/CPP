#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dle-blon <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/16 19:49:24 by dle-blon          #+#    #+#              #
#    Updated: 2017/01/22 19:03:23 by dle-blon         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

PROJECT_NAME = Shared Library \"GUI SDL\"

NAME = libguisdl.so

CC = g++

VERSION = -std=c++11

FLAGS = -shared -fPIC #-Wall -Wextra -Werror

DEFINE = -D PROJ_DEBUG

INC = -I ./inc -I ../../includes

LINK = -lSDL2main -lSDL2

SRC = GUISDL.class.cpp Board.class.cpp Snake.class.cpp \
	  exceptions/GUIException.class.cpp \
	  exceptions/DynamicLoadGUIException.class.cpp \
	  exceptions/UnknownEventException.class.cpp \
	  exceptions/InvalidArgumentException.class.cpp \
	  exceptions/ShouldNeverOccurException.class.cpp \

SRC_DIR = ./src

SRCS = $(addprefix $(SRC_DIR)/,$(SRC))

LIB_DIR = ./lib

LIB =  $(addprefix $(LIB_DIR)/,$(NAME))

WHITE =		\033[37;01m
RED =		\033[31;01m
GREEN =		\033[32;01m
YELLOW =	\033[33;01m
BLUE =		\033[34;01m
BASIC =		\033[0m

.PHONY: all clean fclean re

all : info $(NAME)

info :
	@if ! (test -e $(LIB));												\
	then																\
		echo "$(WHITE) Project: $(BASIC) $(PROJECT_NAME)";				\
		echo "$(WHITE) C++ Compiler: $(BASIC) $(CC)";					\
		echo "$(WHITE) C++ Version: $(BASIC) $(VERSION)";				\
		echo "$(WHITE) C++ Flags: $(BASIC) $(FLAGS)";					\
		echo "$(WHITE) Defines: $(BASIC) $(DEFINE)";					\
		echo "$(WHITE) Includes: $(BASIC) $(INC)";						\
		echo "$(WHITE) Links: $(BASIC) $(LINK)";						\
	fi

$(NAME) :
	@if ! (test -e $(LIB));																			\
	then																							\
		$(CC) $(VERSION) $(FLAGS) $(DEFINE) $(INC) -o $(LIB) $(SRCS) $(LINK);						\
		echo "$(BLUE) created $(WHITE)->$(RED) $@ $(GREEN) (emplacement: ./lib) $(BASIC)";			\
	else																							\
		echo "$(BLUE) already created $(WHITE)->$(RED) $@ $(GREEN) (emplacement: ./lib) $(BASIC)";	\
	fi

clean :
	@rm -f $(LIB)
	@echo "$(BLUE) $(NAME) $(WHITE)->$(RED) DELETED $(BASIC)"

fclean: clean

re: fclean all;
