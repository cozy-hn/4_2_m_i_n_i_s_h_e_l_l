/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirection_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiko <jiko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 06:26:15 by sumjo             #+#    #+#             */
/*   Updated: 2024/01/31 20:28:52 by jiko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_bonus.h"

void	close_in_out_fds(t_arg *arg)
{
	t_lst	*lst;

	lst = arg->lst;
	while (lst)
	{
		if (lst->fd_in != -1)
			close(lst->fd_in);
		if (lst->fd_out != -1)
			close(lst->fd_out);
		lst = lst->next;
	}
}

int	handle_fd_input(t_lst *lst)
{
	int	fd;

	if (lst->in_type != T_NONE)
	{
		fd = open(lst->fd_in_name, O_RDONLY);
		if (fd == -1)
		{
			throw_error(lst->fd_in_name, 0, strerror(errno));
			return (1);
		}
		lst->fd_in = fd;
	}
	return (0);
}

int	handle_fd_output(t_lst *lst)
{
	int	fd;

	fd = 0;
	if (lst->out_type != T_NONE)
	{
		if (lst->out_type == T_R_REDIR)
			fd = open(lst->fd_out_name, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		else if (lst->out_type == T_R_D_REDIR)
			fd = open(lst->fd_out_name, O_CREAT | O_APPEND | O_WRONLY, 0644);
		if (fd == -1)
		{
			throw_error(lst->fd_out_name, 0, strerror(errno));
			return (1);
		}
		lst->fd_out = fd;
	}
	return (0);
}

int	handle_redirection(t_lst *lst)
{
	int	error;

	error = handle_fd_input(lst);
	if (error)
		handle_fd_output(lst);
	else
		error = handle_fd_output(lst);
	return (error);
}
