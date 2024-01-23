/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 04:34:07 by sumjo             #+#    #+#             */
/*   Updated: 2024/01/24 05:20:04 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void handle_heredoc(t_arg *arg)
// {
// 	t_lst *lst;

// 	lst = arg->lst;
// 	while (lst)
// 	{
// 		// if (heredoc)
//         {
//             if (access(lst->fd_in_name, F_OK) == 0)
//                 unlink(lst->fd_in_name);
//         }
//         lst = lst->next;
// 	}
// }

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

char *avoid_duplicate_name(void)
{
	char *name;
	char *tmp;
	int i;

	i = 0;
	tmp = ft_strdup("/tmp/heredoc");
	name = tmp;
	while (access(tmp, F_OK) == 0)
	{
		if (name)
			safe_free(name);
		safe_free(tmp);
		tmp = ft_strdup("/tmp/heredoc");
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

	if (!is_directory("/tmp"))
	{
		// ft_putendl_fd("minishell: /tmp: Is a directory", 2);
		// return ;
	}
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

int main ()
{
	char *str = avoid_duplicate_name();
	printf("%s\n", str);
}