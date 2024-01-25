/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiko <jiko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 04:34:07 by sumjo             #+#    #+#             */
/*   Updated: 2024/01/25 21:14:11 by jiko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_heredoc(t_arg *arg)
{
	t_lst	*lst;

	lst = arg->lst;
	while (lst)
	{
		if (lst->in_type == T_L_D_REDIR)
		{
			if (access(lst->fd_in_name, F_OK) == 0)
				unlink(lst->fd_in_name);
		}
		lst = lst->next;
	}
}

char	*avoid_duplicate_name(void)
{
	char	*name;
	char	*tmp;
	int		i;

	i = 0;
	tmp = wft_strdup("./.tmp");
	name = tmp;
	while (access(name, F_OK) == 0)
	{
		safe_free(name);
		tmp = wft_strdup("./.tmp");
		name = wft_strjoin(tmp, ft_itoa(++i));
	}
	return (name);
}

int	is_directory(const char *path)
{
	struct stat	info;

	if (stat(path, &info) != 0)
		return (0);
	else
		return (((info.st_mode) & S_IFMT) == S_IFDIR);
}

void	heredoc(char **end)
{
	int		fd;
	char	*line;
	char	*name;
	int		i;

	i = 0;
	name = avoid_duplicate_name();
	fd = open(name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			printf("\033[A");
			printf("> ");
			break ;
		}
		if (ft_strncmp(line, *end, ft_strlen(*end) + 1) == 0)
		{
			safe_free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		safe_free(line);
	}
	close(fd);
	safe_free(*end);
	*end = name;
}
