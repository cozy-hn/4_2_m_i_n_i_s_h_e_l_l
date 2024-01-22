/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiko <jiko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 20:06:22 by sumjo             #+#    #+#             */
/*   Updated: 2024/01/22 19:03:43 by jiko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	handle_redirection(t_lst *lst)
{
	int	fd[2];

	if (lst->fd_in_name != NULL)
	{
		fd[0] = open(lst->fd_in_name, O_RDONLY);
		if (fd[0] == -1)
		{
			throw_error(lst->fd_in_name, 0, strerror(errno));
			g_exit_status = 1;
			return (1);
		}
		lst->fd_in = fd[0];
	}
	if (lst->fd_out_name != NULL)
	{
		fd[1] = open(lst->fd_out_name,  O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (fd[1] == -1)
		{
			throw_error(lst->fd_out_name, 0, strerror(errno));
			g_exit_status = 1;
			return (1);
		}
		lst->fd_out = fd[1];
	}
	return (0);
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
		exit(status);
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
	{
		if (handle_redirection(arg->lst) != 0)
			return (1);
		g_exit_status = run_builtin_helper(arg->lst, arg);
		return (g_exit_status);
	}
	lst = arg->lst;
	while (lst)
	{
		if (handle_redirection(arg->lst) != 0)
		{
			lst = lst->next;
			continue ;
		}
		executor_helper(lst, arg, &status);
		lst = lst->next;
	}
	// handle_heredoc(arg);
	g_exit_status = WEXITSTATUS(status);
	return (status);
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

// }