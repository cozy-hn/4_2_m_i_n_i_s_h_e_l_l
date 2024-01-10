/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josumin <josumin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 16:57:27 by sumjo             #+#    #+#             */
/*   Updated: 2024/01/10 14:16:12 by josumin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// typedef struct s_lst{
//     int     fd_in;
//     int     fd_out;
// 	char	**cmd;
//     int     prev_pipe;
// 	struct s_lst *next;
// } t_lst;


// typedef struct s_env
// {
// 	char			*key;
// 	char			*value;
// 	struct s_env	*next;
// }	t_env;

// typedef struct s_arg
// {
// 	t_env	*env;
// 	char	**path;
// 	t_lst	*lst;
// } t_arg;
#include "../minishell.h"

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

char	**env_lst_to_arr(t_arg *arg)
{
	t_env *tmp;
	char **ret;
	int i;

	tmp = arg->env;
	i = 0;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	ret = (char **)malloc(sizeof(char *) * (i + 1));
	i = -1;
	tmp = arg->env;
	while (tmp)
	{
		ret[++i] = ft_strjoin(tmp->key, "=");
		ret[i] = ft_strjoin(ret[i], tmp->value);
		tmp = tmp->next;
	}
	ret[i + 1] = NULL;
	return (ret);
}

// int main(int ac, char **av, char **env)
// {
// 	t_arg arg;
	
// 	ac = 0;
// 	av = 0;

// }
