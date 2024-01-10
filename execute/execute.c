/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 20:06:22 by sumjo             #+#    #+#             */
/*   Updated: 2024/01/10 20:10:57 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

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
		exit(0);
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
		exit(0);
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
	int			status;

	pid = fork();
	if (pid == 0)
	{
		if (lst->fd_in != -1)
			dup2(lst->fd_in, STDIN_FILENO);
		else
			dup2(lst->prev_pipe, STDIN_FILENO);
		if (lst->fd_out != -1)
			dup2(lst->fd_out, STDOUT_FILENO);
		status = execute(lst, arg);
		exit(WEXITSTATUS(status));
	}
	return (pid);
}

void	executor_helper(t_lst *lst, t_arg *arg, int *status)
{
	int	pipe_fd[2];
	int	pid;

	if (!lst->next)
	{
		pid = run_last(lst, arg);
		waitpid(pid, status, 0);
	}
	else
	{
		pipe(pipe_fd);
		if (lst->prev_pipe == -1)
			run_first(lst, arg, pipe_fd);
		else
			run_middle(lst, arg, pipe_fd);
	}
}

int	executor(t_arg *arg)
{
	int		status;
	t_lst	*lst;

	if (is_builtin(arg->lst) && arg->lst->next == NULL)
		return (run_builtin(arg->lst, arg));
	lst = arg->lst;
	while (lst)
	{
		executor_helper(lst, arg, &status);
		lst = lst->next;
	}
	return (status);
}

int	main(int ac, char **av, char **env)
{
	t_arg	*arg;
	t_lst	*lst;

	ac = 0;
	av = 0;

	arg = malloc(sizeof(t_arg));
	init_arg(arg, env);
	while (1)
	{
		char *line = readline("minishell$ ");
		lst = mock_lst(line);
		arg->lst = lst;
		g_exit_status = executor(arg);
		free(line);
		free(arg->lst);
	}	
	return (g_exit_status);
}
