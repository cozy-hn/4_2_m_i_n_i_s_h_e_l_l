# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jiko <jiko@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/27 16:32:40 by jiko              #+#    #+#              #
#    Updated: 2024/01/08 19:29:13 by jiko             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
LIBFTFLAG	= -Llibft -lft
LFLAGS		= -lreadline
RMF			= rm -f
BASE		= main minishell_util wlibft token_checker_1 token_checker_2 token_checker_3 \
tokenizer print_for_test parser print_tree
SRCS		= $(addsuffix .c, $(BASE))
OBJS		= $(addsuffix .o, $(BASE))
NAME		= minishell

all : lib $(NAME)

lib :
	@make -s -j -C ./libft

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
