/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 04:25:00 by sumjo             #+#    #+#             */
/*   Updated: 2024/01/06 20:07:31 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include <stdio.h>

int	unset_env(char ***env, int env_idx)
{
	int		i;
	int		j;
	char	**new_dup_env;

	i = 0;
	j = 0;
	while ((*env)[i])
		i++;
	new_dup_env = (char **)malloc(sizeof(char *) * i);
	i = 0;
	while ((*env)[i])
	{
		if (i != env_idx)
		{
			new_dup_env[j] = ft_strdup((*env)[i]);
			j++;
		}
		i++;
	}
	new_dup_env[j] = NULL;
	ft_free_arr(*env);
	*env = new_dup_env;
	return (0);
}

int	unset_check_str(char *str, int *exit_status)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[0]))
	{
		throw_error("unset", str, "not a valid identifier");
		*exit_status = 1;
		return (0);
	}
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			throw_error("unset", str, "not a valid identifier");
			*exit_status = 1;
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_unset(char ***env, char **str)
{
	int		i;
	int		j;
	int		exit_status;
	char	**dup_env;

	i = 0;
	if (!str[1])
		return (0);
	dup_env = ft_dup_env(*env);
	while (str[++i])
	{
		j = -1;
		if (!unset_check_str(str[i], &exit_status))
			continue ;
		while (dup_env[++j])
		{
			if (same_env(dup_env[j], str[i]))
			{
				unset_env(&dup_env, j);
				break ;
			}
		}
	}
	*env = dup_env;
	return (exit_status);
}

int main(int argc, char** argv, char **env)
{
	argc = 0;

	char **arr = (char **)malloc(sizeof(char *) * 10);
	arr[0] = ft_strdup("command");
	arr[1] = ft_strdup("a=1");
	arr[2] = ft_strdup("b=2");
	arr[3] = ft_strdup("c=3");
	arr[4] = ft_strdup("d=4");
	arr[5] = ft_strdup("e=5");
	arr[6] = ft_strdup("f=6");
	arr[7] = ft_strdup("g=7");
	arr[8] = ft_strdup("h=8");
	arr[9] = NULL;
	ft_export(&env, arr);
	ft_unset(&env, argv);
	// ft_print_env(env);
	// system("leaks a.out");
	return 0;
}
