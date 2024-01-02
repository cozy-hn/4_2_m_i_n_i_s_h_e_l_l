# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jiko <jiko@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/27 16:32:40 by jiko              #+#    #+#              #
#    Updated: 2024/01/02 19:49:09 by jiko             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
LFLAGS = -lreadline
RMF = rm -f
BASE = main 
SRCS = $(addsuffix .c, $(BASE))
OBJS = $(addsuffix .o, $(BASE))
NAME = minishell

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LFLAGS)

%.o : %.c
	$(CC) $(CFLAGS) -I . -c $<

clean :
	$(RMF) $(OBJS)

fclean : clean
	$(RMF) $(NAME)

re : fclean all

.PHONY : all clean fclean re
