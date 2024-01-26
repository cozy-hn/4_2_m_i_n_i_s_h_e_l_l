/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiko <jiko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 19:15:10 by jiko              #+#    #+#             */
/*   Updated: 2024/01/26 05:00:20 by jiko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_command_else(t_cmd_tree **head, t_token **now, t_heredoc **hed_lst)
{
	t_cmd_tree	*next;

	if (cmd_command(&(*head)->left, now, hed_lst))
		return (1);
	while (*now && (*now)->type == T_PIPE)
	{
		(*head)->token = *now;
		*now = (*now)->next;
		next = wft_calloc(1, sizeof(t_cmd_tree));
		next->bnf_type = BNF_PIPELINE;
		next->left = *head;
		*head = next;
		if (cmd_command(&next->right, now, hed_lst))
			return (1);
	}
	return (0);
}
