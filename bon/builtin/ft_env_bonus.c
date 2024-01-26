/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 02:41:48 by sumjo             #+#    #+#             */
/*   Updated: 2024/01/26 12:22:09 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_bonus.h"

int	ft_env(t_env *env)
{
	while (env)
	{
		if (env->value)
		{
			ft_putstr_fd(env->key, 1);
			write(1, "=", 1);
			ft_putstr_fd(env->value, 1);
			write(1, "\n", 1);
		}
		env = env->next;
	}
	return (1);
}
