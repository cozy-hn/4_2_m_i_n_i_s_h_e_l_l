# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jiko <jiko@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/27 16:32:40 by jiko              #+#    #+#              #
#    Updated: 2024/01/26 06:05:30 by jiko             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
LIBFTFLAG	= -Llibft -lft
LFLAGS		= -lreadline
RMF			= rm -f
BASE		= main minishell_util wlibft token_checker_1 token_checker_2 token_checker_3 \
tokenizer tokenizer_util parser parser_util print_tree minishell_free expansion start_exec heredoc wlibft_list \
main_signal start_exec_util

SRCS		= $(addsuffix .c, $(BASE))
OBJS		= $(addsuffix .o, $(BASE))

NOW_DIR = ./

EXECUTE_DIR = ./execute/
EXECUTE_BASE = builtin_helper exec execute handle_redirection is_builtin  make_command path
EXECUTE_SRC = $(addprefix $(EXECUTE_DIR), $(addsuffix .c, $(EXECUTE_BASE)))
EXECUTE_OBJ = $(addprefix $(EXECUTE_DIR), $(addsuffix .o, $(EXECUTE_BASE)))

BUILTIN_DIR = ./builtin/
BUILTIN_BASE = builtin_util builtin_util2 env_util ft_cd ft_echo ft_env ft_exit ft_export ft_pwd ft_unset
BUILTIN_SRC = $(addprefix $(BUILTIN_DIR), $(addsuffix .c, $(BUILTIN_BASE)))
BUILTIN_OBJ = $(addprefix $(BUILTIN_DIR), $(addsuffix .o, $(BUILTIN_BASE)))

NAME		= minishell

all : lib $(NAME)

lib :
	@make -s -j -C ./libft

$(NAME) : $(OBJS) $(EXECUTE_OBJ) $(BUILTIN_OBJ)
	$(CC) $(OBJS) $(EXECUTE_OBJ) $(BUILTIN_OBJ) -o $(NAME) $(LFLAGS) $(LIBFTFLAG)

$(NOW_DIR)%.o : $(NOW_DIR)%.c
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

t : all clean
	./$(NAME)

.PHONY : all clean fclean re
