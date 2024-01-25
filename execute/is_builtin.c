/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 18:55:14 by sumjo             #+#    #+#             */
/*   Updated: 2024/01/26 04:56:48 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

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

int	run_builtin(t_lst *lst, t_arg *arg)
{
	if (ft_strncmp(lst->cmd[0], "echo", 5) == 0)
		return (ft_echo(lst->cmd));
	else if (ft_strncmp(lst->cmd[0], "cd", 3) == 0)
		return (ft_cd(arg, lst->cmd));
	else if (ft_strncmp(lst->cmd[0], "pwd", 4) == 0)
		return (ft_pwd());
	else if (ft_strncmp(lst->cmd[0], "export", 7) == 0)
		return (ft_export(arg->env, lst->cmd));
	else if (ft_strncmp(lst->cmd[0], "unset", 6) == 0)
		return (ft_unset(&(arg->env), lst->cmd));
	else if (ft_strncmp(lst->cmd[0], "env", 4) == 0)
		return (ft_env(arg->env));
	else if (ft_strncmp(lst->cmd[0], "exit", 5) == 0)
		return (ft_exit(arg, lst->cmd));
	return (0);
}
