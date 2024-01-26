/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 04:22:43 by sumjo             #+#    #+#             */
/*   Updated: 2024/01/26 12:22:09 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_bonus.h"

int	ft_pwd(t_env *env)
{
	char	*pwd;

	pwd = get_env_value(env, "PWD");
	ft_putstr_fd(pwd, 1);
	write(1, "\n", 1);
	free(pwd);
	return (0);
}
