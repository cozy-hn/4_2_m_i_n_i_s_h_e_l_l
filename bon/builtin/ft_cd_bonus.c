/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 19:27:37 by sumjo             #+#    #+#             */
/*   Updated: 2024/01/30 06:59:12 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_bonus.h"

int	set_pwd(t_arg *arg)
{
	char	**pwd;
	char	**oldpwd;
	char	*now_path;

	now_path = getcwd(NULL, 0);
	if (now_path == NULL)
	{
		throw_error("cd", 0, "error retrieving current directory");
		return (1);
	}
	pwd = wft_calloc(3, sizeof(char *));
	oldpwd = wft_calloc(3, sizeof(char *));
	pwd[0] = wft_strdup("export");
	pwd[1] = wft_strjoin(ft_strdup("PWD="), now_path);
	oldpwd[0] = wft_strdup("export");
	oldpwd[1] = wft_strjoin(ft_strdup("OLDPWD="),
			get_env_value(arg->env, "PWD"));
	ft_export(arg->env, pwd);
	ft_export(arg->env, oldpwd);
	ft_free_arr(pwd);
	ft_free_arr(oldpwd);
	return (0);
}

int	ft_cd(t_arg *arg, char **cmd)
{
	char	*home;

	if (cmd[1] == NULL)
	{
		home = get_env_value(arg->env, "HOME");
		if (home == NULL)
			return (throw_error("cd", 0, "HOME not set"));
		if (chdir(home) != 0)
			return (throw_error("cd", home, strerror(errno)));
		return (0);
	}
	else
	{
		if (chdir(cmd[1]) == -1)
			return (throw_error("cd", cmd[1], strerror(errno)));
		set_pwd(arg);
	}
	return (0);
}
