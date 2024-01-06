/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 02:46:33 by sumjo             #+#    #+#             */
/*   Updated: 2024/01/06 20:05:07 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "builtin.h"

int	add_env(char ***env, char *str)
{
	int		i;

	i = 0;
	while ((*env)[i])
	{
		if (same_env((*env)[i], str))
		{
			if (has_char(str, '='))
			{
				modify_env(&str);
				(*env)[i] = ft_strdup(str);
			}
			return (0);
		}
		i++;
	}
	*env = set_env(*env, str);
	return (1);
}

char	**set_env(char **env, char *str)
{
	int		i;
	char	**dup_env;

	i = 0;
	while (env[i])
		i++;
	dup_env = (char **)malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (env[i])
	{
		dup_env[i] = ft_strdup(env[i]);
		i++;
	}
	ft_free_arr(env);
	modify_env(&str);
	dup_env[i] = ft_strdup(str);
	dup_env[i + 1] = NULL;
	return (dup_env);
}

int	export_check_str2(char *str, int *exit_status)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
	{
		throw_error("export", str, "not a valid identifier");
		*exit_status = 1;
		return (0);
	}
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			throw_error("export", str, "not a valid identifier");
			*exit_status = 1;
			return (0);
		}
		i++;
	}
	return (1);
}

int	export_check_str1(char **str)
{
	int	i;
	int	j;

	i = 1;
	j = 0;

	if (str[1] == NULL)
		return (0);
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (str[i][j] != ' ')
				return (1);
			j++;
		}
	}
	return (0);
}

int	ft_export(char ***env, char **str)
{
	char	**dup_env;
	int		exit_status;
	int		i;

	dup_env = ft_dup_env(*env);
	exit_status = 0;
	i = 0;
	if (!export_check_str1(str))
	{
		ft_print_env(ft_sort_env(dup_env));
		ft_free_arr(dup_env);
		return (exit_status);
	}
	while (str[++i])
	{
		if (!export_check_str2(str[i], &exit_status))
			continue ;
		add_env(&dup_env, str[i]);
	}
	*env = dup_env;
	return (exit_status);
}
// int	main(int argc, char **argv, char **env)
// {
// 	(void)argc;
// 	ft_export(&env, argv);
// 	ft_print_env(env);
// }
