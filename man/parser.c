/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 17:52:55 by jiko              #+#    #+#             */
/*   Updated: 2024/01/28 05:42:08 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//<list> ::= <pipeline> {("&&" | "||") <pipeline>}
int	cmd_list(t_cmd_tree **head, t_token **now, t_heredoc **hed_lst)
{
	t_cmd_tree	*next;

	*head = wft_calloc(1, sizeof(t_cmd_tree));
	(*head)->bnf_type = BNF_LIST;
	if (cmd_pipeline(&(*head)->left, now, hed_lst))
		return (1);
	while (*now && ((*now)->type == T_OR || (*now)->type == T_AND))
	{
		(*head)->token = *now;
		*now = (*now)->next;
		next = wft_calloc(1, sizeof(t_cmd_tree));
		next->bnf_type = BNF_LIST;
		next->left = *head;
		*head = next;
		if (cmd_pipeline(&next->right, now, hed_lst))
			return (1);
	}
	return (0);
}

//<pipeline> ::= "(" <list> ")" | <command> {"|" <command>}
int	cmd_pipeline(t_cmd_tree **head, t_token **now, t_heredoc **hed_lst)
{
	*head = wft_calloc(1, sizeof(t_cmd_tree));
	(*head)->bnf_type = BNF_PIPELINE;
	if (*now && (*now)->type == T_L_PAR)
	{
		*now = (*now)->next;
		if (cmd_list(&(*head)->left, now, hed_lst))
			return (1);
		if (!(*now) || (*now)->type != T_R_PAR)
			return (1);
		*now = (*now)->next;
	}
	else
		if (cmd_command_else(head, now, hed_lst))
			return (1);
	return (0);
}

// <command> ::= <command_part> {<command_part>}
int	cmd_command(t_cmd_tree **head, t_token **now, t_heredoc **hed_lst)
{
	t_cmd_tree	*next;

	*head = wft_calloc(1, sizeof(t_cmd_tree));
	(*head)->bnf_type = BNF_COMMAND;
	if (cmd_command_part(&(*head)->left, now, hed_lst))
		return (1);
	while (*now && (T_L_REDIR <= (*now)->type && (*now)->type <= T_WORD))
	{
		next = wft_calloc(1, sizeof(t_cmd_tree));
		next->bnf_type = BNF_COMMAND;
		next->left = *head;
		*head = next;
		if (cmd_command_part(&next->right, now, hed_lst))
			return (1);
	}
	return (0);
}

//	<command_part>	::= (">" | ">>" | "<" | "<<") <word> | <word>
int	cmd_command_part(t_cmd_tree **head, t_token **now, t_heredoc **hed_lst)
{
	*head = wft_calloc(1, sizeof(t_cmd_tree));
	(*head)->bnf_type = BNF_COMMAND_PART;
	(*head)->token = *now;
	if (*now && T_L_REDIR <= (*now)->type && (*now)->type <= T_R_D_REDIR)
	{
		if (!(*now)->next || ((*now)->next->type != T_WORD))
		{
			(*now) = (*now)->next;
			return (1);
		}
		safe_free((*head)->token->word);
		(*head)->token->word = wft_strdup((*now)->next->word);
		if ((*now)->type == 8 && heredoc(&(*head)->token->word, hed_lst))
			return (1);
		*now = (*now)->next->next;
	}
	else if (*now && (*now)->type == T_WORD)
		*now = (*now)->next;
	else
		return (1);
	return (0);
}

int	parser(t_cmd_tree **head, t_token **token, t_main *main)
{
	t_token	*now;
	int		type;

	now = *token;
	type = wft_lstlast(*token)->type;
	if (cmd_list(head, &now, &(main->hed_lst)) || now)
	{
		main->exit_code = 1;
		if (!(main->hed_lst && main->hed_lst->hed_flag))
		{
			main->exit_code = 258;
			ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
			g_exit = 0;
			if (now)
				ft_putstr_fd(now->word, 2);
			else
				ft_putstr_fd("newline", 2);
			ft_putstr_fd("'\n", 2);
		}
		free_cmd_tree(*head);
		free_token(*token);
		return (1);
	}
	return (0);
}
