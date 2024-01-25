/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 19:48:59 by sumjo             #+#    #+#             */
/*   Updated: 2024/01/26 05:00:54 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

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

	i = 0;
	if (arg->path == NULL)
	{
		throw_error(cmd[0], "No Such file or directory", 0);
		exit(127);
	}
	while (arg->path[i])
	{
		arr = wft_strdup(arg->path[i]);
		arr = wft_strjoin(arr, wft_strdup(cmd[0]));
		if (access(arr, F_OK) == 0)
		{
			cmd[0] = arr;
			return (cmd);
		}
		free(arr);
		i++;
	}
	throw_error(cmd[0], "command not found", 0);
	exit(127);
	return (0);
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
	if (is_directory(cmd[0]))
	{
		throw_error(cmd[0], 0, "is a directory");
		exit(126);
	}
	if (access(cmd[0], F_OK | X_OK) == -1)
	{
		throw_error(cmd[0], 0, strerror(errno));
		if (errno == 20 || errno == 13)
			exit(126);
		exit(127);
	}
	return (cmd);
}
