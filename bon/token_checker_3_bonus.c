/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_checker_3_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiko <jiko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 22:44:38 by jiko              #+#    #+#             */
/*   Updated: 2024/01/31 20:28:07 by jiko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	is_l_par(char *line, int *i)
{
	if (line[*i] && line[*i] == '(')
	{
		(*i)++;
		return (1);
	}
	return (0);
}

int	is_r_par(char *line, int *i)
{
	if (line[*i] && line[*i] == ')')
	{
		(*i)++;
		return (1);
	}
	return (0);
}

int	is_quote(char c)
{
	if (c == '\'')
		return (1);
	return (0);
}

int	is_d_quote(char c)
{
	if (c == '\"')
		return (1);
	return (0);
}
