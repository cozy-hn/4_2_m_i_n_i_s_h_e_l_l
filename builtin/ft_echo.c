/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 02:15:16 by sumjo             #+#    #+#             */
/*   Updated: 2024/01/04 02:40:20 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "../minishell.h"

int	check_option(char **args)
{
	int	i;
	int	j;

	i = 0;
	while (args[++i])
	{
		if (args[i][0] == '-')
		{
			j = 0;
			while (args[i][++j])
			{
				if (args[i][j] != 'n')
					return (NO_OPTION);
			}
			return (OPTION);
		}
		else
			return (NO_OPTION);
	}
	return (NO_OPTION);
}

int	ft_echo(char **args)
{
	int	idx;
	int	option_flag;

	if (args[1] == NULL)
	{
		write(1, "\n", 1);
		return (1);
	}
	option_flag = check_option(args);
	if (option_flag == OPTION)
		idx = 1;
	else
		idx = 0;
	while (args[++idx])
	{
		ft_putstr_fd(args[idx], 1);
		if (args[idx + 1] != NULL)
			write(1, " ", 1);
	}
	if (option_flag == NO_OPTION)
		write(1, "\n", 1);
	return (1);
}

// int main(int argc, char **argv)
// {
// 	(void)argc;
// 	ft_echo(argv);
// 	return (0);
// }
