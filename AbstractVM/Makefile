#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dle-blon <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/16 19:49:24 by dle-blon          #+#    #+#              #
#    Updated: 2017/01/21 23:19:35 by dle-blon         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = avm

CC = g++

VERSION = -std=c++11

FLAGS = -Wall -Wextra -Werror

INC = -I ./includes

SRC = main.cpp \
	  standard_workflow.cpp file_workflow.cpp skeleton.cpp\
	  Operand.class.cpp Stack.class.cpp \
	  exceptions/DivModByZeroException.class.cpp \
	  exceptions/InvalidArgumentException.class.cpp \
	  exceptions/ModuloFloatingException.class.cpp \
	  exceptions/OverflowException.class.cpp \
	  exceptions/ShouldNeverOccurException.class.cpp \
	  exceptions/StackException.class.cpp \
	  exceptions/UnderflowException.class.cpp \
	  exceptions/UnknownInstructionException.class.cpp

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

all : info $(NAME)

info :
	@if (! (test -e $(NAME) && test -e srcs/main.o));					\
	then																\
		echo "$(WHITE) Project: $(BASIC) $(PROJECT_NAME)";				\
		echo "$(WHITE) Compiler: $(BASIC) $(CC)";						\
		echo "$(WHITE) Version: $(BASIC) $(VERSION)";					\
		echo "$(WHITE) Flags: $(BASIC) $(FLAGS)";						\
	fi

%.o : %.cpp
	@$(CC) $(VERSION) $(FLAGS) $(INC) -c -o $@ $<
	@echo "$(BLUE) $< $(WHITE)->$(RED) $@ $(BASIC)"

$(NAME) : $(OBJS)
	@$(CC) $(VERSION) $(FLAGS) $(INC) $(OBJS) -o $(NAME)
	@echo "$(BLUE) objs $(WHITE)->$(RED) $@ $(BASIC)"

clean :
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all;