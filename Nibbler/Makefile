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

LIB_SDL_REQUIREMENT = libsdl2-dev

LIB_OPENGL_REQUIREMENT = freeglut3-dev

SRC = main.cpp Board.class.cpp Snake.class.cpp \
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
	@if ! (dpkg --get-selections | grep -q "^$(LIB_SDL_REQUIREMENT)" >/dev/null);									\
	then																												\
		echo "$(BLUE) package $(LIB_SDL_REQUIREMENT)$(RED) missing$(BASIC) ... starting installation$(BASIC)";		\
		if (sudo apt install $(LIB_SDL_REQUIREMENT));																\
		then																											\
			echo "$(GREEN)Successfully installed $(LIB_SDL_REQUIREMENT)$(BASIC)";									\
		else																											\
			echo "$(RED)Error installing $(LIB_SDL_REQUIREMENT)... $(GREEN)Cannot continue exit$(BASIC)";			\
			exit 1;																										\
		fi																												\
	fi

packagesOpenGL:
	@if ! (dpkg --get-selections | grep -q "^$(LIB_OPENGL_REQUIREMENT)" >/dev/null);									\
	then																												\
		echo "$(BLUE) package $(LIB_OPENGL_REQUIREMENT)$(RED) missing$(BASIC) ... starting installation$(BASIC)";		\
		if (sudo apt install $(LIB_OPENGL_REQUIREMENT));																\
		then																											\
			echo "$(GREEN)Successfully installed $(LIB_OPENGL_REQUIREMENT)$(BASIC)";									\
		else																											\
			echo "$(RED)Error installing $(LIB_OPENGL_REQUIREMENT)... $(GREEN)Cannot continue exit$(BASIC)";			\
			exit 1;																										\
		fi																												\
	fi

createlibs: createlibSDL createlibOpenGL

createlibSDL:
	@make -C ./libs/SDL
	@ln -s ./libs/SDL/lib/libguisdl.so libguisdl.so

createlibOpenGL:
	@make -C ./libs/openGL
	@ln -s ./libs/openGL//lib/libguiopengl.so libguiopengl.so

destroylibs: destroylibSDL destroylibOpenGL

destroylibSDL:
	@make fclean -C ./libs/SDL
	@rm -f libguisdl.so

destroylibOpenGL:
	@make fclean -C ./libs/openGL
	@rm -f libguiopengl	.so

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
