# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jiko <jiko@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/27 16:32:40 by jiko              #+#    #+#              #
#    Updated: 2024/01/03 22:27:48 by jiko             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
LFLAGS = -lreadline
RMF = rm -f
BASE = main minishell_util
SRCS = $(addsuffix .c, $(BASE))
OBJS = $(addsuffix .o, $(BASE))
NAME = minishell

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(LFLAGS)

%.o : %.c
	$(CC) $(CFLAGS) -I . -c $<

clean :
	$(RMF) $(OBJS)

fclean : clean
	$(RMF) $(NAME)

re : fclean all

.PHONY : all clean fclean re
