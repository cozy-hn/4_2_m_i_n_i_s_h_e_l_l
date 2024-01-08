/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiko <jiko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 19:20:53 by jiko              #+#    #+#             */
/*   Updated: 2024/01/08 20:25:27 by jiko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "minishell.h"

void test_print_command_part(t_cmd_tree *node)
{
	if (node->token->type == T_L_REDIR)
		printf("< ");
	else if (node->token->type == T_R_REDIR)
		printf("> ");
	else if (node->token->type == T_L_D_REDIR)
		printf("<< ");
	else if (node->token->type == T_R_D_REDIR)
		printf(">> ");
	printf("%s", node->token->word);
	printf("\n");
}

void test_print_node(t_cmd_tree *node)
{
	if (node->bnf_type == BNF_LIST)
	{
		if (node->token && node->token->type == T_AND)
			printf("[LS&&]");
		else if (node->token && node->token->type == T_OR)
			printf("[LS||]");
		else
			printf("[LS--]");
	}
	else if (node->bnf_type == BNF_PIPELINE)
		printf("[PIPE]");
	else if (node->bnf_type == BNF_COMMAND)
		printf("[COMD]");
	else if (node->bnf_type == BNF_COMMAND_PART)
	{
		if (node->token->type == T_L_REDIR)
			printf("< %s", node->token->word);
		else if (node->token->type == T_R_REDIR)
			printf("> %s", node->token->word);
		else if (node->token->type == T_L_D_REDIR)
			printf("<< %s", node->token->word);
		else if (node->token->type == T_R_D_REDIR)
			printf(">> %s", node->token->word);
		else
			printf("%s", node->token->word);
	}
	else
		printf("[COMD]");
	printf("\n");
}

void test_displayTree(t_cmd_tree *node, char *indent, int isLast)
{
	if (node == NULL)
		return ;
	printf("%s", indent);
	if (isLast)
		printf("└──");
	else
		printf("├──");
	// 노드 데이터 출력
	test_print_node(node);
	// 들여쓰기 업데이트를 위한 새로운 임시 문자열
	char newIndent[1000];
	strcpy(newIndent, indent);
	if (isLast) {
		strcat(newIndent, "       ");  // 오른쪽 자식 (또는 자식 없음)을 위한 들여쓰기
	} else {
		strcat(newIndent, "│      ");  // 왼쪽 자식을 위한 들여쓰기
	}
	// 재귀적으로 자식 노드 출력
	test_displayTree(node->left, newIndent, node->right == NULL);
	test_displayTree(node->right, newIndent, 1);
}

int	test_tr_print_tree(t_cmd_tree *root)
{
	char indent[2500] = ""; // 초기 들여쓰기 설정
	printf("\n[TREE] DONE!\n│\n"); //test code
	test_displayTree(root, indent, 1); // 트리 출력
    printf("\n");
	return (0);
}
