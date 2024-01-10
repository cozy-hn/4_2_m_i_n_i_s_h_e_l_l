/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiko <jiko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 22:27:20 by jiko              #+#    #+#             */
/*   Updated: 2024/01/09 14:25:17 by jiko             ###   ########.fr       */
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

