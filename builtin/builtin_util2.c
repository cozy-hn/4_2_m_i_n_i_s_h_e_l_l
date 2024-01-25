/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_util2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 03:09:27 by sumjo             #+#    #+#             */
/*   Updated: 2024/01/25 23:31:22 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	ft_print_env(char **env)
{
	int	i;
	int	j;

	i = 0;
	while (env[i])
	{
		ft_putstr_fd("declare -x ", 1);
		j = -1;
		while (env[i][++j])
		{
			ft_putchar_fd(env[i][j], 1);
			if (env[i][j] == '=')
				ft_putchar_fd('\"', 1);
		}
		if (has_char(env[i], '=') && env[i][j] == '\0')
			ft_putstr_fd("\"", 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
	return (0);
}

char	**ft_sort_env(char **env_arr, t_env *env_lst)
{
	char	*tmp;
	t_env	*tmp_lst;
	int		i;
	int		j;

	i = 0;
	while (env_arr[i])
	{
		j = i + 1;
		tmp_lst = env_lst->next;
		if (tmp_lst && ft_strncmp(env_lst->key, tmp_lst->key,
				ft_strlen(env_lst->key) + 1) > 0)
		{
			tmp = env_arr[i];
			env_arr[i] = env_arr[j];
			env_arr[j] = tmp;
		}
		i++;
		env_lst = env_lst->next;
	}
	return (env_arr);
}

int	throw_error(char *cmd, char *str, char *msg)
{
	ft_putstr_fd("minishell: ", 2);
	if (cmd)
	{
		ft_putstr_fd(cmd, 2);
	}
	if (str)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(str, 2);
	}
	if (msg)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(msg, 2);
	}
	ft_putstr_fd("\n", 2);
	return (1);
}

void	free_env_lst(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		safe_free(env->key);
		safe_free(env->value);
		safe_free(env);
		env = tmp;
	}
	return ;
}
