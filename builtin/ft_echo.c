/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josumin <josumin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 02:15:16 by sumjo             #+#    #+#             */
/*   Updated: 2024/01/10 16:30:05 by josumin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "../minishell.h"

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
			while (cmd[i][++j] && cmd[i][j] == '\0')
			{
				if (cmd[i][j] != 'n')
					return (0);
			}
			return (1);
		}
		else
			return (0);
	}
	return (0);
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
	idx = check_option(cmd);
	if (option_flag == OPTION)
		idx = 1;
	else
		idx = 0;
	while (cmd[++idx])
	{
		ft_putstr_fd(cmd[idx], 1);
		if (cmd[idx + 1] != NULL)
			write(1, " ", 1);
	}
	if (option_flag == NO_OPTION)
		write(1, "\n", 1);
	return (0);
}

int main()
{
	char *cmd[] = {"echo", "-n", "hello", "world", NULL};
	ft_echo(cmd);
	return (0);
}
