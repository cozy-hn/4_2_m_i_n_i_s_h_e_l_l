/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 19:48:59 by sumjo             #+#    #+#             */
/*   Updated: 2024/01/14 18:34:42 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	parse_commands(t_arg *arg, char **cmd)
{
	int		i;
	char	*arr;

	i = 0;
	if (arg->path == NULL)
	{
		throw_error("No Such file or directory", cmd[0], "");
		exit(127);
	}
	while (arg->path[i])
	{
		arr = ft_strdup(arg->path[i]);
		arr = ft_strjoin(arr, cmd[0]);
		if (access(arr, F_OK) == 0)
		{
			cmd[0] = arr;
			return ;
		}
		free(arr);
		i++;
	}
	throw_error("No Such file or directory", cmd[0], "");
	exit(127);
}

char	**return_commands(t_arg	*arg, char **cmd)
{
	if (cmd[0][0] != '/' && cmd[0][0] != '.')
	{
		parse_commands(arg, cmd);
		return (cmd);
	}
	if (access(cmd[0], F_OK) == -1)
	{
		throw_error("No Such file or directory", cmd[0], "");
		exit(127);
	}
	return (cmd);
}
