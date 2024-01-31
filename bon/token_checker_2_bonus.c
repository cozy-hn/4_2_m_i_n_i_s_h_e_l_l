/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_checker_2_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiko <jiko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 22:43:37 by jiko              #+#    #+#             */
/*   Updated: 2024/01/31 20:28:07 by jiko             ###   ########.fr       */
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
