/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 19:48:59 by sumjo             #+#    #+#             */
/*   Updated: 2024/01/28 07:21:26 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	throw_error_exit(char *cmd, char *str, char *msg)
{
	ft_putstr_fd("minishell: ", 2);
	if (cmd)
	{
		ft_putstr_fd(cmd, 2);
	}
	if (str)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(str, 2);
	}
	if (msg)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(msg, 2);
	}
	ft_putstr_fd("\n", 2);
	exit(127);
}

int	is_directory(const char *path)
{
	struct stat	info;

	if (stat(path, &info) != 0)
		return (0);
	else
		return (((info.st_mode) & S_IFMT) == S_IFDIR);
}

char	**parse_commands(t_arg *arg, char **cmd)
{
	int		i;
	char	*arr;

	i = -1;
	if (arg->path == NULL)
		throw_error_exit(cmd[0], "No Such file or directory", 0);
	if (access(arr, F_OK) == 0)
		return (cmd);
	while (arg->path[++i])
	{
		arr = wft_strdup(arg->path[i]);
		arr = wft_strjoin(arr, wft_strdup(cmd[0]));
		if (access(arr, F_OK) == 0)
		{
			cmd[0] = arr;
			return (cmd);
		}
		free(arr);
	}
	if (has_char(cmd[0], '/'))
	{
		throw_error(cmd[0], "Not a directory", 0);
		exit(126);
	}
	return (cmd);
}

char	**return_commands(t_arg	*arg, char **cmd)
{
	if (ft_strncmp(cmd[0], "", 2) == 0)
	{
		throw_error(cmd[0], "command not found", 0);
		exit(127);
	}
	if (cmd[0][0] != '/' && cmd[0][0] != '.')
		return (parse_commands(arg, cmd));
	if (access(cmd[0], F_OK) == -1)
	{
		throw_error(cmd[0], "No Such file or directory", 0);
		exit(127);
	}
	if (access(cmd[0], X_OK) == -1)
	{
		throw_error(cmd[0], "Permission denied", 0);
		exit(126);
	}
	if (is_directory(cmd[0]))
	{
		throw_error(cmd[0], 0, "is a directory");
		exit(126);
	}
	return (cmd);
}
