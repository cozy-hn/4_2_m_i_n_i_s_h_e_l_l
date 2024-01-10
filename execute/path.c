/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 19:39:21 by sumjo             #+#    #+#             */
/*   Updated: 2024/01/10 19:34:57 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

char	*return_path(char **env)
{
	char	*arr;
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp("PATH=", env[i], 5) == 0)
		{
			arr = ft_strdup(env[i] + 5);
			return (arr);
		}
		i++;
	}
	throw_error("PATH not found", "", "");
	return (NULL);
}

void	get_path(t_arg *arg, char **env)
{
	char	*arr;
	int		i;

	i = 0;
	arr = return_path(env);
	arg->path = ft_split(arr, ':');
	while (arg->path[i])
	{
		arg->path[i] = ft_strjoin(arg->path[i], "/");
		i++;
	}
	free(arr);
}
