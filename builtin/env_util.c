/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josumin <josumin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 16:57:27 by sumjo             #+#    #+#             */
/*   Updated: 2024/01/10 14:17:16 by josumin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"
#include "builtin.h"

char *ft_strndup(char *s, char *end)
{
	int i;
	char *ret;

	if (!end)
	{
		ret = ft_strdup(s);
		return (ret);
	}
	i = -1;
	ret = (char *)malloc(sizeof(char) * (end - s + 1));
	while (++i < end - s)
		ret[i] = s[i];
	ret[i] = 0;
	return (ret);
}

int	make_env_lst(t_arg *arg, char **env)
{
	t_env	*tmp;
	int i;

	arg->env = (t_env *)malloc(sizeof(t_env));
	tmp = arg->env;
	i = -1;
	while (env[++i])
	{
		tmp->key = ft_strndup(env[i], ft_strchr(env[i], '='));
		tmp->value = ft_strdup(ft_strchr(env[i], '=') + 1);
		if (env[i + 1])
		{
			tmp->next = (t_env *)malloc(sizeof(t_env));
			tmp = tmp->next;
		}
		else
			tmp->next = NULL;
	}
	return (0);
}

char	**env_lst_to_arr(t_env *env)
{
	t_env	*tmp;
	char **ret;
	int i;

	i = 0;
	tmp = env;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	ret = (char **)malloc(sizeof(char *) * (i + 1));
	i = -1;
	tmp = env;
	while (tmp)
	{
		if (tmp->value == NULL)
			ret[++i] = ft_strdup(tmp->key);
		else
		{
			ret[++i] = ft_strjoin(tmp->key, "=");
			ret[i] = ft_strjoin(ret[i], tmp->value);
		}
		tmp = tmp->next;
	}
	ret[i + 1] = NULL;
	return (ret);
}

char *get_env_value(t_env *env, char *key)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, ft_strlen(key)) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}
