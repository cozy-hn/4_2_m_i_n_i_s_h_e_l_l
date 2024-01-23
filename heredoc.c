/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiko <jiko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 04:34:07 by sumjo             #+#    #+#             */
/*   Updated: 2024/01/23 23:22:22 by jiko             ###   ########.fr       */
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

void	heredoc(char	**end)
{
	int		fd;
	char	*line;
	char	*name;
	int		i;

	i = 0;
	name = ft_strdup("/tmp/heredoc");
	while (access(name, F_OK) == 0)
		name = wft_strjoin(name, ft_itoa(++i));
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

// int main ()
// {
//     t_lst *lst;
//     lst = (t_lst *)malloc(sizeof(t_lst));
//     lst->cmd = (char **)malloc(sizeof(char *) * 2);
//     lst->cmd[0] = ft_strdup("limiter");
//     lst->cmd[1] = NULL;
//     heredoc(lst);
//     printf("%s\n", lst->fd_in_name);
//     int fd = open(lst->fd_in_name, O_RDONLY);
//     char *line;

//         line = malloc(100);
//         read(fd, line, 100);
//         printf("%s\n", line);
//         free(line);

//     unlink(lst->fd_in_name);
//     return (0);
// }