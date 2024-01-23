/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 16:57:27 by sumjo             #+#    #+#             */
/*   Updated: 2024/01/24 05:16:15 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

char	*ft_strndup(char *s, char *end)
{
	int		i;
	char	*ret;

	if (!end)
	{
		ret = wft_strdup(s);
		return (ret);
	}
	i = -1;
	ret = wft_calloc(end - s + 1, 1);
	while (++i < end - s)
		ret[i] = s[i];
	ret[i] = 0;
	return (ret);
}

t_env	*make_env_lst(char **env)
{
	t_env	*env_lst;
	t_env	*tmp;
	int		i;

	env_lst = wft_calloc(1, sizeof(t_env));
	tmp = env_lst;
	i = -1;
	while (env[++i])
	{
		tmp->key = ft_strndup(env[i], ft_strchr(env[i], '='));
		tmp->value = wft_strdup(ft_strchr(env[i], '=') + 1);
		if (env[i + 1])
		{
			tmp->next = (t_env *)malloc(sizeof(t_env));
			tmp = tmp->next;
		}
		else
			tmp->next = NULL;
	}
	return (env_lst);
}

int	env_lst_count(t_env *env)
{
	t_env	*tmp;
	int		count;

	count = 0;
	tmp = env;
	while (tmp)
	{
		tmp = tmp->next;
		count++;
	}
	return (count);
}

char	**env_lst_to_arr(t_env *env)
{
	t_env	*tmp;
	char	*str;
	char	**ret;
	int		i;

	i = env_lst_count(env);
	ret = (char **)malloc(sizeof(char *) * (i + 1));
	i = -1;
	tmp = env;
	while (tmp)
	{
		if (tmp->value == NULL)
			ret[++i] = wft_strdup(tmp->key);
		else
		{
			str = ft_strjoin(tmp->key, "=");
			ret[++i] = ft_strjoin(str, tmp->value);
			safe_free(str);
		}
		tmp = tmp->next;
	}
	ret[i + 1] = NULL;
	return (ret);
}

char	*get_env_value(t_env *env, char *key)
{
	t_env	*tmp;

	if (ft_strncmp(key, "?", 2) == 0)
		return (ft_itoa(g_exit_status));
	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, ft_strlen(key) + 1) == 0)
			return (wft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (NULL);
}
