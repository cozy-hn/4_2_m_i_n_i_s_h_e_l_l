/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiko <jiko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 22:27:20 by jiko              #+#    #+#             */
/*   Updated: 2024/01/22 19:12:29 by jiko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	remove_space(char *line, int *i)
{
	int	flag;

	flag = 0;
	while (line[*i] && is_space(line[*i]))
	{
		(*i)++;
		flag = 1;
	}
	return (flag);
}

int	ft_is_env_word(char c, int i)
{
	if (i == 0)
		return (ft_isalpha(c) || c == '_' || c == '?');
	else
		return (ft_isalnum(c) || c == '_');
}
