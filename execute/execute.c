
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../libft/libft.h"

static char **env_;

typedef struct s_list1{
    int     fd_in;
    int     fd_out;
	char	**cmd;
    int     prev_pipe;
	struct s_list1 *next;
} t_list1;

typedef struct s_arg
{
	char	**env;
	char	**path;
	t_list1	*lst;
} t_arg;

int	throw_error(char *cmd, char *str, char *msg)
{
	ft_putendl_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("':", 2);
	ft_putendl_fd(msg, 2);
	return (1);
}

void	parse_commands(t_arg *arg, char **cmd)
{
	int		i;
	char	*arr;

	i = 0;
	while (arg->path[i])
	{
		arr = ft_strdup(arg->path[i]);
		arr = ft_strjoin(arr, cmd[0]);
		if (access(arr, F_OK) == 0)
		{
			cmd[0] = arr;
			return ;
		}
		free(arr);
		i++;
	}
	throw_error("command not found", cmd[0], "");
}

char	**return_commands(t_arg *arg, char **cmd)
{
	if (cmd[0][0] != '/')
	{
		parse_commands(arg, cmd);
		return (cmd);
	}
	return (cmd);
}

void	run_command(t_list1 *lst)
{
	int			pid;
	int			pipe_fd[2];

	pipe(pipe_fd);
	pid = fork();
	if (pid == 0)
	{
		close(pipe_fd[0]);
		if (lst->fd_in != -1)
			dup2(lst->fd_in, STDIN_FILENO);
		else
			dup2(lst->prev_pipe, STDIN_FILENO);
		if (lst->fd_out != -1)
			dup2(lst->fd_out, STDOUT_FILENO);
		else
			dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		execve(lst->cmd[0], lst->cmd, env_);
	}
	else
	{
		close(lst->prev_pipe);
		lst->next->prev_pipe = pipe_fd[0];
		close(pipe_fd[1]);
		wait(NULL);
	}
}
void run_first_command(t_list1 *lst)
{
	int			pid;
	int			pipe_fd[2];

	pipe(pipe_fd);
	pid = fork();
	if (pid == 0)
	{
		if (lst->fd_in != -1)
			dup2(lst->fd_in, STDIN_FILENO);
		if (lst->fd_out != -1)
			dup2(lst->fd_out, STDOUT_FILENO);
		else
			dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		execve(lst->cmd[0], lst->cmd, env_);
	}
	else
	{
		close(pipe_fd[1]);
		lst->next->prev_pipe = pipe_fd[0];
		wait(NULL);
	}
}

int run_last_command(t_list1 *lst)
{
	int			pid;

	pid = fork();
	if (pid == 0)
	{
		if (lst->fd_in != -1)
			dup2(lst->fd_in, STDIN_FILENO);
		else
			dup2(lst->prev_pipe, STDIN_FILENO);
		if (lst->fd_out != -1)
			dup2(lst->fd_out, STDOUT_FILENO);
		execve(lst->cmd[0], lst->cmd, env_);
	}
	return (pid);
}

int	execute(t_arg *arg)
{
	int		pid;
	int		status;
	t_list1	*lst;

	lst = arg->lst;
	while (lst)
	{
		lst->cmd = return_commands(arg, lst->cmd);
		if (!lst->next)
		{
			pid = run_last_command(lst);
			waitpid(pid, &status, 0);
		}
		else
		{
			if (lst->prev_pipe == -1)
				run_first_command(lst);
			else
				run_command(lst);
		}
		lst = lst->next;
	}
	return (status);
}

void	is_valid_command(t_arg *arg, char **cmd)
{
	int		is_valid;
	int		i;
	char	*arr;

	i = -1;
	is_valid = 0;
	while (arg->path[++i])
	{
		arr = ft_strdup(arg->path[i]);
		arr = ft_strjoin(arr, cmd[0]);
		if (access(arr, F_OK) == 0)
		{
			is_valid = 1;
			free(arr);
			break ;
		}
		free(arr);
	}
	if (is_valid == 0)
		throw_error("command not found", cmd[0], "");
}

// void	check_commands(t_arg *arg, char **av)
// {
// 	int		i;
// 	char	**cmd;

// 	i = 1;
// 	while (++i < ac - 1)
// 	{
// 		cmd = ft_split(av[i], ' ');
// 		is_valid_command(arg, cmd);
// 	}
// }

char	*return_path(char **env)
{
	char	*arr;
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp("PATH=", env[i], 5) == 0)
		{
			arr = ft_strdup(env[i] + 5);
			return (arr);
		}
		i++;
	}
	throw_error("PATH not found", "", "");
	exit(1);
}

void	get_path(t_arg *arg, char **env)
{
	char	*arr;
	int		i;

	i = 0;
	arr = return_path(env);
	arg->path = ft_split(arr, ':');
	while (arg->path[i])
	{
		arg->path[i] = ft_strjoin(arg->path[i], "/");
		i++;
	}
	free(arr);
}

int init_arg(t_arg *arg, char **env)
{
	get_path(arg, env);
	arg->env = env;
	return (0);
}
t_list1 *mock_lst()
{
	t_list1  *lst;
	t_list1  *tmp;

	lst = malloc(sizeof(t_list1));
	lst->fd_in = -1;
	lst->fd_out = -1;
	lst->cmd = malloc(sizeof(char *) * 3);
	lst->cmd[0] = strdup("ls");
	lst->cmd[1] = strdup("-l");
	lst->cmd[2] = NULL;
	lst->prev_pipe = -1;
	lst->next = malloc(sizeof(t_list1));
	tmp = lst->next;
	tmp->fd_in = -1;
	tmp->fd_out = -1;
	tmp->cmd = malloc(sizeof(char *) * 3);
	tmp->cmd[0] = strdup("grep");
	tmp->cmd[1] = strdup("a");
	tmp->cmd[2] = NULL;
	tmp->prev_pipe = -1;
	tmp->next = malloc(sizeof(t_list1));
	// tmp = tmp->next;
	// tmp->fd_in = -1;
	// tmp->fd_out = -1;
	// tmp->cmd = malloc(sizeof(char *) * 3);
	// tmp->cmd[0] = strdup("wc");
	// tmp->cmd[1] = strdup("-l");
	// tmp->cmd[2] = NULL;
	// tmp->prev_pipe = -1;
	tmp->next = NULL;
	return (lst);
}

int main(int ac, char **av, char **env)
{
	ac = 0;
	av = 0;

	t_arg   *arg;
	t_list1  *lst;
	int     status;

	arg = malloc(sizeof(t_arg));
	init_arg(arg, env);
	lst = mock_lst();
	arg->lst = lst;

	status = execute(arg);
	return (status);
}

