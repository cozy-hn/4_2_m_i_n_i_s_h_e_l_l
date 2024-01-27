/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec_util.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 06:00:48 by jiko              #+#    #+#             */
/*   Updated: 2024/01/28 02:19:04 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	start_play_executor(t_lst **tmp_lst, t_main *main)
{
	play_executor(tmp_lst, main);
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
