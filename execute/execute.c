/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 20:06:22 by sumjo             #+#    #+#             */
/*   Updated: 2024/01/25 07:09:29 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	run_middle(t_lst *lst, t_arg *arg, int *pipe_fd)
{
	int			pid;

	set_signal(DFL, DFL);
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
		execute(lst, arg);
		exit(0);
	}
	set_signal(IGN, IGN);
	close(lst->prev_pipe);
	lst->next->prev_pipe = pipe_fd[0];
	close(pipe_fd[1]);
	close_in_out_fds(lst);
}

void	run_first(t_lst *lst, t_arg *arg, int *pipe_fd)
{
	int			pid;

	set_signal(DFL, DFL);
	pid = fork();
	if (pid == 0)
	{
		close(pipe_fd[0]);
		dup2(lst->fd_in, STDIN_FILENO);
		if (lst->fd_out != -1)
			dup2(lst->fd_out, STDOUT_FILENO);
		else
			dup2(pipe_fd[1], STDOUT_FILENO);
		execute(lst, arg);
		exit(0);
	}
	set_signal(IGN, IGN);
	close(pipe_fd[1]);
	lst->next->prev_pipe = pipe_fd[0];
	close_in_out_fds(lst);
}

int	run_last(t_lst *lst, t_arg *arg)
{
	int		pid;
	int		status;

	set_signal(DFL, DFL);
	pid = fork();
	if (pid == 0)
	{
		if (lst->fd_in != -1)
			dup2(lst->fd_in, STDIN_FILENO);
		else
			dup2(lst->prev_pipe, STDIN_FILENO);
		dup2(lst->fd_out, STDOUT_FILENO);
		status = execute(lst, arg);
		exit(status);
	}
	set_signal(IGN, IGN);
	close(lst->prev_pipe);
	close_in_out_fds(lst);
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

	if (is_builtin(arg->lst) && arg->lst->next == NULL)
	{
		if (handle_redirection(arg->lst) != 0)
			return ;
		g_exit_status = run_builtin_helper(arg->lst, arg);
		return ;
	}
	lst = arg->lst;
	while (lst)
	{
		if (handle_redirection(lst) != 0)
		{
			lst = lst->next;
			continue ;
		}
		pid = executor_helper(lst, arg);
		lst = lst->next;
	}
	ft_wait(pid, arg);
	handle_heredoc(arg);
}

// int main (int ac, char **av, char **env)
// {
// 	ac = 0;
// 	av = 0;
// 	t_arg arg;
// 	t_lst *lst;

// 	arg.env = make_env_lst(env);
// 	lst = mock_lst();

// 	arg.lst = lst;

// 	executor(&arg);

// 	printf("g_exit_status = %d\n", g_exit_status);
// 	return(g_exit_status);

// }tcgetattr(STDIN_FILENO, &term);