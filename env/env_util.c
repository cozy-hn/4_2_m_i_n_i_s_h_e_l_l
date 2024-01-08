/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 16:57:27 by sumjo             #+#    #+#             */
/*   Updated: 2024/01/08 17:50:47 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

typedef struct s_lst{
    int     fd_in;
    int     fd_out;
	char	**cmd;
    int     prev_pipe;
	struct s_lst *next;
} t_lst;


typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_arg
{
	t_env	*env;
	char	**path;
	t_lst	*lst;
} t_arg;

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

int main(int ac, char **av, char **env)
{
	t_arg arg;
	
	ac = 0;
	av = 0;
	
	int i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}

	make_env_lst(&arg, env);

	// t_env *tmp;
	// tmp = arg.env;
	
	// printf("\n");
	// printf("\n");
	// printf("\n");
	// while (tmp)
	// {
	// 	printf("%s", tmp->key);
	// 	printf("=%s\n", tmp->value);
	// 	tmp = tmp->next;
	// }
}
