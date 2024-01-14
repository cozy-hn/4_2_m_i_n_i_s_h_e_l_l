/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_start.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 02:01:21 by sumjo             #+#    #+#             */
/*   Updated: 2024/01/14 18:48:35 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./execute.h"

// void free_env_lst (t_env *env)
// {
// 	t_env	*tmp;

// 	while (env)
// 	{
// 		tmp = env->next;
// 		safe_free(env->key);
// 		safe_free(env->value);
// 		safe_free(env);
// 		env = tmp;
// 	}
// }

void	free_lst(t_lst *lst)
{
	t_lst	*tmp;

	while (lst)
	{
		tmp = lst->next;
		safe_free(lst->cmd);
		safe_free(lst);
		lst = tmp;
	}
}

void	free_arg_lst(t_arg *arg)
{
	t_arg	*tmp;

	while (arg)
	{
		tmp = arg->next;
		free_lst(arg->lst);
		safe_free(arg->path);
		safe_free(arg);
		arg = tmp;
	}
}

void	execute_start(t_arg *arg)
{
	t_arg	*tmp;
	int		status;

	tmp = arg;
	while (tmp)
	{
		status = executor(tmp);
		if (arg->condition == T_OR && status == 0)
			break ;
		if (arg->condition == T_AND && status != 0)
			break ;
		tmp = tmp->next;
	}	
	free_arg_lst(arg);
	return ;
}

int main(int ac, char **av, char **env)
{
	ac = 0;
	av = 0;
	// t_env	*env_lst;

	t_arg	*arg;
	t_arg	*tmp;
	int		i;

	i = 1;
	// arg = (t_arg *)malloc(sizeof(t_arg));
	arg = wft_calloc(sizeof(t_arg), 1);	
	tmp = arg;


	arg = mock_lst(0, env);
	execute_start(arg);
}
