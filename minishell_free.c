/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiko <jiko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:25:20 by jiko              #+#    #+#             */
/*   Updated: 2024/01/21 21:33:32 by jiko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	safe_free(void *str)
{
	if (str)
		free(str);
}

void	free_token(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token->next;
		safe_free(token->word);
		safe_free(token);
		token = tmp;
	}
}

void	free_cmd_tree(t_cmd_tree *cmd_tree)
{
	if (cmd_tree->left)
		free_cmd_tree(cmd_tree->left);
	if (cmd_tree->right)
		free_cmd_tree(cmd_tree->right);
	safe_free(cmd_tree);
}

// void	free_env_lst (t_env *env_lst)
// {
// 	t_env	*tmp;

// 	while (env_lst)
// 	{
// 		tmp = env_lst->next;
// 		safe_free(env_lst->key);
// 		safe_free(env_lst->value);
// 		safe_free(env_lst);
// 		env_lst = tmp;
// 	}
// }
