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

LINK = -lSDL2main -lSDL2 -lSDL2_image

LIB_REQUIREMENT = libsdl2-dev libsdl2-image-dev

SRC = GUISDL.class.cpp Board.class.cpp Bonus.class.cpp Snake.class.cpp \
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

all : info packages $(NAME)

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

packages:
	@for package in $(LIB_REQUIREMENT); do																\
		if ! (dpkg --get-selections | grep -q "^$$package" >/dev/null);									\
		then																							\
			echo "$(BLUE) package $$package$(RED) missing$(BASIC) ... starting installation$(BASIC)";	\
			if (sudo apt install $$package);															\
			then																						\
				echo "$(GREEN)Successfully installed $$package$(BASIC)";								\
			else																						\
				echo "$(RED)Error installing $$package... $(GREEN)Cannot continue exit$(BASIC)";		\
				exit 1;																					\
			fi																							\
		fi																								\
	done

$(NAME) :
	@if ! (test -e $(LIB));																			\
	then																							\
		mkdir -p ./lib;																				\
		$(CC) $(VERSION) $(FLAGS) $(DEFINE) $(INC) -o $(LIB) $(SRCS) $(LINK);						\
		if (test -e $(LIB));																		\
		then																						\
			echo "$(BLUE) created $(WHITE)->$(RED) $@ $(GREEN) (emplacement: ./lib) $(BASIC)";		\
		fi																							\
	else																							\
		echo "$(BLUE) already created $(WHITE)->$(RED) $@ $(GREEN) (emplacement: ./lib) $(BASIC)";	\
	fi

clean :
	@rm -f $(LIB)
	@rm -rf lib
	@echo "$(BLUE) $(NAME) $(WHITE)->$(RED) DELETED $(BASIC)"

fclean: clean

re: fclean all;
