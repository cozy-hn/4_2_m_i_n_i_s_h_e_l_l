/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 19:39:21 by sumjo             #+#    #+#             */
/*   Updated: 2024/01/28 03:13:12 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

char	*return_path(t_env *env)
{
	char	*arr;
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, "PATH", 5) == 0)
		{
			arr = tmp->value;
			return (arr);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

void	get_path(t_arg *arg)
{
	char	*arr;
	int		i;

	i = 0;
	arr = return_path(*(arg->env));
	if (!arr)
	{
		arg->path = NULL;
		return ;
	}
	arg->path = ft_split(arr, ':');
	while (arg->path[i])
	{
		arg->path[i] = wft_strjoin(arg->path[i], wft_strdup("/"));
		i++;
	}
}
