/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 19:27:17 by sumjo             #+#    #+#             */
/*   Updated: 2024/01/19 04:17:43 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int return_exit_code(char *str, int i)
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

int is_all_digits(const char *str) {

    if (str == NULL || *str == '\0') {
        return 0;  // false
    }

    if (*str == '-' || *str == '+') {
        str++;  // 부호가 있으면 건너뜁니다.
    }

    while (*str != '\0') {
        if (!ft_isdigit(*str)) {
            return 0;  // false
        }
        str++;
    }

    return 1; 
}

int	ft_exit(t_arg *arg, char **cmd)
{
	int	exit_code;

	exit_code = 0;
	if (ft_strncmp(arg->lst->cmd[1], "exit", 4) && arg->lst->next == NULL)
		ft_putstr_fd("exit\n", STDERR_FILENO);
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
	g_exit_status = exit_code;
	exit(exit_code);
	return (exit_code);
}


// int main() {
// 	char *args = "-2dsf";
// 	printf("%d\n", return_exit_code(args, 0));
// }
