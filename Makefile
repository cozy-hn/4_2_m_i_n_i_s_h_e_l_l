# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jiko <jiko@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/27 16:32:40 by jiko              #+#    #+#              #
#    Updated: 2024/01/19 05:22:24 by jiko             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= cc
# CFLAGS		= -Wall -Wextra -Werror
CFLAGS		= 
LIBFTFLAG	= -Llibft -lft
LFLAGS		= -lreadline
RMF			= rm -f
BASE		= main minishell_util wlibft token_checker_1 token_checker_2 token_checker_3 \
tokenizer print_for_test parser print_tree minishell_free expansion start_exec
SRCS		= $(addsuffix .c, $(BASE))
OBJS		= $(addsuffix .o, $(BASE))

NOW_DIR = ./

EXECUTE_DIR = ./execute/
# EXECUTE_BASE = *
# EXECUTE_SRC = $(addprefix $(EXECUTE_DIR), $(addsuffix .c, $(EXECUTE_BASE)))
# EXECUTE_OBJ = $(addprefix $(EXECUTE_DIR), $(addsuffix .o, $(EXECUTE_BASE)))

BUILTIN_DIR = ./builtin/
# BUILTIN_BASE = *
# BUILTIN_SRC = $(addprefix $(BUILTIN_DIR), $(addsuffix .c, $(BUILTIN_BASE)))
# BUILTIN_OBJ = $(addprefix $(BUILTIN_DIR), $(addsuffix .o, $(BUILTIN_BASE)))

EXECUTE_SRC = $(wildcard $(EXECUTE_DIR)*.c)
EXECUTE_OBJ = $(patsubst $(EXECUTE_DIR)%.c,$(EXECUTE_DIR)%.o,$(EXECUTE_SRC))

BUILTIN_SRC = $(wildcard $(BUILTIN_DIR)*.c)
BUILTIN_OBJ = $(patsubst $(BUILTIN_DIR)%.c,$(BUILTIN_DIR)%.o,$(BUILTIN_SRC))

NAME		= minishell

all : lib $(NAME)

lib :
	@make -s -j -C ./libft

$(NAME) : $(OBJS) $(EXECUTE_OBJ) $(BUILTIN_OBJ)
	$(CC) $(OBJS) $(EXECUTE_OBJ) $(BUILTIN_OBJ) -o $(NAME) $(LFLAGS) $(LIBFTFLAG)

$(NOW_DIR)%.o : $(NOW_DIR)./%.c
	$(CC) $(CFLAGS) -I . -c $< -o $@

$(BUILTIN_DIR)%.o : $(BUILTIN_DIR)%.c
	$(CC) $(CFLAGS) -I. -c $< -o $@

$(EXECUTE_DIR)%.o : $(EXECUTE_DIR)%.c
	$(CC) $(CFLAGS) -I. -c $< -o $@

clean :
	@make clean -C ./libft
	$(RMF) $(OBJS) $(EXECUTE_OBJ) $(BUILTIN_OBJ)

fclean : clean
	@make pclean -C ./libft
	$(RMF) $(NAME)

re : fclean all

.PHONY : all clean fclean re
