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
char	*return_path(char **env);
void	get_path(t_arg *arg, char **env);
int		throw_error(char *cmd, char *str, char *msg);
void	parse_commands(t_arg *arg, char **cmd);
int		init_arg(t_arg *arg, char **env);
int		is_builtin(t_lst *lst);
int		run_builtin(t_lst *lst, t_arg *arg);
int		init_arg(t_arg *arg, char **env);
t_lst	*mock_lst(char *str);
int		execute(t_lst *lst, t_arg *arg);


# endif
