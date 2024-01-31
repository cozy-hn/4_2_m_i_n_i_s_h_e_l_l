/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_free_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiko <jiko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:25:20 by jiko              #+#    #+#             */
/*   Updated: 2024/01/31 20:28:07 by jiko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

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

void	free_double_char(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		safe_free(str[i]);
		i++;
	}
	safe_free(str);
}

void	free_lst(t_lst **lst)
{
	t_lst	*tmp;

	while (*lst)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		free_double_char(tmp->cmd);
		safe_free(tmp->fd_in_name);
		safe_free(tmp->fd_out_name);
		safe_free(tmp);
	}
}
