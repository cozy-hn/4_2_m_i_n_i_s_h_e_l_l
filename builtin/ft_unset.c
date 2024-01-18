/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 04:25:00 by sumjo             #+#    #+#             */
/*   Updated: 2024/01/14 20:16:37 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	unset_env(t_env **env, char *cmd)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = *env;
	prev = NULL;
	while (tmp)
	{
		if (same_env(tmp->key, cmd))
		{
			if (prev)
				prev->next = tmp->next;
			else
				*env = tmp->next;
			free(tmp->key);
			free(tmp->value);
			free(tmp);
			return (0);
		}
		prev = tmp;
		tmp = tmp->next;
	}
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
	*exit_status = 0;
	return (1);
}

int	ft_unset(t_env **env, char **cmd)
{
	int		i;
	int		exit_status;
	t_env	*tmp;

	if (!cmd[1])
		return (0);
	i = 0;
	while (cmd[++i])
	{
		if (unset_check_str(cmd[i], &exit_status))
		{
			tmp = *env;
			while (tmp)
			{
				if (same_env(tmp->key, cmd[i]))
				{
					unset_env(env, cmd[i]);
					break ;
				}
				tmp = tmp->next;
			}
		}
	}
	return (exit_status);
}

// int main(int argc, char** argv, char **env)
// {
// 	argc = 0;
// 	t_arg arg;
// 	t_lst lst;

// 	char **export_test = (char **)malloc(sizeof(char *) * 4);
// 	export_test[0] = ft_strdup("export");
// 	export_test[1] = ft_strdup("test=123");
// 	export_test[2] = ft_strdup("test2=456");
// 	export_test[3] = NULL;

// 	make_env_lst(&arg, env);
// 	ft_export(&arg, export_test);
// 	// char **arr = ft_sort_env(env_lst_to_arr(arg.env));
// 	// ft_print_env(arr);

// //unset test
// 	char **unset_test = (char **)malloc(sizeof(char *) * 4);
// 	unset_test[0] = ft_strdup("unset");
// 	unset_test[1] = ft_strdup("test");
// 	unset_test[2] = ft_strdup("TEST3");
// 	unset_test[3] = NULL;

// 	lst.cmd = argv;
// 	ft_unset(&arg, lst.cmd);
// 	char **arr = ft_sort_env(env_lst_to_arr(arg.env));
// 	ft_print_env(arr);
// }
