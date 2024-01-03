/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiko <jiko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 22:27:20 by jiko              #+#    #+#             */
/*   Updated: 2024/01/03 22:32:35 by jiko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	remove_space(char *line)
{
	int	i;

	i = 0;
	while (line[i] && is_space(line[i]))
		i++;
	return (i);
}

int	is_space(char c)
{
	if (c == ' ')
		return (1);
	return (0);
}

int	is_meta(char c)
{
	if (c == '|' || c == '<' || c == '>' || c == ';'
		|| c == '&' || c == '(' || c == ')')
		return (1);
	return (0);
}

int	is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

int is_double_quote(char c)
{
	if (c == '\"')
		return (1);
	return (0);
}

int is_single_quote(char c)
{
	if (c == '\'')
		return (1);
	return (0);
}

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*rtm;
	size_t			idx;

	idx = size * count;
	rtm = malloc(idx);
	if (!rtm)
		return (NULL);
	while (idx--)
		rtm[idx] = 0;
	return (rtm);
}
