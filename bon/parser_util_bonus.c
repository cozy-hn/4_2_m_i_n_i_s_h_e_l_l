/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 19:15:10 by jiko              #+#    #+#             */
/*   Updated: 2024/01/26 12:21:37 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

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
