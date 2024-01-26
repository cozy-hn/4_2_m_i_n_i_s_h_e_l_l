/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 20:06:22 by sumjo             #+#    #+#             */
/*   Updated: 2024/01/26 12:22:23 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_bonus.h"

void	run_middle(t_lst *lst, t_arg *arg, int *pipe_fd)
{
	int			pid;
	int			red;

	set_signal(DFL, DFL);
	pid = fork();
	if (pid == 0)
	{
		close(pipe_fd[0]);
		red = handle_redirection(lst);
		if (lst->fd_in != -1)
			dup2(lst->fd_in, STDIN_FILENO);
		else
			dup2(lst->prev_pipe, STDIN_FILENO);
		if (lst->fd_out != -1)
			dup2(lst->fd_out, STDOUT_FILENO);
		else
			dup2(pipe_fd[1], STDOUT_FILENO);
		if (!red)
			execute(lst, arg);
		exit(0);
	}
	set_signal(IGN, IGN);
	close(lst->prev_pipe);
	lst->next->prev_pipe = pipe_fd[0];
	close(pipe_fd[1]);
}

void	run_first(t_lst *lst, t_arg *arg, int *pipe_fd)
{
	int			pid;
	int			red;

	set_signal(DFL, DFL);
	pid = fork();
	if (pid == 0)
	{
		close(pipe_fd[0]);
		red = handle_redirection(lst);
		if (lst->fd_in != -1)
			dup2(lst->fd_in, STDIN_FILENO);
		if (lst->fd_out != -1)
			dup2(lst->fd_out, STDOUT_FILENO);
		else
			dup2(pipe_fd[1], STDOUT_FILENO);
		if (!red)
			execute(lst, arg);
		exit(0);
	}
	set_signal(IGN, IGN);
	close(pipe_fd[1]);
	lst->next->prev_pipe = pipe_fd[0];
}

int	run_last(t_lst *lst, t_arg *arg)
{
	int		pid;
	int		status;
	int		red;

	set_signal(DFL, DFL);
	pid = fork();
	if (pid == 0)
	{
		red = handle_redirection(lst);
		if (lst->fd_in != -1)
			dup2(lst->fd_in, STDIN_FILENO);
		else
			dup2(lst->prev_pipe, STDIN_FILENO);
		dup2(lst->fd_out, STDOUT_FILENO);
		if (!red)
			status = execute(lst, arg);
		else
			exit(1);
		exit(status);
	}
	set_signal(IGN, IGN);
	close(lst->prev_pipe);
	close_in_out_fds(arg);
	return (pid);
}

int	executor_helper(t_lst *lst, t_arg *arg)
{
	int	pipe_fd[2];
	int	pid;

	if (!lst->next)
	{
		pid = run_last(lst, arg);
		return (pid);
	}
	else
	{
		pipe(pipe_fd);
		if (lst->prev_pipe == -1)
			run_first(lst, arg, pipe_fd);
		else
			run_middle(lst, arg, pipe_fd);
	}
	return (0);
}

void	executor(t_arg *arg)
{
	int		pid;
	t_lst	*lst;

	pid = 0;
	if (is_builtin(arg->lst) && arg->lst->next == NULL)
	{
		if (handle_redirection(arg->lst) != 0)
		{
			close_in_out_fds(arg);
			return ;
		}
		g_exit = run_builtin_helper(arg->lst, arg);
		return ;
	}
	lst = arg->lst;
	while (lst)
	{
		pid = executor_helper(lst, arg);
		lst = lst->next;
	}
	ft_wait(pid);
	handle_heredoc(arg);
}
