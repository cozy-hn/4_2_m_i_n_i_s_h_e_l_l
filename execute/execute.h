#ifndef EXECUTE_H
# define EXECUTE_H

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../libft/libft.h"
#include "execute.h"

typedef struct s_lst{
    int     fd_in;
    int     fd_out;
	char	**cmd;
    int     prev_pipe;
	struct s_lst *next;
} t_lst;

typedef struct s_arg
{
	char	**env;
	char	**path;
	t_lst	*lst;
} t_arg;

char	*return_path(char **env);
void	get_path(t_arg *arg, char **env);
int		throw_error(char *cmd, char *str, char *msg);
void	parse_commands(t_arg *arg, char **cmd);
char	**return_commands(t_arg *arg, char **cmd);
int	init_arg(t_arg *arg, char **env);
t_lst *mock_lst();


# endif