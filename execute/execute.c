/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 20:06:22 by sumjo             #+#    #+#             */
/*   Updated: 2024/01/07 21:47:45 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	run_execve(t_lst *lst, t_arg *arg)
{
	char	**cmd;

	cmd = return_commands(arg, lst->cmd);
	return (execve(cmd[0], cmd, arg->env));
}

int	is_builtin(t_lst *lst)
{
	if (ft_strncmp(lst->cmd[0], "echo", 4) == 0)
		return (1);
	else if (ft_strncmp(lst->cmd[0], "cd", 2) == 0)
		return (1);
	else if (ft_strncmp(lst->cmd[0], "pwd", 3) == 0)
		return (1);
	else if (ft_strncmp(lst->cmd[0], "export", 6) == 0)
		return (1);
	else if (ft_strncmp(lst->cmd[0], "unset", 5) == 0)
		return (1);
	else if (ft_strncmp(lst->cmd[0], "env", 3) == 0)
		return (1);
	else if (ft_strncmp(lst->cmd[0], "exit", 4) == 0)
		return (1);
	return (0);
}

int run_builtin(t_lst *lst, t_arg *arg)
{
	// if (ft_strncmp(lst->cmd[0], "echo", 4) == 0)
	// 	return (ft_echo(lst->cmd));
	// else if (ft_strncmp(lst->cmd[0], "cd", 2) == 0)
	// 	return (ft_cd(lst->cmd, arg));
	// else if (ft_strncmp(lst->cmd[0], "pwd", 3) == 0)
	// 	return (ft_pwd());
	// else if (ft_strncmp(lst->cmd[0], "export", 6) == 0)
	// 	return (ft_export(lst->cmd, arg));
	// else if (ft_strncmp(lst->cmd[0], "unset", 5) == 0)
	// 	return (ft_unset(lst->cmd, arg));
	// else if (ft_strncmp(lst->cmd[0], "env", 3) == 0)
	// 	return (ft_env(arg));
	// else if (ft_strncmp(lst->cmd[0], "exit", 4) == 0)
	// 	return (ft_exit(lst->cmd));
	(void)arg;
	(void)lst;
	return (0);
}

int	execute(t_lst *lst, t_arg *arg)
{
	if (is_builtin(lst))
		return (run_builtin(lst, arg));
	else
		return (run_execve(lst, arg));
}

void	run_middle(t_lst *lst, t_arg *arg, int *pipe_fd)
{
	int			pid;

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
		execute(lst, arg);
	}
	else
	{
		close(lst->prev_pipe);
		lst->next->prev_pipe = pipe_fd[0];
		close(pipe_fd[1]);
		wait(NULL);
	}
}


void	run_first(t_lst *lst, t_arg *arg, int *pipe_fd)
{
	int			pid;

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
		execute(lst, arg);
	}
	else
	{
		close(pipe_fd[1]);
		lst->next->prev_pipe = pipe_fd[0];
		wait(NULL);
	}
}

int	run_last(t_lst *lst, t_arg *arg)
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
		return (execute(lst, arg));
	}
	return (pid);
}

int	executor(t_arg *arg)
{
	int		pid;
	int		status;
	t_lst	*lst;
	int		pipe_fd[2];

	lst = arg->lst;
	while (lst)
	{
		if (!lst->next)
		{
			pid = run_last(lst, arg);
			waitpid(pid, &status, 0);
		}
		else
		{
			pipe(pipe_fd);
			if (lst->prev_pipe == -1)
				run_first(lst, arg, pipe_fd);
			else
				run_middle(lst, arg, pipe_fd);
		}
		lst = lst->next;
	}
	return (status);
}

int	main(int ac, char **av, char **env)
{
	t_arg	*arg;
	t_lst	*lst;
	int		status;

	ac = 0;
	av = 0;

	arg = malloc(sizeof(t_arg));
	init_arg(arg, env);
	lst = mock_lst();
	arg->lst = lst;

	status = executor(arg);
	return (status);
}

