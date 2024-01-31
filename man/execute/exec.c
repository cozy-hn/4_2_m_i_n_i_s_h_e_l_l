/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 18:57:41 by sumjo             #+#    #+#             */
/*   Updated: 2024/01/30 07:12:49 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	last_wait(int last_status, int *i, t_main *main)
{
	int		signo;

	signo = WTERMSIG(last_status);
	if (signo == SIGINT && (*i)++ == 0)
	{
		ft_putstr_fd("\n", STDERR_FILENO);
		main->exit_code = 128 + signo;
	}
	else if (signo == SIGQUIT && (*i)++ == 0)
	{
		ft_putstr_fd("Quit: 3\n", STDERR_FILENO);
		main->exit_code = 128 + signo;
	}
}

void	ft_wait(int pid, t_main *main)
{
	int		last_status;
	int		status;
	int		signo;
	int		i;

	i = 0;
	if (pid)
	{
		waitpid(pid, &last_status, 0);
		main->exit_code = WEXITSTATUS(last_status);
		if (WIFSIGNALED(last_status))
			last_wait(last_status, &i, main);
	}
	while (wait(&status) != -1)
	{
		if (WIFSIGNALED(status))
		{
			signo = WTERMSIG(status);
			if (signo == SIGINT && i++ == 0)
				ft_putstr_fd("\n", STDERR_FILENO);
			else if (signo == SIGQUIT && i++ == 0)
				ft_putstr_fd("", STDERR_FILENO);
		}
	}
}

int	run_execve(t_lst *lst, t_main *main)
{
	char	**cmd;

	get_path(main->arg);
	cmd = return_commands(main->arg, lst->cmd);
	if (execve(cmd[0], cmd, env_lst_to_arr(*(main->arg->env))) == -1)
	{
		throw_error(cmd[0], "command not found", 0);
		exit(127);
	}
	return (0);
}

int	execute(t_lst *lst, t_main *main)
{
	if (is_builtin(lst))
		return (run_builtin(lst, main));
	else
		return (run_execve(lst, main));
}
