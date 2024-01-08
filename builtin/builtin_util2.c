/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_util2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 03:09:27 by sumjo             #+#    #+#             */
/*   Updated: 2024/01/08 20:09:54 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	ft_print_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (env[i][ft_strlen(env[i]) - 1] == '=')
		{
			ft_putstr_fd(env[i], 1);
			ft_putendl_fd("\"\"", 1);
		}
		else
			ft_putendl_fd(env[i], 1);
		i++;
	}
	return (0);
}

char	**ft_sort_env(char **env)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[j])
		{
			if (ft_strncmp(env[i], env[j], ft_strlen(env[j])) < 0)
			{
				tmp = env[i];
				env[i] = env[j];
				env[j] = tmp;
			}
			j++;
		}
		i++;
	}
	return (env);
}

int	modify_env(char **str)
{
	int	i;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '=')
		{
			if ((*str)[i + 1] == '\0')
			{
				*str = ft_strjoin(*str, "\"\"");
				return (0);
			}
			else
				return (0);
		}
		i++;
	}
	return (0);
}

int	throw_error(char *cmd, char *str, char *msg)
{
	ft_putendl_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("':", 2);
	ft_putendl_fd(msg, 2);
	return (1);
}
