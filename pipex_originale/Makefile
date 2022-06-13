# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/11 21:26:02 by mmarinel          #+#    #+#              #
#    Updated: 2022/03/20 10:21:19 by mmarinel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = gcc
CFLAGS = -Wall -Werror -Wextra


UTILS_SRCS = utils/*.c
CHILDREN_SRCS = children/*.c
GNL_SRCS = get_next_line/*.c

PX_SRCS = pipex.c
BONUS_SRCS = bonus/*.c

SRCS = $(UTILS_SRCS) $(CHILDREN_SRCS) $(PX_SRCS)

all: .ADD_MANDATORY

bonus: .ADD_BONUS

do_bonus: $(NAME)

do_mandatory: $(NAME)

$(NAME): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

clean:
	/bin/rm -f $(PX_SRCS:.c=.o) $(BONUS_SRCS:.c=.o) $(GNL_SRCS:.c=.o) $(UTILS_SRCS:.c=.o) $(CHILDREN_SRCS:.c=.o)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

.ADD_MANDATORY:
	@$(MAKE) do_mandatory SRCS="$(UTILS_SRCS) $(CHILDREN_SRCS) $(PX_SRCS)"

.ADD_BONUS:
	@$(MAKE) do_bonus SRCS="$(UTILS_SRCS) $(CHILDREN_SRCS) $(GNL_SRCS) $(BONUS_SRCS)"