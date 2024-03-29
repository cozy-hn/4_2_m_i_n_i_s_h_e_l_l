/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiko <jiko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 17:53:26 by jiko              #+#    #+#             */
/*   Updated: 2024/01/31 20:26:41 by jiko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_BONUS_H
# define MINISHELL_BONUS_H
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "./libft/libft.h"
# include <termios.h>
# include <signal.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/stat.h>

# define SHE 0
# define DFL 1
# define IGN 2
# define HED 3

int	g_exit;

typedef enum type
{
	T_NONE = 0,
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
	BNF_LIST = 12,
	BNF_PIPELINE = 13,
	BNF_COMMAND = 14,
	BNF_COMMAND_PART = 15
}	t_type;

typedef struct s_token
{
	t_type			type;
	char			*word;
	struct s_token	*next;
}	t_token;

typedef struct s_cmd_tree
{
	t_token				*token;
	t_type				bnf_type;
	struct s_cmd_tree	*left;
	struct s_cmd_tree	*right;
}	t_cmd_tree;

typedef struct s_lst{
	t_type			in_type;
	t_type			out_type;
	char			*fd_in_name;
	char			*fd_out_name;
	int				fd_in;
	int				fd_out;
	char			**cmd;
	int				prev_pipe;
	int				error_flag;
	struct s_lst	*next;
}	t_lst;

typedef struct s_heredoc
{
	char				*name;
	struct s_heredoc	*next;
	int					hed_flag;
}	t_heredoc;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_arg
{
	t_env			**env;
	t_heredoc		*hed_lst;
	char			**path;
	t_lst			*lst;
}	t_arg;

typedef struct s_main
{
	char			*line;
	t_token			*token;
	t_cmd_tree		*cmd_tree;
	t_env			*env_lst;
	t_arg			*arg;
	t_heredoc		*hed_lst;
	int				exit_code;
}	t_main;

int		remove_space(char *line, int *i);
int		is_space(char c);
int		is_pipe(char *line, int *i);
int		is_meta(char *line);
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
void	free_token(t_token *token);
int		set_type(char *line, int *i);
int		word_checker(char *line, int dquote, int squote);
char	*set_word(char *line, int *i, t_main *main);
int		parser(t_cmd_tree **head, t_token **token, t_main *main);
int		cmd_list(t_cmd_tree **head, t_token **now, t_heredoc **hed_lst);
int		cmd_pipeline(t_cmd_tree **head, t_token **now, t_heredoc **hed_lst);
int		cmd_command(t_cmd_tree **head, t_token **now, t_heredoc **hed_lst);
int		cmd_command_part(t_cmd_tree **head, t_token **now, t_heredoc **hed_lst);
int		cmd_command_else(t_cmd_tree **head, t_token **now, t_heredoc **hed_lst);
int		tokenizer(char *line, t_token **token, t_main *main);
void	free_cmd_tree(t_cmd_tree *cmd_tree);
void	safe_free(void *str);
char	*wft_strdup(const char *src);
int		wft_lstsize(t_token *lst);
t_token	*wft_lstlast(t_token *lst);
int		ft_is_env_word(char c, int i);
int		expander(t_cmd_tree **cmd_tree, t_env *env_lst);
char	*wft_strjoin(char const *s1, char const *s2);
void	start_exec(t_cmd_tree *cmd_tree, t_main *main);
void	wft_lstadd_back_lst(t_lst **lst, t_lst *new);
void	free_env_lst(t_env *env_lst);
char	*avoid_duplicate_name(void);
t_lst	*wft_lstlast_lst(t_lst *lst);
char	*expand(char *word, t_main *main);
char	*expand_env(char **word, t_main *main);
void	set_signal(int sig_int, int sig_quit);
char	*set_meta_word(int type);
void	heredoc_free(t_heredoc *hed_lst);
char	*remove_quotes(char *word);
void	free_double_char(char **str);
void	free_lst(t_lst **lst);
void	stack_cmd_else(t_cmd_tree *ct, char ***cmd);
void	start_play_executor(t_lst **tmp_lst, t_main *main);
void	play_executor(t_lst **tmp_lst, t_main *main);
void	tokenizer_if_is_meta(char *line, int *i, t_token *new, t_main *main);
void	turn_to_shell_mode(void);

int		is_directory(const char *path);
t_env	*make_env_lst(char **env);
void	executor(t_main *main);
int		heredoc(char **end, t_heredoc **hed_lst);

char	*get_env_value(t_main *main, char *key);
void	handle_heredoc(t_arg *arg);
int		throw_error(char *cmd, char *str, char *msg);
void	wft_lstadd_back_hed(t_heredoc **lst, t_heredoc *new);
void	signal_handler(int signo);
int		heredoc_handler(t_heredoc *hed_lst);

#endif