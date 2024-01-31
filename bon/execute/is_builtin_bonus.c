/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiko <jiko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 18:55:14 by sumjo             #+#    #+#             */
/*   Updated: 2024/01/31 20:28:52 by jiko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_bonus.h"

int	is_builtin(t_lst *lst)
{
	if (lst->cmd == NULL || lst->cmd[0] == NULL)
		return (0);
	if (ft_strncmp(lst->cmd[0], "echo", 5) == 0)
		return (1);
	else if (ft_strncmp(lst->cmd[0], "cd", 3) == 0)
		return (1);
	else if (ft_strncmp(lst->cmd[0], "pwd", 4) == 0)
		return (1);
	else if (ft_strncmp(lst->cmd[0], "export", 7) == 0)
		return (1);
	else if (ft_strncmp(lst->cmd[0], "unset", 6) == 0)
		return (1);
	else if (ft_strncmp(lst->cmd[0], "env", 4) == 0)
		return (1);
	else if (ft_strncmp(lst->cmd[0], "exit", 5) == 0)
		return (1);
	return (0);
}

int	run_builtin(t_lst *lst, t_main *main)
{
	if (ft_strncmp(lst->cmd[0], "echo", 5) == 0)
		return (ft_echo(lst->cmd));
	else if (ft_strncmp(lst->cmd[0], "cd", 3) == 0)
		return (ft_cd(main, lst->cmd));
	else if (ft_strncmp(lst->cmd[0], "pwd", 4) == 0)
		return (ft_pwd(main));
	else if (ft_strncmp(lst->cmd[0], "export", 7) == 0)
		return (ft_export(main->arg->env, lst->cmd));
	else if (ft_strncmp(lst->cmd[0], "unset", 6) == 0)
		return (ft_unset(main->arg->env, lst->cmd));
	else if (ft_strncmp(lst->cmd[0], "env", 4) == 0)
		return (ft_env(main->arg->env));
	else if (ft_strncmp(lst->cmd[0], "exit", 5) == 0)
		return (ft_exit(main, lst->cmd));
	return (0);
}
