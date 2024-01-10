/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 19:27:37 by sumjo             #+#    #+#             */
/*   Updated: 2024/01/10 16:42:30 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "builtin.h"

int ft_cd(t_arg *arg, char **cmd)
{
	char *home;

	if (cmd[1] == NULL)
	{
		home = get_env_value(arg->env, "HOME");
		if (chdir(home) == 0)
			printf("success! current path : %s\n", getcwd(NULL, 0));
		else
		{
			printf("fail! current path : %s\n", getcwd(NULL, 0));
			exit(1);
		}
	}
	else if (cmd[2] == NULL)
	{
		if (chdir(cmd[1]) == 0)
			printf("success! current path : %s\n", getcwd(NULL, 0));
		else
		{
			printf("fail! current path : %s\n", getcwd(NULL, 0));
			exit(1);
		}
	}
	else
	{
		printf("cd: too many arguments\n");
		exit(1);
	}
	return (0);
}
