/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 19:27:37 by sumjo             #+#    #+#             */
/*   Updated: 2024/01/14 19:00:24 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int ft_cd(t_arg *arg, char **cmd)
{
	char *home;

	if (cmd[1] == NULL)
	{
		home = get_env_value(arg->env, "HOME");
		if (chdir(home) == -1)
		{
			printf("path : %s not found\n", home);
			exit(1);
		}
		else
			printf("current path : %s\n", getcwd(NULL, 0));
		return (0);
	}
	else if (cmd[2] == NULL)
	{
		if (chdir(cmd[1]) == -1)
		{
			printf("fail! current path : %s\n", getcwd(NULL, 0));
			exit(1);
		}
		else
			printf("current path : %s\n", getcwd(NULL, 0));
	}
	else
	{
		printf("cd: too many arguments\n");
		exit(1);
	}
	return (0);
}
