/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiko <jiko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 17:52:55 by jiko              #+#    #+#             */
/*   Updated: 2024/01/21 18:03:52 by jiko             ###   ########.fr       */
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
		next->bnf_type = BNF_LIST;
		next->left = *head;
		*head = next;
		if (cmd_pipeline(&next->right, now))
			return (1);
	}
	return (0);
}

//<pipeline> ::= "(" <list> ")" | <command> {"|" <command>}
int	cmd_pipeline(t_cmd_tree **head, t_token **now)
{
	t_cmd_tree	*next;

	*head = wft_calloc(1, sizeof(t_cmd_tree));
	(*head)->bnf_type = BNF_PIPELINE;
	if (*now && (*now)->type == T_L_PAR)
	{
		*now = (*now)->next;
		if (cmd_list(&(*head)->left, now))
			return (1);
		if ((*now)->type != T_R_PAR)
			return (1);
		*now = (*now)->next;
	}
	else
	{
		if (cmd_command(&(*head)->left, now))
			return (1);
		while (*now && (*now)->type == T_PIPE)
		{
			(*head)->token = *now;
			*now = (*now)->next;
			next = wft_calloc(1, sizeof(t_cmd_tree));
			next->bnf_type = BNF_PIPELINE;
			next->left = *head;
			*head = next;
			if (cmd_command(&next->right, now))
				return (1);
		}
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
	while (*now && (T_L_REDIR <= (*now)->type && (*now)->type <= T_WORD))
	{
		next = wft_calloc(1, sizeof(t_cmd_tree));
		next->bnf_type = BNF_COMMAND;
		next->left = *head;
		*head = next;
		if (cmd_command_part(&next->right, now))
			return (1);
	}
	return (0);
}

//	<command_part>	::= (">" | ">>" | "<" | "<<") <word> | <word>
int	cmd_command_part(t_cmd_tree **head, t_token **now)
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
		*now = (*now)->next->next;
	}
	else if (*now && (*now)->type == T_WORD)
		*now = (*now)->next;
	else
		return (1);
	return (0);
}

int	parser(t_cmd_tree **head, t_token **token)
{
	t_token	*now;
	int		type;

	now = *token;
	type = wft_lstlast(*token)->type;
	if (cmd_list(head, &now))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		if (now)
			ft_putstr_fd(now->word, 2);
		else
			ft_putstr_fd("newline", 2);
		ft_putstr_fd("'\n", 2);
		free_cmd_tree(*head);
		free_token(*token);
		return (1);
	}
	return (0);
}
