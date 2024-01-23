/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 18:57:41 by sumjo             #+#    #+#             */
/*   Updated: 2024/01/24 08:32:37 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	ft_wait(int pid, t_arg *arg, int *status)
{
	int		i;
	t_lst	*tmp;

	i = 0;
	tmp = arg->lst;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	waitpid(pid, status, 0);
	i -= 1;
	while (i > 0)
	{
		wait(NULL);
		i--;
	}
}

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
