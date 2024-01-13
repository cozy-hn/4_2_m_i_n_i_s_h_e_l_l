/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiko <jiko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 03:10:47 by jiko              #+#    #+#             */
/*   Updated: 2024/01/14 04:03:03 by jiko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void	add_front_lst(t_lst **lst, t_cmd_tree *cmd_tree)
{
	//전위순회 하면서 command_part를 char **로 만들어서 t_lst의 char **cmd에 넣어줌
	t_lst	*tmp;
	char	**cmd;

	tmp = wft_calloc(1, sizeof(t_lst));
	cmd = wft_calloc(1, sizeof(char *));
	wft_lstadd_front_lst(lst, tmp);
	
}
void	add_front_arg(t_arg **arg_lst, t_cmd_tree *cmd_tree, t_env *env_lst)
{
	t_lst	*cmd_lst;
	t_arg	*tmp;

	cmd_lst = NULL;
	tmp = wft_calloc(1, sizeof(t_arg));
	wft_lstadd_front_arg(arg_lst, tmp, env_lst, cmd_tree);
	if (cmd_tree->right)
		add_front_lst(&cmd_lst, cmd_tree->right);
	while (cmd_tree->left->bnf_type == BNF_PIPELINE)
	{
		cmd_tree = cmd_tree->left;
		if (cmd_tree->right)
			add_front_lst(&cmd_lst, cmd_tree->right);
		else if (cmd_tree->left->bnf_type == BNF_COMMAND)
			add_front_lst(&cmd_lst, cmd_tree->left);
	}
	(*arg_lst)->lst = cmd_lst;
}

void	start_exec(t_cmd_tree *cmd_tree, t_env *env_lst)
{
	t_arg	*arg_lst;

	arg_lst = NULL;
	if (cmd_tree->right)
		add_front_arg(&arg_lst, cmd_tree->right, env_lst);
	while (cmd_tree->left->bnf_type == BNF_LIST)
	{
		cmd_tree = cmd_tree->left;
		if (cmd_tree->right)
			add_front_arg(&arg_lst, cmd_tree->right, env_lst);
		else if (cmd_tree->left->bnf_type == BNF_PIPELINE)
			add_front_arg(&arg_lst, cmd_tree->left, env_lst);
	}
}
