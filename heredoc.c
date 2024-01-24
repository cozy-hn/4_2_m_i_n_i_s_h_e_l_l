/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiko <jiko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 04:34:07 by sumjo             #+#    #+#             */
/*   Updated: 2024/01/24 22:57:09 by jiko             ###   ########.fr       */
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

// void	heredoc(t_lst *lst)
// {
// 	int		fd;
// 	char	*line;
// 	char	*name;
// 	int		i;

// 	i = 0;
// 	name = ft_strdup("/tmp/heredoc");
// 	while (access(name, F_OK) == 0)
// 		name = wft_strjoin(name, ft_itoa(++i));
// 	fd = open(name, O_RDWR | O_CREAT | O_TRUNC, 0644);
// 	while (1)
// 	{
// 		ft_putstr_fd("> ", 1);
// 		// line = get_next_line(0);
// 		line = readline(0);
// 		if (ft_strncmp(line, lst->cmd[0], ft_strlen(lst->cmd[0])) == 0)
// 		{
// 			safe_free(line);
// 			break ;
// 		}
// 		ft_putendl_fd(line, fd);
// 		free(line);
// 	}
// 	lst->fd_in_name = name;
// 	close(fd);
// }

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

// int	make_directory(const char *path)
// {
// 	char	**cmd;
// 	int		pid;
// 	int		status;

// 	cmd = wft_calloc(3, sizeof(char *));
// 	cmd[0] = wft_strdup("mkdir");
// 	cmd[1] = wft_strdup(path);
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		if (execve(cmd[0], cmd, NULL) != 0)
// 		{
// 			throw_error("mkdir", 0, strerror(errno));
// 			exit(1);
// 		}
// 		exit(0);
// 	}
// 	safe_free(cmd[0]);
// 	safe_free(cmd[1]);
// 	safe_free(cmd);
// 	waitpid(pid, &status, 0);
// 	if (WIFEXITED(status))
// 		return (WEXITSTATUS(status));
// 	return (0);
// }

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
