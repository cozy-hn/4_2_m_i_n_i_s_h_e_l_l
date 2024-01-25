/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiko <jiko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 03:10:47 by jiko              #+#    #+#             */
/*   Updated: 2024/01/26 06:06:44 by jiko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	play_executor(t_lst **tmp_lst, t_env *env_lst, t_heredoc *hed_lst)
{
	t_arg	*arg;

	arg = wft_calloc(1, sizeof(t_arg));
	arg->env = env_lst;
	arg->lst = *tmp_lst;
	arg->hed_lst = hed_lst;
	executor(arg);
	safe_free(arg);
	set_signal(SHE, SHE);
}

void	add_redir(t_cmd_tree *ct, t_lst **tmp_lst, t_lst *new)
{
	if (ct->token->type == T_L_REDIR
		|| ct->token->type == T_L_D_REDIR)
	{
		new->fd_in = open(ct->token->word, O_RDONLY);
		if (new->fd_in != -1)
			close(new->fd_in);
		else
			(*tmp_lst)->error_flag = 1;
		safe_free(new->fd_in_name);
		new->fd_in_name = ft_strdup(ct->token->word);
		new->in_type = ct->token->type;
	}
	else
	{
		new->fd_out = open(ct->token->word, O_WRONLY | O_CREAT, 0644);
		if (new->fd_out != -1)
			close(new->fd_out);
		else
			(*tmp_lst)->error_flag = 1;
		safe_free(new->fd_out_name);
		new->fd_out_name = ft_strdup(ct->token->word);
		new->out_type = ct->token->type;
	}
}

void	stack_cmd(t_cmd_tree *ct, t_lst **tmp_lst, char ***cmd, t_env *env_lst)
{
	if (ct == NULL || (*tmp_lst)->error_flag)
		return ;
	if (ct->bnf_type == BNF_COMMAND_PART)
	{
		ct->token->word = expand(ct->token->word, env_lst);
		if (6 <= ct->token->type && ct->token->type <= 9)
			add_redir(ct, tmp_lst, wft_lstlast_lst(*tmp_lst));
		else
			stack_cmd_else(ct, cmd);
		return ;
	}
	else
	{
		stack_cmd(ct->left, tmp_lst, cmd, env_lst);
		stack_cmd(ct->right, tmp_lst, cmd, env_lst);
	}
}

void	play_cmd(t_cmd_tree *ct, t_env *env_lst, t_lst **tmp_lst)
{
	t_lst	*new;
	char	**cmd;

	if (ct == NULL)
		return ;
	if (ct->bnf_type == BNF_COMMAND)
	{
		new = wft_calloc(1, sizeof(t_lst));
		wft_lstadd_back_lst(tmp_lst, new);
		cmd = wft_calloc(1, sizeof(char *));
		new->fd_in = -1;
		new->fd_out = -1;
		new->prev_pipe = -1;
		stack_cmd(ct, tmp_lst, &cmd, env_lst);
		new->cmd = cmd;
	}
	else if (ct->bnf_type == BNF_PIPELINE)
	{
		play_cmd(ct->left, env_lst, tmp_lst);
		play_cmd(ct->right, env_lst, tmp_lst);
	}
}

void	start_exec(t_cmd_tree *ct, t_env *env_lst, t_heredoc *hed_lst)
{
	t_lst	*tmp_lst;

	if (ct == NULL)
		return ;
	if (ct -> bnf_type == BNF_LIST)
	{
		start_exec(ct->left, env_lst, hed_lst);
		if (ct->left->token && ((ct->left->token->type == T_OR && g_exit) \
		|| (ct->left->token->type == T_AND && !g_exit)))
			start_exec(ct->right, env_lst, hed_lst);
	}
	else if (ct -> bnf_type == BNF_PIPELINE)
	{
		tmp_lst = NULL;
		if (ct -> left -> bnf_type == BNF_LIST)
			start_exec(ct->left, env_lst, hed_lst);
		else
			play_cmd(ct->left, env_lst, &tmp_lst);
		if (ct -> right && ct -> right -> bnf_type == BNF_LIST)
			start_exec(ct->right, env_lst, hed_lst);
		else
			play_cmd(ct->right, env_lst, &tmp_lst);
		if (tmp_lst)
			start_play_executor(&tmp_lst, env_lst, hed_lst);
	}
}
