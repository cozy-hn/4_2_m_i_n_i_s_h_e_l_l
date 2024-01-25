/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 18:57:41 by sumjo             #+#    #+#             */
/*   Updated: 2024/01/26 00:47:30 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	ft_wait(int pid, t_arg *arg)
{
	int		last_status;
	int		status;
	int		signo;
	int		i;

	i = 0;
	waitpid(pid, &last_status, 0);
	g_exit = WEXITSTATUS(last_status);
	if (WIFSIGNALED(last_status))
	{
		signo = WTERMSIG(last_status);
		if (signo == SIGINT && i++ == 0)
		{
			ft_putstr_fd("^C\n", STDERR_FILENO);
			g_exit = 128 + signo;
		}
		else if (signo == SIGQUIT && i++ == 0)
			ft_putstr_fd("^\\Quit: 3\n", STDERR_FILENO);
	}
	while (wait(&status) != -1)
	{
		if (WIFSIGNALED(status))
		{
			signo = WTERMSIG(status);
			if (signo == SIGINT && i++ == 0)
				ft_putstr_fd("^C\n", STDERR_FILENO);
			else if (signo == SIGQUIT && i++ == 0)
				ft_putstr_fd("^\\Quit: 3\n", STDERR_FILENO);
		}
	}
}

int	run_execve(t_lst *lst, t_arg *arg)
{
	char	**cmd;
	char	**env;

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
