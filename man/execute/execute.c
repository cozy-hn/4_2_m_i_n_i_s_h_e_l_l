/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 20:06:22 by sumjo             #+#    #+#             */
/*   Updated: 2024/01/28 06:34:47 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	run_middle(t_lst *lst, t_main *main, int *pipe_fd)
{
	int			pid;
	int			red;

	default_terminal();
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
			execute(lst, main);
		exit(0);
	}
	set_signal(IGN, IGN);
	close(lst->prev_pipe);
	lst->next->prev_pipe = pipe_fd[0];
	close(pipe_fd[1]);
}

void	run_first(t_lst *lst, t_main *main, int *pipe_fd)
{
	int			pid;
	int			red;

	default_terminal();
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
			execute(lst, main);
		exit(0);
	}
	set_signal(IGN, IGN);
	close(pipe_fd[1]);
	lst->next->prev_pipe = pipe_fd[0];
}

int	run_last(t_lst *lst, t_main *main)
{
	int		pid;
	int		status;
	int		red;

	default_terminal();
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
			status = execute(lst, main);
		else
			exit(1);
		exit(status);
	}
	set_signal(IGN, IGN);
	close(lst->prev_pipe);
	close_in_out_fds(main->arg);
	return (pid);
}

int	executor_helper(t_lst *lst, t_main *main)
{
	int	pipe_fd[2];
	int	pid;

	if (!lst->next)
	{
		pid = run_last(lst, main);
		return (pid);
	}
	else
	{
		pipe(pipe_fd);
		if (lst->prev_pipe == -1)
			run_first(lst, main, pipe_fd);
		else
			run_middle(lst, main, pipe_fd);
	}
	return (0);
}

void	executor(t_main *main)
{
	int		pid;
	t_lst	*lst;

	pid = 0;
	if (is_builtin(main->arg->lst) && main->arg->lst->next == NULL)
	{
		if (handle_redirection(main->arg->lst) != 0)
		{
			main->exit_code = 1;
			close_in_out_fds(main->arg);
			return ;
		}
		main->exit_code = run_builtin_helper(main);
		return ;
	}
	lst = main->arg->lst;
	while (lst)
	{
		pid = executor_helper(lst, main);
		lst = lst->next;
	}
	ft_wait(pid, main);
	handle_heredoc(main->arg);
}
