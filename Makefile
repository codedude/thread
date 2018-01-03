# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vparis <vparis@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/02 17:37:24 by vparis            #+#    #+#              #
#    Updated: 2018/01/03 18:50:04 by vparis           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	thread
CC			=	gcc

SRCD		=	srcs
INCD		=	includes
LIBFTD		=	libft

SRCS		=	$(SRCD)/main.c $(SRCD)/algo.c $(SRCD)/tp_queue.c \
				$(SRCD)/tp_pool.c $(SRCD)/tp_thread.c
OBJS		=	$(patsubst %.c, %.o, $(SRCS))

CFLAGS		+=	-I$(INCD) -I$(LIBFTD)/includes
#Warnigs and debug
LDFLAGS		+=	-Wall -Wextra -ansi -pedantic -Wno-unused-result
LDLIBS		+=	-L$(LIBFTD) -lft -lpthread

.PHONY: clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(LIBFTD)
	$(CC) -o $@ $^ $(LDLIBS)

%.o: %.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ -c $<

clean:
	make -C $(LIBFTD) clean
	@rm -vf $(OBJS)

fclean: clean
	make -C $(LIBFTD) __fclean
	@rm -vf $(NAME)

re: fclean all
