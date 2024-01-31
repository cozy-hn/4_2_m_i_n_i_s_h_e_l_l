# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jiko <jiko@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/27 16:32:40 by jiko              #+#    #+#              #
#    Updated: 2024/01/31 19:52:15 by jiko             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
LIBFTFLAG	= -Llibft -lft
LFLAGS		= -lreadline
RMF			= rm -f
BASE		= main minishell_util wlibft token_checker_1 token_checker_2 token_checker_3 \
tokenizer tokenizer_util parser parser_util minishell_free expansion start_exec heredoc wlibft_list \
main_signal start_exec_util


MAN_DIR = man/
SRC = $(addprefix $(MAN_DIR), $(addsuffix .c, $(BASE)))
OBJ = $(addprefix $(MAN_DIR), $(addsuffix .o, $(BASE)))

EXECUTE_DIR = man/execute/
EXECUTE_BASE = builtin_helper exec execute handle_redirection is_builtin  make_command path default_terminal
EXECUTE_SRC = $(addprefix $(EXECUTE_DIR), $(addsuffix .c, $(EXECUTE_BASE)))
EXECUTE_OBJ = $(addprefix $(EXECUTE_DIR), $(addsuffix .o, $(EXECUTE_BASE)))

BUILTIN_DIR = man/builtin/
BUILTIN_BASE = builtin_util builtin_util2 env_util ft_cd ft_echo ft_env ft_exit ft_export ft_pwd ft_unset
BUILTIN_SRC = $(addprefix $(BUILTIN_DIR), $(addsuffix .c, $(BUILTIN_BASE)))
BUILTIN_OBJ = $(addprefix $(BUILTIN_DIR), $(addsuffix .o, $(BUILTIN_BASE)))

BON_DIR = bon/
BON_SRC = $(addprefix $(BON_DIR), $(addsuffix _bonus.c, $(BASE)))
BON_OBJ = $(addprefix $(BON_DIR), $(addsuffix _bonus.o, $(BASE)))

BON_EXECUTE_DIR = bon/execute/
BON_EXECUTE_SRC = $(addprefix $(BON_EXECUTE_DIR), $(addsuffix _bonus.c, $(EXECUTE_BASE)))
BON_EXECUTE_OBJ = $(addprefix $(BON_EXECUTE_DIR), $(addsuffix _bonus.o, $(EXECUTE_BASE)))

BON_BUILTIN_DIR = bon/builtin/
BON_BUILTIN_SRC = $(addprefix $(BON_BUILTIN_DIR), $(addsuffix _bonus.c, $(BUILTIN_BASE)))
BON_BUILTIN_OBJ = $(addprefix $(BON_BUILTIN_DIR), $(addsuffix _bonus.o, $(BUILTIN_BASE)))

NAME		= minishell
BON_NAME	= minishell_bonus

all : lib $(NAME)

bonus : lib $(BON_NAME)
	@touch bonus

lib :
	@make -s -j -C ./libft

$(NAME) : $(OBJ) $(EXECUTE_OBJ) $(BUILTIN_OBJ)
	$(CC) $(OBJ) $(EXECUTE_OBJ) $(BUILTIN_OBJ) -o $(NAME) $(LFLAGS) $(LIBFTFLAG)

%.o : %.c
	$(CC) $(CFLAGS) -I . -c $< -o $@
	
# $(MAN_DIR)%.o : $(MAN_DIR)%.c
# 	$(CC) $(CFLAGS) -I . -c $< -o $@

# $(BUILTIN_DIR)%.o : $(BUILTIN_DIR)%.c
# 	$(CC) $(CFLAGS) -I. -c $< -o $@

# $(EXECUTE_DIR)%.o : $(EXECUTE_DIR)%.c
# 	$(CC) $(CFLAGS) -I. -c $< -o $@
	
$(BON_NAME) : $(BON_OBJ) $(BON_EXECUTE_OBJ) $(BON_BUILTIN_OBJ)
	$(CC) $(BON_OBJ) $(BON_EXECUTE_OBJ) $(BON_BUILTIN_OBJ) -o $(BON_NAME) $(LFLAGS) $(LIBFTFLAG)

# $(BON_DIR)%.o : $(BON_DIR)%.c
# 	$(CC) $(CFLAGS) -I . -c $< -o $@

# $(BON_BUILTIN_DIR)%.o : $(BON_BUILTIN_DIR)%.c
# 	$(CC) $(CFLAGS) -I. -c $< -o $@

# $(BON_EXECUTE_DIR)%.o : $(BON_EXECUTE_DIR)%.c
# 	$(CC) $(CFLAGS) -I. -c $< -o $@

clean :
	@make clean -C ./libft
	$(RMF) $(OBJ) $(EXECUTE_OBJ) $(BUILTIN_OBJ) $(BON_OBJ) $(BON_EXECUTE_OBJ) $(BON_BUILTIN_OBJ)

fclean : clean
	@make pclean -C ./libft
	$(RMF) $(NAME) $(BON_NAME) bonus

re : fclean all

t : all clean
	./$(NAME)

.PHONY : all clean fclean re 
