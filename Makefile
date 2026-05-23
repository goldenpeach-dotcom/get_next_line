# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkaneko <mkaneko@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/05/04 15:09:15 by mkaneko           #+#    #+#              #
#    Updated: 2026/05/23 16:43:04 by mkaneko          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME     = test_gnl

CC       = cc
CFLAGS   = -Wall -Wextra -Werror

BUFFER_SIZE	?= 42

SRCS = \
	get_next_line.c \
	get_next_line_utils.c\
	main.c
	 
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -D BUFFER_SIZE=$(BUFFER_SIZE) $(OBJS) -o $(NAME) 
%.o: %.c get_next_line.h
	$(CC) $(CFLAGS) -D BUFFER_SIZE=$(BUFFER_SIZE) -c $< -o $@

clean:
	rm -f $(OBJS) 

fclean: clean
	rm -f $(NAME)

re:	fclean all

.PHONY	:	all clean fclean re
