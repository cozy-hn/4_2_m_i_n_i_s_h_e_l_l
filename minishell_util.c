/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiko <jiko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 22:27:20 by jiko              #+#    #+#             */
/*   Updated: 2024/01/26 05:24:17 by jiko             ###   ########.fr       */
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

void	remove_quotes(char **word)
{
	int		s_quote;
	int		d_quote;
	char	*tmp;
	char	*ret;

	s_quote = 0;
	d_quote = 0;
	tmp = word;
	ret = wft_calloc(1, sizeof(char));
	while (*word)
	{
		if (*word == '\'' && !d_quote)
			s_quote = !s_quote;
		else if (*word == '\"' && !s_quote)
			d_quote = !d_quote;
		else
			ret = ft_strjoin_char(ret, *word);
		if (*word)
			word++;
	}
	safe_free(tmp);
	return (ret);
}

int	ft_is_env_word(char c, int i)
{
	if (i == 0)
		return (ft_isalpha(c) || c == '_' || c == '?');
	else
		return (ft_isalnum(c) || c == '_');
}
