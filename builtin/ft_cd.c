/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 19:27:37 by sumjo             #+#    #+#             */
/*   Updated: 2024/01/19 03:53:22 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

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
	}
	else
	{
		if (chdir(cmd[1]) == -1)
		{
			throw_error("cd", cmd[1], strerror(errno));
			return (1);
		}
	}
	return (0);
}
