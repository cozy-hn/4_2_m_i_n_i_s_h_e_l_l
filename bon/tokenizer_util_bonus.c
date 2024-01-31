/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_util_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 18:47:22 by jiko              #+#    #+#             */
/*   Updated: 2024/01/26 12:21:37 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

void	tokenizer_if_is_meta(char *line, int *i, t_token *new)
{
	if (is_meta(&line[*i]))
	{
		new->type = set_type(line, i);
		new->word = set_meta_word(new->type);
	}
	else
	{
		new->type = T_WORD;
		new->word = set_word(line, i);
	}
}
