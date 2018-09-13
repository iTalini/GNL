# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dkalashn <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/09 15:38:15 by dkalashn          #+#    #+#              #
#    Updated: 2017/11/09 15:44:11 by dkalashn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = $(wildcard *.c)
INCLUDE = libft.h
OBJECTS = $(SRC:.c=.o)
CFLAGS = -Wall -Wextra -Werror

.PHONY: all
all: $(NAME)

$(NAME): $(OBJECTS)
	@echo made
	@ar rc $(NAME) $(OBJECTS)
	@ranlib $(NAME)

.c.o:
	@gcc -c $(CFLAGS) -I $(INCLUDE) $(SRC) $<

.PHONY: clean
clean:
	@echo cleaned
	@/bin/rm -f $(OBJECTS)

.PHONY: fclean
fclean: clean
	@echo fcleaned
	@/bin/rm -f $(NAME)

.PHONY: re
re: fclean all
