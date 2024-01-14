#ifndef EXECUTE_H
# define EXECUTE_H

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../minishell.h"
#include "../builtin/builtin.h"

char	**return_commands(t_arg *arg, char **cmd);
void	get_path(t_arg *arg);
char	*return_path(t_env *env);
int		throw_error(char *cmd, char *str, char *msg);
void	parse_commands(t_arg *arg, char **cmd);
int		is_builtin(t_lst *lst);
int		run_builtin(t_lst *lst, t_arg *arg);
int		init_arg(t_arg *arg);
t_arg	*mock_lst(char *str, char **env);
int		execute(t_lst *lst, t_arg *arg);
int		executor(t_arg *arg);

# endif
