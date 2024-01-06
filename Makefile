# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jiko <jiko@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/27 16:32:40 by jiko              #+#    #+#              #
#    Updated: 2024/01/07 01:24:08 by jiko             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
LIBFTFLAG	= -Llibft -lft
LFLAGS		= -lreadline
RMF			= rm -f
BASE		= main minishell_util wlibft
SRCS		= $(addsuffix .c, $(BASE))
OBJS		= $(addsuffix .o, $(BASE))
NAME		= minishell

all : lib $(NAME)

lib :
	@make -j -C ./libft

$(NAME) : $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(LFLAGS) $(LIBFTFLAG)

%.o : %.c
	$(CC) $(CFLAGS) -I . -c $<

clean :
	@make clean -C ./libft
	$(RMF) $(OBJS)

fclean : clean
	@make pclean -C ./libft
	$(RMF) $(NAME)

re : fclean all

.PHONY : all clean fclean re
