/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 03:10:47 by jiko              #+#    #+#             */
/*   Updated: 2024/01/25 06:26:11 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_lst(t_lst *lst)
{
	int i;
	printf("====print arg====\n");
	while (lst)
	{
		i = 0;
		printf("====print lst====\n");
		if (lst->cmd)
		{
			printf("fd_in_name: %s\n", lst->fd_in_name);
			printf("fd_out_name: %s\n", lst->fd_out_name);
			while (lst->cmd[i])
			{
				// printf("lst->cmd[%d] addr %p\n", i, &(lst->cmd[i]));
				printf("lst->cmd[%d]: ", i);
				if (lst->cmd[i])
					printf("%s\n", lst->cmd[i]);
				else
					printf("NULL\n");
				i++;
			}
		}
		else
			printf("lst->cmd: NULL\n");
		lst = lst->next;
	}
}

void	play_executor(t_lst **tmp_lst, t_env *env_lst)
{
	t_arg	*arg;

	arg = wft_calloc(1, sizeof(t_arg));
	arg->env = env_lst;
	arg->lst = *tmp_lst;
	executor(arg);
	safe_free(arg);
	// print_lst(*tmp_lst);
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

void	add_redir(t_cmd_tree *cmd_tree, t_lst **tmp_lst, t_lst *new)
{
	if (cmd_tree->token->type == T_L_REDIR || cmd_tree->token->type == T_L_D_REDIR)
	{
		new->fd_in = open(cmd_tree->token->word, O_RDONLY);
		if (new->fd_in != -1)
			close(new->fd_in);
		else
			(*tmp_lst)->error_flag = 1;
		safe_free(new->fd_in_name);
		new->fd_in_name = ft_strdup(cmd_tree->token->word);
		new->in_type = cmd_tree->token->type;
	}
	else
	{
		new->fd_out = open(cmd_tree->token->word, O_WRONLY | O_CREAT, 0644);
		if (new->fd_out != -1)
			close(new->fd_out);
		else
			(*tmp_lst)->error_flag = 1;
		safe_free(new->fd_out_name);
		new->fd_out_name = ft_strdup(cmd_tree->token->word);
		new->out_type = cmd_tree->token->type;
	}
}

void	stack_cmd(t_cmd_tree *cmd_tree, t_lst **tmp_lst, char ***cmd, t_env *env_lst)
{
	char	**tmp;
	int		cmd_len;

	if (cmd_tree == NULL || (*tmp_lst)->error_flag)
		return ;
	if (cmd_tree->bnf_type == BNF_COMMAND_PART)
	{
		cmd_tree->token->word = expand(cmd_tree->token->word, env_lst);
		if (6 <= cmd_tree->token->type && cmd_tree->token->type <= 9)
			add_redir(cmd_tree, tmp_lst, wft_lstlast_lst(*tmp_lst));
		else
		{
			cmd_len = 0;
			while ((*cmd)[cmd_len])
				cmd_len++;
			tmp = wft_calloc(cmd_len + 2, sizeof(char *));
			ft_memcpy(tmp, *cmd, cmd_len * sizeof(char *));
			tmp[cmd_len] = ft_strdup(cmd_tree->token->word);
			safe_free(*cmd);
			*cmd = tmp;
		}
		return ;
	}
	else
	{
		stack_cmd(cmd_tree->left, tmp_lst, cmd, env_lst);
		stack_cmd(cmd_tree->right, tmp_lst, cmd, env_lst);
	}
}

void	play_cmd(t_cmd_tree *cmd_tree, t_env *env_lst, t_lst **tmp_lst)
{
	t_lst	*new;
	char	**cmd;

	if (cmd_tree == NULL)
		return ;
	if (cmd_tree->bnf_type == BNF_COMMAND)
	{
		new = wft_calloc(1, sizeof(t_lst));
		wft_lstadd_back_lst(tmp_lst, new);
		cmd = wft_calloc(1, sizeof(char *));
		new->fd_in = -1;
		new->fd_out = -1;
		new->prev_pipe = -1;
		stack_cmd(cmd_tree, tmp_lst, &cmd, env_lst);
		new->cmd = cmd;
	}
	else if (cmd_tree->bnf_type == BNF_PIPELINE)
	{
		play_cmd(cmd_tree->left, env_lst, tmp_lst);
		play_cmd(cmd_tree->right, env_lst, tmp_lst);
	}
}

void	start_exec(t_cmd_tree *cmd_tree, t_env *env_lst)
{
	t_lst	*tmp_lst;

	if (cmd_tree == NULL)
		return ;
	if (cmd_tree -> bnf_type == BNF_LIST)
	{
		start_exec(cmd_tree->left, env_lst);
		if (cmd_tree->left->token && ((cmd_tree->left->token->type == T_AND && !g_exit_status) || \
			(cmd_tree->left->token->type == T_OR && g_exit_status)))
			start_exec(cmd_tree->right, env_lst);
	}
	else if (cmd_tree -> bnf_type == BNF_PIPELINE)
	{
		tmp_lst = NULL;
		if (cmd_tree -> left -> bnf_type == BNF_LIST)
			start_exec(cmd_tree->left, env_lst);
		else
			play_cmd(cmd_tree->left, env_lst, &tmp_lst);
		if (cmd_tree -> right && cmd_tree -> right -> bnf_type == BNF_LIST)
			start_exec(cmd_tree->right, env_lst);
		else
			play_cmd(cmd_tree->right, env_lst, &tmp_lst);
		if (tmp_lst)
		{
			// print_lst(tmp_lst);
			play_executor(&tmp_lst, env_lst);
			free_lst(&tmp_lst);
		}
	}
}
