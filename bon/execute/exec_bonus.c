/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 18:57:41 by sumjo             #+#    #+#             */
/*   Updated: 2024/01/30 07:22:46 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_bonus.h"

void	last_wait(int last_status, int *i)
{
	int		signo;

	signo = WTERMSIG(last_status);
	if (signo == SIGINT && (*i)++ == 0)
	{
		ft_putstr_fd("^C\n", STDERR_FILENO);
		g_exit = 128 + signo;
	}
	else if (signo == SIGQUIT && (*i)++ == 0)
	{
		ft_putstr_fd("^\\Quit: 3\n", STDERR_FILENO);
		g_exit = 128 + signo;
	}
}

void	ft_wait(int pid)
{
	int		last_status;
	int		status;
	int		signo;
	int		i;

	i = 0;
	if (pid)
	{
		waitpid(pid, &last_status, 0);
		g_exit = WEXITSTATUS(last_status);
		if (WIFSIGNALED(last_status))
			last_wait(last_status, &i);
	}
	while (wait(&status) != -1)
	{
		if (WIFSIGNALED(status))
		{
			signo = WTERMSIG(status);
			if (signo == SIGINT && i++ == 0)
				ft_putstr_fd("^C\n", STDERR_FILENO);
			else if (signo == SIGQUIT && i++ == 0)
				ft_putstr_fd("^\\", STDERR_FILENO);
		}
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
