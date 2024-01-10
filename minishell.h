/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 17:53:26 by jiko              #+#    #+#             */
/*   Updated: 2024/01/10 19:07:15 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h> // for tmp
# include "./libft/libft.h"

// # include <signal.h>
// # include <unistd.h>
// # include <sys/types.h>
// # include <sys/wait.h>
// # include <sys/stat.h>
// # include <fcntl.h>
// # include <dirent.h>
// # include <errno.h>	

extern int g_exit_status;
int g_exit_status;

typedef enum type
{
	T_PIPE = 1,
	T_OR = 2,
	T_AND = 3,
	T_L_PAR = 4,
	T_R_PAR = 5,
	T_L_REDIR = 6,
	T_R_REDIR = 7,
	T_L_D_REDIR = 8,
	T_R_D_REDIR = 9,
	T_WORD = 10,
	T_NEWLINE = 11,
}	t_type;

typedef struct s_token
{
	t_type			type;
	char			*word;
	struct s_token	*next;
}	t_token;

typedef struct s_lst{
    int				fd_in;
    int				fd_out;
	char			**cmd;
	int				prev_pipe;
	struct s_lst	*next;
} t_lst;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_arg
{
	t_env	*env;
	char	**path;
	t_lst	*lst;
} t_arg;

int		remove_space(char *line, int *i);
int		is_space(char c);
int		is_pipe(char *line, int *i);
int 	is_meta(char *line);
int		is_or(char *line, int *i);
int		is_and(char *line, int *i);
int		is_l_redir(char *line, int *i);
int		is_r_redir(char *line, int *i);
int		is_l_d_redir(char *line, int *i);
int		is_r_d_redir(char *line, int *i);
int		is_l_par(char *line, int *i);
int		is_r_par(char *line, int *i);
void	wft_lstadd_back(t_token **lst, t_token *new);
void	*wft_calloc(size_t count, size_t size);
char	*ft_strjoin_char(char const *s1, char const s2);
void 	free_token(t_token *token);


#endif
