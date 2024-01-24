/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 06:26:15 by sumjo             #+#    #+#             */
/*   Updated: 2024/01/24 09:31:14 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	close_in_out_fds(t_lst *lst)
{
	close(lst->fd_in);
	close(lst->fd_out);
}

int	handle_fd_input(t_lst *lst)
{
	int	fd;

	// if (lst->in_type != T_NONE)
	// {
	// 	fd = open(lst->fd_in_name, O_RDONLY);
	// 	if (fd == -1)
	// 	{
	// 		throw_error(lst->fd_in_name, 0, strerror(errno));
	// 		g_exit_status = 1;
	// 		return (1);
	// 	}
	// 	lst->fd_in = fd;
	// }
	
	if (lst->fd_in_name != NULL)
	{
		fd = open(lst->fd_in_name, O_RDONLY);
		if (fd == -1)
		{
			throw_error(lst->fd_in_name, 0, strerror(errno));
			g_exit_status = 1;
			return (1);
		}
		lst->fd_in = fd;
	}
	return (0);
}

int	handle_fd_output(t_lst *lst)
{
	int	fd;

	// if (lst->out_type != T_NONE)
	// {
	// 	if (lst->out_type == T_R_REDIR)
	// 		fd = open(lst->fd_out_name, O_CREAT | O_WRONLY, 0644);
	// 	else if (lst->out_type == T_R_D_REDIR)
	// 		fd = open(lst->fd_out_name, O_CREAT | O_APPEND | O_WRONLY, 0644);
	// 	if (fd == -1)
	// 	{
	// 		throw_error(lst->fd_out_name, 0, strerror(errno));
	// 		g_exit_status = 1;
	// 		return (1);
	// 	}
	// 	lst->fd_out = fd;
	// }

	if (lst->fd_out_name != NULL)
	{
		fd = open(lst->fd_out_name, O_CREAT | O_APPEND | O_WRONLY, 0644);
		if (fd == -1)
		{
			throw_error(lst->fd_out_name, 0, strerror(errno));
			g_exit_status = 1;
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
	error = handle_fd_output(lst);
	return (error);
}
