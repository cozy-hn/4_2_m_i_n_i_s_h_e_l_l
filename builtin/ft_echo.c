/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 02:15:16 by sumjo             #+#    #+#             */
/*   Updated: 2024/01/25 04:06:58 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	check_option(char **cmd)
{
	int	i;
	int	j;

	i = 0;
	while (cmd[++i])
	{
		if (cmd[i][0] == '-')
		{
			j = 0;
			if (!cmd[i][1])
				return (i - 1);
			while (cmd[i][++j])
			{
				if (cmd[i][j] != 'n')
					return (i - 1);
			}
		}
		else
			return (i - 1);
	}
	return (i - 1);
}

void	run_echo(char **cmd, int idx)
{
	int	i;
	int	j;

	i = idx;
	j = 0;
	while (cmd[++i])
	{
		j = 0;
		while (cmd[i][j])
		{
			if (cmd[i][j] == '$' && cmd[i][j + 1] == '?')
			{
				ft_putnbr_fd(g_exit_status, 1);
				j++;
			}
			else
				write(1, &cmd[i][j], 1);
			j++;
		}
		if (cmd[i + 1])
			write(1, " ", 1);
	}
}

int	ft_echo(char **cmd)
{
	int	idx;
	int	option_flag;

	if (cmd[1] == NULL)
	{
		write(1, "\n", 1);
		return (0);
	}
	option_flag = check_option(cmd);
	idx = option_flag;
	run_echo(cmd, idx);
	if (option_flag == 0)
		write(1, "\n", 1);
	return (0);
}
