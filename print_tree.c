/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 19:20:53 by jiko              #+#    #+#             */
/*   Updated: 2024/01/26 05:02:06 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include "minishell.h"

// void	test_print_command_part(t_cmd_tree *node)
// {	
// 	if (node->token->type == T_L_REDIR)
// 		printf("< ");
// 	else if (node->token->type == T_R_REDIR)
// 		printf("> ");
// 	else if (node->token->type == T_L_D_REDIR)
// 		printf("<< ");
// 	else if (node->token->type == T_R_D_REDIR)
// 		printf(">> ");
// 	printf("%s", node->token->word);
// 	printf("\n");
// }

// void	test_print_node(t_cmd_tree *node)
// {
// 	if (node->bnf_type == BNF_LIST)
// 	{
// 		if (node->token && node->token->type == T_AND)
// 			printf("[LS&&]");
// 		else if (node->token && node->token->type == T_OR)
// 			printf("[LS||]");
// 		else
// 			printf("[LS--]");
// 	}
// 	else if (node->bnf_type == BNF_PIPELINE)
// 		printf("[PIPE]");
// 	else if (node->bnf_type == BNF_COMMAND)
// 		printf("[COMD]");
// 	else if (node->bnf_type == BNF_COMMAND_PART)
// 	{
// 		if (node->token == NULL)
// 		{
// 			printf("[NULL]\n");
// 			return ;
// 		}
// 		if (node->token->type == T_L_REDIR)
// 			printf("< %s", node->token->word);
// 		else if (node->token->type == T_R_REDIR)
// 			printf("> %s", node->token->word);
// 		else if (node->token->type == T_L_D_REDIR)
// 			printf("<< %s", node->token->word);
// 		else if (node->token->type == T_R_D_REDIR)
// 			printf(">> %s", node->token->word);
// 		else
// 			printf("%s", node->token->word);
// 	}
// 	printf("\n");
// }

// void	test_displayTree(t_cmd_tree *node, char *indent, int isLast)
// {
// 	char	newIndent[1000];
// 	if (node == NULL)
// 		return ;
// 	printf("%s", indent);
// 	if (isLast)
// 		printf("└──");
// 	else
// 		printf("├──");
// 	test_print_node(node);
// 	strcpy(newIndent, indent);
// 	if (isLast)
// 		strcat(newIndent, "       ");
// 	else
// 		strcat(newIndent, "│      ");
// 	test_displayTree(node->left, newIndent, node->right == NULL);
// 	test_displayTree(node->right, newIndent, 1);
// }

// int	test_tr_print_tree(t_cmd_tree *root)
// {
// 	char indent[2500] = "";
// 	printf("\n[TREE] DONE!\n│\n");
// 	test_displayTree(root, indent, 1);
// 	printf("\n");
// 	return (0);
// }

// void	print_token(t_token *token)
// {
// 	while (token)
// 	{
// 		printf("type: %d\n", token->type);
// 		printf("word: %s\n", token->word);
// 		printf("==========\n");
// 		token = token->next;
// 	}
// }

// void	print_env(t_env *env)
// {
// 	while (env)
// 	{
// 		printf("key: %s\n", env->key);
// 		printf("value: %s\n", env->value);
// 		printf("==========\n");
// 		env = env->next;
// 	}
// }