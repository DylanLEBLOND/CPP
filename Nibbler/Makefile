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

INC = -I ./includes

LINK = -L./libs -ldl

SRC = main.cpp gestionGUI.cpp Board.class.cpp Bonus.class.cpp Snake.class.cpp \
	  exceptions/GUIException.class.cpp \
	  exceptions/DynamicLoadGUIException.class.cpp \
	  exceptions/UnknownEventException.class.cpp \
	  exceptions/InvalidArgumentException.class.cpp \
	  exceptions/ShouldNeverOccurException.class.cpp \

SRC_DIR = ./sources

SRCS = $(addprefix $(SRC_DIR)/,$(SRC))

OBJS = $(SRCS:.cpp=.o)

WHITE =		\033[37;01m
RED =		\033[31;01m
GREEN =		\033[32;01m
YELLOW =	\033[33;01m
BLUE =		\033[34;01m
BASIC =		\033[0m

.PHONY: all clean fclean re

all : info createlibs $(NAME)

createlibs: createlibSDL createlibSFML createlibAllegro

createlibSDL:
	@make -C ./libs/SDL
	@ln -fs ./libs/SDL/lib/libguisdl.so libguisdl.so

createlibSFML:
	@make -C ./libs/SFML
	@ln -fs ./libs/SFML/lib/libguisfml.so libguisfml.so

createlibAllegro:
	@make -C ./libs/Allegro
	@ln -fs ./libs/Allegro/lib/libguiallegro.so libguiallegro.so

destroylibs: destroylibSDL destroylibSFML destroylibAllegro

destroylibSDL:
	@make fclean -C ./libs/SDL
	@rm -f libguisdl.so

destroylibSFML:
	@make fclean -C ./libs/SFML
	@rm -f libguisfml.so

destroylibAllegro:
	@make fclean -C ./libs/Allegro
	@rm -f libguiallegro.so

info :
	@if (! (test -e $(NAME)));											\
	then																\
		echo "$(WHITE) Project: $(BASIC) $(NAME)";						\
		echo "$(WHITE) C++ Compiler: $(BASIC) $(CC)";					\
		echo "$(WHITE) C++ Version: $(BASIC) $(VERSION)";				\
		echo "$(WHITE) C++ Flags: $(BASIC) $(FLAGS)";					\
		echo "$(WHITE) Includes: $(BASIC) $(INC)";						\
		echo "$(WHITE) Links: $(BASIC) $(LINK)";						\
	fi

%.o : %.cpp
	@$(CC) $(FLAGS) $(INC) -c -o $@ $<
	@echo "$(BLUE) $< $(WHITE)->$(RED) $@ $(BASIC)"

$(NAME) : $(OBJS)
	@$(CC) $(VERSION) $(FLAGS) $(OBJS) $(LINK) -o $(NAME)
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

############################## DEBUG MODE ###############################

createlibsdebug: createlibSDLdebug createlibSFMLdebug \
				 createlibAllegrodebug

createlibSDLdebug:
	@make debug -C ./libs/SDL
	@ln -fs ./libs/SDL/lib/libguisdl.so libguisdl.so

createlibSFMLdebug:
	@make debug -C ./libs/SFML
	@ln -fs ./libs/SFML/lib/libguisfml.so libguisfml.so

createlibAllegrodebug:
	@make debug -C ./libs/Allegro
	@ln -fs ./libs/Allegro/lib/libguiallegro.so libguiallegro.so

printdebug :
	@echo "$(RED)*************** DEBUG MODE ***************$(BASIC)"

debug: FLAGS += -g -D DEBUG_MODE
debug : printdebug info createlibsdebug $(NAME)
