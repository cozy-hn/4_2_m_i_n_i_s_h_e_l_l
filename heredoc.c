/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 04:34:07 by sumjo             #+#    #+#             */
/*   Updated: 2024/01/26 01:15:24 by sumjo            ###   ########.fr       */
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

void	run_heredoc(char *name, char **end)
{
	int		fd;
	char	*line;

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
	exit(0);
}

int	heredoc(char **end)
{
	int		pid;
	int		status;
	char	*name;
	int		signo;

	name = avoid_duplicate_name();
	set_signal(HED, HED);
	pid = fork();
	if (pid == 0)
		run_heredoc(name, end);
	set_signal(IGN, IGN);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		signo = WTERMSIG(status);
		if (signo == SIGINT)
		{
			heredoc_handler(signo);
		}
	}
	safe_free(*end);
	*end = name;
	return (0);
}

// void	heredoc(char **end)
// {
// 	int	pid;

// 	set_signal(DFL, DFL);
// 	pid = fork();
// 	if (pid == 0)
// 		run_heredoc(end);
// 	else if (pid > 0)
// 		waitpid(pid, NULL, 0);

// }
