/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec_util_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiko <jiko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 06:00:48 by jiko              #+#    #+#             */
/*   Updated: 2024/01/31 17:21:39 by jiko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

void	start_play_executor(t_lst **tmp_lst, t_env *env_lst, t_heredoc *hed_lst)
{
	print_lst(*tmp_lst);
	play_executor(tmp_lst, env_lst, hed_lst);
	free_lst(tmp_lst);
}

void	stack_cmd_else(t_cmd_tree *ct, char ***cmd)
{
	char	**tmp;
	int		cmd_len;

	cmd_len = 0;
	while ((*cmd)[cmd_len])
		cmd_len++;
	tmp = wft_calloc(cmd_len + 2, sizeof(char *));
	ft_memcpy(tmp, *cmd, cmd_len * sizeof(char *));
	tmp[cmd_len] = ft_strdup(ct->token->word);
	safe_free(*cmd);
	*cmd = tmp;
}
