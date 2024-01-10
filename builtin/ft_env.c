/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josumin <josumin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 02:41:48 by sumjo             #+#    #+#             */
/*   Updated: 2024/01/10 13:55:47 by josumin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
int	ft_env(t_env *env)
{
	while (env)
	{
		ft_putstr_fd(env->key, 1);
		write(1, "=", 1);
		ft_putstr_fd(env->value, 1);
		write(1, "\n", 1);
		env = env->next;
	}
	return (1);
}
