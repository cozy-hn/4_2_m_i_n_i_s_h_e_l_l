/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 02:41:48 by sumjo             #+#    #+#             */
/*   Updated: 2024/01/28 03:26:06 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	ft_env(t_env **env_lst)
{
	t_env	*env;

	env = *env_lst;
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
