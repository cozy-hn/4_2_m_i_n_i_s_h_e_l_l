/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 19:27:17 by sumjo             #+#    #+#             */
/*   Updated: 2024/01/06 20:30:54 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

// int	check_lld(unsigned long long res, int sign)
// {
// 	if (res > 9223372036854775807UL && sign > 0)
// 		return (77);
// 	if (res > 9223372036854775808UL && sign < 0)
// 		return (77);
// 	return (TRUE);
// }

int	valid_exit_code(const char *s)
{
	char				*ptr;
	unsigned long long	res;
	int					sign;

	ptr = (char *)s;
	res = 0;
	sign = 1;
	if (*ptr == '-')
	{
		sign = -1;
		ptr++;
	}
	while (*ptr)
	{
		if (res > res * 10 + (*ptr - '0'))
			return (77);
		res = res * 10 + (*ptr - '0');
		ptr++;
	}
	return (check_lld(res, sign));
}

unsigned char	check_exit_arg(char *arg)
{
	char	*str;

	str = arg;
	if (*str == '-')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
		{
			throw_error("exit", str, "numeric argument required");
			exit(255);
		}
		str++;
	}
	if (valid_exit_code(arg) == FALSE)
	{
		throw_error("exit", ptr, "numeric argument required");
		exit(255);
	}
	return (ft_atoi(arg));
}

int	ft_exit(char **argv char **env)
{
	unsigned char	exit_code;

	exit_code = 0;
	ft_putstr_fd("exit\n", STDERR_FILENO);
	if (argv[1])
	{
		exit_code = check_exit_arg(argv[1]);
		if (argv[2])
			return (throw_error("exit", NULL, "too many arguments"));
	}
	ft_free_arr(env);
	exit(exit_code);
	return (1);
}
