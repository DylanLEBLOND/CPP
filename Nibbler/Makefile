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

NAME = nibbler

CC = g++

VERSION = -std=c++11

FLAGS = -Wall -Wextra -Werror

DEFINE = # -D PROJ_DEBUG

INC = -I ./includes

LINK = -L./libs -ldl

LIB_SDL_REQUIREMENT = libsdl2-dev libsdl2-image-dev

LIB_OPENGL_REQUIREMENT = freeglut3-dev

SRC = main.cpp gestionGUI.cpp Board.class.cpp Bonus.class.cpp Snake.class.cpp \
	  exceptions/GUIException.class.cpp \
	  exceptions/DynamicLoadGUIException.class.cpp \
	  exceptions/UnknownEventException.class.cpp \
	  exceptions/InvalidArgumentException.class.cpp \
	  exceptions/ShouldNeverOccurException.class.cpp \

SRC_DIR = ./srcs

SRCS = $(addprefix $(SRC_DIR)/,$(SRC))

OBJS = $(SRCS:.cpp=.o)

WHITE =		\033[37;01m
RED =		\033[31;01m
GREEN =		\033[32;01m
YELLOW =	\033[33;01m
BLUE =		\033[34;01m
BASIC =		\033[0m

.PHONY: all clean fclean re

all : info packages createlibs $(NAME)

packages: packagesSDL packagesOpenGL

packagesSDL:
	@for package in $(LIB_SDL_REQUIREMENT); do															\
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

packagesOpenGL:
	@for package in $(LIB_OPENGL_REQUIREMENT); do															\
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

createlibs: createlibSDL createlibOpenGL

createlibSDL:
	@if (! (test -e libguisdl.so));										\
	then																\
		make -C ./libs/SDL;												\
		ln -s ./libs/SDL/lib/libguisdl.so libguisdl.so;					\
	fi

createlibOpenGL:
	@if (! (test -e libguiopengl.so));									\
	then																\
		make -C ./libs/openGL;											\
		ln -s ./libs/openGL/lib/libguiopengl.so libguiopengl.so;		\
	fi

destroylibs: destroylibSDL destroylibOpenGL

destroylibSDL:
	@make fclean -C ./libs/SDL
	@rm -f libguisdl.so

destroylibOpenGL:
	@make fclean -C ./libs/openGL
	@rm -f libguiopengl.so

info :
	@if (! (test -e $(NAME) && test -e srcs/main.o));					\
	then																\
		echo "$(WHITE) Project: $(BASIC) $(NAME)";						\
		echo "$(WHITE) C++ Compiler: $(BASIC) $(CC)";					\
		echo "$(WHITE) C++ Version: $(BASIC) $(VERSION)";				\
		echo "$(WHITE) C++ Flags: $(BASIC) $(FLAGS)";					\
		echo "$(WHITE) Defines: $(BASIC) $(DEFINE)";					\
		echo "$(WHITE) Includes: $(BASIC) $(INC)";						\
		echo "$(WHITE) Links: $(BASIC) $(LINK)";						\
	fi

%.o : %.cpp
	@$(CC) $(FLAGS) $(DEFINE) $(INC) -c -o $@ $<
	@echo "$(BLUE) $< $(WHITE)->$(RED) $@ $(BASIC)"

$(NAME) : $(OBJS)
	@$(CC) $(VERSION) $(FLAGS) $(DEFINE) $(OBJS) $(LINK) -o \
	 $(NAME)
	@echo "$(BLUE) objs $(WHITE)->$(RED) $@ $(BASIC)"

print :
	@echo $(OBJS)

clean :
	@rm -f $(OBJS)
	@echo "$(BLUE) objs $(WHITE)->$(RED) DELETED $(BASIC)"

fclean: clean destroylibs
	@rm -f $(NAME)
	@echo "$(BLUE) $(NAME) $(WHITE)->$(RED) DELETED $(BASIC)"

re: fclean all;
