/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_checker_2_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 22:43:37 by jiko              #+#    #+#             */
/*   Updated: 2024/01/26 12:21:37 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	is_l_redir(char *line, int *i)
{
	if (line[*i] && line[*i] == '<')
	{
		(*i)++;
		return (1);
	}
	return (0);
}

int	is_r_redir(char *line, int *i)
{
	if (line[*i] && line[*i] == '>')
	{
		(*i)++;
		return (1);
	}
	return (0);
}

int	is_l_d_redir(char *line, int *i)
{
	if (line[*i] && line[*i] == '<' && line[*i + 1] == '<')
	{
		(*i) += 2;
		return (1);
	}
	return (0);
}

int	is_r_d_redir(char *line, int *i)
{
	if (line[*i] && line[*i] == '>' && line[*i + 1] == '>')
	{
		(*i) += 2;
		return (1);
	}
	return (0);
}
