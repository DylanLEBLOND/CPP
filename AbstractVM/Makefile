#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dle-blon <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/16 19:49:24 by dle-blon          #+#    #+#              #
#    Updated: 2017/01/16 19:56:11 by dle-blon         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = avm

CC = g++

FLAGS = -Wall -Wextra -Werror

INC = -I ./includes

SRC = 

SRC_DIR = ./srcs

SRCS = $(addprefix $(SRC_DIR)/,$(SRC))

OBJS = $(SRCS:.c=.o)

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
		echo "$(WHITE) Flags: $(BASIC) $(FLAGS)";						\
		echo "$(WHITE) Compiler: $(BASIC) $(CC)";						\
	fi

%.o : %.c
	@$(CC) $(FLAGS) $(INC) -c -o $@ $<
	@echo "$(BLUE) $< $(WHITE)->$(RED) $@ $(BASIC)"

$(NAME) : $(OBJS)
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)
	@echo "$(BLUE) objs $(WHITE)->$(RED) $(NAME) $(BASIC)"

clean :
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all;