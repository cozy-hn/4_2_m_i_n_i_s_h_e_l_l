/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_checker_1_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 22:42:54 by jiko              #+#    #+#             */
/*   Updated: 2024/01/26 12:21:37 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

int	is_meta(char *line)
{
	if (line[0] && (line[0] == '|' || line[0] == '<' || line[0] == '>'
			|| (line[0] == '&' && line[1] == '&') || line[0] == '('
			|| line[0] == ')'))
		return (1);
	return (0);
}

int	is_pipe(char *line, int *i)
{
	if (line[*i] && line[*i] == '|')
	{
		(*i)++;
		return (1);
	}
	return (0);
}

int	is_or(char *line, int *i)
{
	if (line[*i] && line[*i] == '|' && line[*i + 1] == '|')
	{
		(*i) += 2;
		return (1);
	}
	return (0);
}

int	is_and(char *line, int *i)
{
	if (line[*i] && line[*i] == '&' && line[*i + 1] == '&')
	{
		(*i) += 2;
		return (1);
	}
	return (0);
}
