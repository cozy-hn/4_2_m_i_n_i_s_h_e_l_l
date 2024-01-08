/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiko <jiko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 17:52:55 by jiko              #+#    #+#             */
/*   Updated: 2024/01/08 23:19:35 by jiko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//<list> ::= <pipeline> {("&&" | "||") <pipeline>}
int	cmd_list(t_cmd_tree **head, t_token **now)
{
	t_cmd_tree	*next;

	*head = wft_calloc(1, sizeof(t_cmd_tree));
	(*head)->bnf_type = BNF_LIST;
	if (cmd_pipeline(&(*head)->left, now))
		return (1);
	while (*now && ((*now)->type == T_OR || (*now)->type == T_AND))
	{
		(*head)->token = *now;
		*now = (*now)->next;
		next = wft_calloc(1, sizeof(t_cmd_tree));
		next->left = *head;
		if (cmd_pipeline(&next->right, now))
			return (1);
		*head = next;
	}
	return (0);
}

//<pipeline> ::= "(" <list> ")" | <command> {"|" <command>}
int	cmd_pipeline(t_cmd_tree **head, t_token **now)
{
	t_cmd_tree	*next;

	*head = wft_calloc(1, sizeof(t_cmd_tree));
	(*head)->bnf_type = BNF_PIPELINE;
	if ((*now)->type == T_L_PAR)
	{
		*now = (*now)->next;
		if (cmd_list(&(*head)->left, now))
			return (1);
		if ((*now)->type != T_R_PAR)
			return (1);
		*now = (*now)->next;
	}
	else if (cmd_command(&(*head)->left, now))
		return (1);
	while (*now && (*now)->type == T_PIPE)
	{
		(*head)->token = *now;
		*now = (*now)->next;
		next = wft_calloc(1, sizeof(t_cmd_tree));
		next->left = *head;
		if (cmd_command(&next->right, now))
			return (1);
		*head = next;
	}
	return (0);
}

// <command> ::= <command_part> {<command_part>}
int	cmd_command(t_cmd_tree **head, t_token **now)
{
	t_cmd_tree	*next;

	*head = wft_calloc(1, sizeof(t_cmd_tree));
	(*head)->bnf_type = BNF_COMMAND;
	if (cmd_command_part(&(*head)->left, now))
		return (1);
	while (*now && (*now)->type == T_WORD)
	{
		next = wft_calloc(1, sizeof(t_cmd_tree));
		next->left = *head;
		if (cmd_command_part(&next->right, now))
			return (1);
		*head = next;
	}
	return (0);
}

//	<command_part>	::= (">" | ">>" | "<" | "<<") <word> | <word>
int	cmd_command_part(t_cmd_tree **head, t_token **now)
{
	*head = wft_calloc(1, sizeof(t_cmd_tree));
	(*head)->bnf_type = BNF_COMMAND_PART;
	if ((*now)->type == T_R_REDIR || (*now)->type == T_R_D_REDIR
		|| (*now)->type == T_L_REDIR || (*now)->type == T_L_D_REDIR)
	{
		(*head)->token = *now;
		printf("cmd_command_part\n");
		printf("(*head)->token->word = %s\n", (*head)->token->word);
		printf("(*now)->next = %p\n", (*now)->next);
		if (!(*now)->next || ((*now)->next->type != T_WORD))
			return (1);
		(*head)->token->word = (*now)->next->word;
		*now = (*now)->next->next;
	}
	else if ((*now)->type == T_WORD)
	{
		(*head)->token = *now;
		*now = (*now)->next;
	}
	else
		return (1);
	return (0);
}

void	parser(t_cmd_tree **head, t_token **token)
{
	t_token	*now;

	now = *token;
	cmd_list(head, &now);
}
