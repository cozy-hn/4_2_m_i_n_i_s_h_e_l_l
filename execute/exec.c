/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 18:57:41 by sumjo             #+#    #+#             */
/*   Updated: 2024/01/19 04:25:50 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	run_execve(t_lst *lst, t_arg *arg)
{
	char	**cmd;

	get_path(arg);
	cmd = return_commands(arg, lst->cmd);

	if (execve(cmd[0], cmd, env_lst_to_arr(arg->env)) == -1)
	{
		throw_error(cmd[0], 0, strerror(errno));
		if (errno == 21)
			exit(126);
		exit(1);
	}
	return (0);
}

int	execute(t_lst *lst, t_arg *arg)
{
	if (is_builtin(lst))
		return (run_builtin(lst, arg));
	else
		return (run_execve(lst, arg));
}
