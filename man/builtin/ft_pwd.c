/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 04:22:43 by sumjo             #+#    #+#             */
/*   Updated: 2024/01/28 03:00:03 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	ft_pwd(t_main *main)
{
	char	*pwd;

	main = 0;
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		pwd = get_env_value(main, "PWD");
		if (pwd == NULL)
		{
			throw_error("pwd", "error retrieving current directory", NULL);
			return (1);
		}
	}
	ft_putstr_fd(pwd, 1);
	write(1, "\n", 1);
	if (pwd != NULL)
		free(pwd);
	return (0);
}
