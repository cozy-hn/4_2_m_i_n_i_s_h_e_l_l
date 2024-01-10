/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josumin <josumin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 04:25:00 by sumjo             #+#    #+#             */
/*   Updated: 2024/01/09 21:52:04 by josumin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include <stdio.h>

int	unset_env(t_arg *arg, int env_idx)
{
	t_env	*tmp;
	t_env	*tmp2;
	int		i;

	i = 0;
	tmp = arg->env;
	if (env_idx == 0)
	{
		arg->env = tmp->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
		return (0);
	}
	while (i < env_idx - 1)
	{
		tmp = tmp->next;
		i++;
	}
	tmp2 = tmp->next;
	tmp->next = tmp2->next;
	free(tmp2->key);
	free(tmp2->value);
	free(tmp2);
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

int	ft_unset(t_arg *arg, char **cmd)
{
	int		i;
	int		j;
	int		exit_status;
	t_env	*tmp;

	if (!cmd[1])
		return (0);
	i = 0;
	exit_status = 0;
	while (cmd[++i])
	{
		if (unset_check_str(cmd[i], &exit_status))
		{
			j = 0;
			tmp = arg->env;
			while (tmp)
			{
				if (ft_strncmp(tmp->key, cmd[i], ft_strlen(cmd[i])) == 0
					&& ft_strlen(tmp->key) == ft_strlen(cmd[i]))
				{
					unset_env(arg, j);
					break ;
				}
				tmp = tmp->next;
				j++;
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
