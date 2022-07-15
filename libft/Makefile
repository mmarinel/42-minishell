# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/15 17:54:40 by mmarinel          #+#    #+#              #
#    Updated: 2022/07/15 18:02:47 by mmarinel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
HEADERS = libft.h

CFLAGS = -Wall -Wextra -Werror
CC = gcc

OBJS_DIR = ".objs"
OBJS = $(shell find . -name **/*.c -print | sed 's/\.c/\.o/g' | sed 's/\.\///')

all: $(NAME)

$(NAME): $(OBJS) $(HEADERS)
	ar -rc $(NAME) $(OBJS) && ranlib $(NAME)

clean:
	/bin/rm -f $(OBJS)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re