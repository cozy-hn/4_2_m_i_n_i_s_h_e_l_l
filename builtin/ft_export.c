/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 02:46:33 by sumjo             #+#    #+#             */
/*   Updated: 2024/01/18 21:54:24 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	set_env(t_env *env, char *key, char *value)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, ft_strlen(key)) == 0)
		{
			if (value != NULL)
			{
				free(key);
				free(tmp->value);
				tmp->value = value;
			}
			return (0);
		}
		tmp = tmp->next;
	}
	while (env->next)
		env = env->next;
	env->next = wft_calloc(1, sizeof(t_env));
	env->next->key = key;
	env->next->value = value;
	env->next->next = NULL;
	return (0);
}

int	add_env(t_env *env, char *str)
{
	char	*key;
	char	*value;

	if (has_char(str, '='))
	{
		if (str[ft_strlen(str) - 1] == '=')
		{
			key = ft_strndup(str, ft_strchr(str, '='));
			value = ft_strdup("");
		}
		else
		{
			key = ft_strndup(str, ft_strchr(str, '='));
			value = ft_strdup(ft_strchr(str, '=') + 1);
		}
	}
	else
	{
		key = ft_strdup(str);
		value = 0;
	}
	set_env(env, key, value);
	return (0);
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

int	ft_export(t_env *env, char **cmd)
{
	char	**env_arr;
	int		exit_status;
	int		i;

	exit_status = 0;
	i = 0;
	if (cmd[1] == NULL)
	{
		env_arr = env_lst_to_arr(env);
		ft_print_env(ft_sort_env(env_arr));
		ft_free_arr(env_arr);
		return (exit_status);
	}
	while (cmd[++i])
	{
		if (!export_check_str2(cmd[i], &exit_status))
			continue ;
		add_env(env, cmd[i]);
	}
	return (exit_status);
}
// int	main(int argc, char **argv, char **env)
// {
// 	argc = 0;
// 	t_arg arg;
// 	t_lst lst;

// 	lst.cmd = argv;

// 	make_env_lst(&arg, env);
// 	ft_export(&arg, lst->cmd);
// 	char **arr = ft_sort_env(env_lst_to_arr(arg.env));
// 	ft_print_env(arr);
// }
