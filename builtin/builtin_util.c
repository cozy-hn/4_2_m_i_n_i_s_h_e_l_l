/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 16:15:56 by josumin           #+#    #+#             */
/*   Updated: 2024/01/24 05:12:18 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	has_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	env_len(char *env)
{
	int	i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	return (i);
}

int	same_env(char *env, char *str)
{
	if ((int)ft_strlen(str) == env_len(env)
		&& ft_strncmp(env, str, env_len(env) + 1) == 0)
		return (1);
	return (0);
}

char	**ft_dup_env(char **env)
{
	int		i;
	char	**dup_env;

	i = 0;
	while (env[i])
		i++;
	dup_env = wft_calloc(i + 1, sizeof(char *));
	i = 0;
	while (env[i])
	{
		dup_env[i] = ft_strdup(env[i]);
		i++;
	}
	dup_env[i] = NULL;
	return (dup_env);
}

int	ft_free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		safe_free(arr[i]);
		i++;
	}
	safe_free(arr);
	return (0);
}
