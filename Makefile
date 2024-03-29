# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vparis <vparis@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/02 17:37:24 by vparis            #+#    #+#              #
#    Updated: 2018/01/15 10:23:15 by vparis           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	algo
CC			=	gcc

SRCD		=	srcs
INCD		=	includes
LIBFTD		=	libft
LIBTPOOLD	=	libtpool

SRCS		=	$(SRCD)/main.c $(SRCD)/algo.c
OBJS		=	$(patsubst %.c, %.o, $(SRCS))

CFLAGS		+=	-I$(INCD) -I$(LIBFTD)/includes -I$(LIBTPOOLD)/includes \
				-O3 -march=native
LDFLAGS		+=	-Wall -Wextra -Werror -std=c11 -pedantic -Wno-unused-result
LDLIBS		+=	-L$(LIBFTD) -L$(LIBTPOOLD) -lft -ltpool -lpthread

.PHONY: clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(LIBFTD)
	make -C $(LIBTPOOLD)
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

%.o: %.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ -c $<

clean:
	make -C $(LIBTPOOLD) clean
	make -C $(LIBFTD) clean
	@rm -vf $(OBJS)

fclean: clean
	make -C $(LIBTPOOLD) __fclean
	make -C $(LIBFTD) __fclean
	@rm -vf $(NAME)

re: fclean all
