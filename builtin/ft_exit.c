/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 19:27:17 by sumjo             #+#    #+#             */
/*   Updated: 2024/01/26 00:47:30 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	return_exit_code(char *str, int i)
{
	int	result;
	int	sign;

	sign = 0;
	result = 0;
	if (str[0] == '+')
		i = 1;
	if (str[0] == '-')
	{
		i = 1;
		sign = -1;
	}
	while (str[i] != '\0')
	{
		result = (result * 10) + (str[i] - '0');
		if (result > 255)
			result %= 256;
		i++;
	}
	if (sign == -1)
		result = 256 - result;
	return (result);
}

int	is_all_digits(const char *str)
{
	if (str == NULL || *str == '\0')
	{
		return (0);
	}
	if (*str == '-' || *str == '+')
	{
		str++;
	}
	while (*str != '\0')
	{
		if (!ft_isdigit(*str))
		{
			return (0);
		}
		str++;
	}
	return (1);
}

int	ft_exit(t_arg *arg, char **cmd)
{
	int	exit_code;

	exit_code = 0;
	if (ft_strncmp(arg->lst->cmd[0], "exit", 5) == 0 && arg->lst->next == NULL)
		ft_putstr_fd("exit\n", STDERR_FILENO);
	handle_heredoc(arg);
	if (!cmd[1])
		exit(exit_code);
	else if (!is_all_digits(cmd[1]))
	{
		throw_error("exit", NULL, "numeric argument required");
		exit_code = 255;
	}
	else if (cmd[2])
	{
		throw_error("exit", NULL, "too many arguments");
		return (1);
	}
	else
		exit_code = return_exit_code(cmd[1], 0);
	g_exit = exit_code;
	exit(exit_code);
	return (exit_code);
}
