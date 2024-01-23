/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 00:23:52 by sumjo             #+#    #+#             */
/*   Updated: 2024/01/24 07:46:47 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	connect_original_fd(t_lst *lst, int *fd)
{
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	if (lst->fd_in != -1)
		close(lst->fd_in);
	if (lst->fd_out != -1)
		close(lst->fd_out);
}

void	connect_redir(t_lst *lst)
{
	if (lst->fd_in != -1)
		dup2(lst->fd_in, STDIN_FILENO);
	if (lst->fd_out != -1)
		dup2(lst->fd_out, STDOUT_FILENO);
}

void	duplicate_original_fd(int *fd)
{
	fd[0] = dup(STDIN_FILENO);
	fd[1] = dup(STDOUT_FILENO);
}

int	run_builtin_helper(t_lst *lst, t_arg *arg)
{
	int	fd[2];
	int	status;

	duplicate_original_fd(fd);
	connect_redir(arg->lst);
	status = run_builtin(arg->lst, arg);
	connect_original_fd(lst, fd);
	return (status);
}
