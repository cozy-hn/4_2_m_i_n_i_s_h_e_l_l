/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 19:27:37 by sumjo             #+#    #+#             */
/*   Updated: 2024/01/24 04:57:15 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int set_pwd(t_arg *arg)
{
	char **pwd;
	char **oldpwd;

	pwd = wft_calloc(3, sizeof(char *));
	oldpwd = wft_calloc(3, sizeof(char *));

	pwd[0] = ft_strdup("export");
	pwd[1] = wft_strjoin(ft_strdup("PWD="), getcwd(NULL, 0));
	pwd[2] = NULL;
	oldpwd[0] = ft_strdup("export");
	oldpwd[1] = wft_strjoin(ft_strdup("OLDPWD="), get_env_value(arg->env, "PWD"));
	oldpwd[2] = NULL;
	write(1, "hello\n", 6);
	ft_export(arg->env, pwd);
	ft_export(arg->env, oldpwd);
	ft_free_arr(pwd);
	ft_free_arr(oldpwd);
	return (0);
}

int ft_cd(t_arg *arg, char **cmd)
{
	char *home;

	if (cmd[1] == NULL)
	{
		home = get_env_value(arg->env, "HOME");
		if (home == NULL)
		{
			throw_error("cd", 0, "HOME not set");
			return (1);
		}
		chdir(home);
		return (0);
	}
	else
	{
		if (chdir(cmd[1]) == -1)
		{
			throw_error("cd", cmd[1], strerror(errno));
			return (1);
		}
		set_pwd(arg);
	}
	return (0);
}
