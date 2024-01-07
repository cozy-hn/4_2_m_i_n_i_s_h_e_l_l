/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 20:06:22 by sumjo             #+#    #+#             */
/*   Updated: 2024/01/07 20:42:46 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	run_command(t_lst *lst, t_arg *arg, int *pipe_fd)
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
		if (execve(lst->cmd[0], lst->cmd, arg->env) == -1)
			return ;
	}
	else
	{
		close(lst->prev_pipe);
		lst->next->prev_pipe = pipe_fd[0];
		close(pipe_fd[1]);
		wait(NULL);
	}
}


void	run_first_command(t_lst *lst, t_arg *arg, int *pipe_fd)
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
		if (execve(lst->cmd[0], lst->cmd, arg->env) == -1)
			return ;
	}
	else
	{
		close(pipe_fd[1]);
		lst->next->prev_pipe = pipe_fd[0];
		wait(NULL);
	}
}

int	run_last_command(t_lst *lst, t_arg *arg)
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
		execve(lst->cmd[0], lst->cmd, arg->env);
	}
	return (pid);
}

int	execute(t_arg *arg)
{
	int		pid;
	int		status;
	t_lst	*lst;
	int		pipe_fd[2];

	lst = arg->lst;
	while (lst)
	{
		lst->cmd = return_commands(arg, lst->cmd);
		if (!lst->next)
		{
			pid = run_last_command(lst, arg);
			waitpid(pid, &status, 0);
		}
		else
		{
			pipe(pipe_fd);
			if (lst->prev_pipe == -1)
				run_first_command(lst, arg, pipe_fd);
			else
				run_command(lst, arg, pipe_fd);
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

	status = execute(arg);
	return (status);
}

