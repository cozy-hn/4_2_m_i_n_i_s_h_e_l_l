/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 22:04:35 by jiko              #+#    #+#             */
/*   Updated: 2024/01/28 02:04:39 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_env(char **word, t_main *main)
{
	char	*ret;
	char	*env;
	int		i;

	i = 0;
	(*word)++;
	ret = wft_calloc(1, sizeof(char));
	if (**word == '?')
		i++;
	else
	{
		while (*(*word + i) && ft_is_env_word(*(*word + i), i))
			i++;
	}
	env = ft_substr(*word, 0, i);
	ret = wft_strjoin(ret, get_env_value(main, env));
	if (i > 0)
		(*word) += i - 1;
	safe_free(env);
	return (ret);
}

void	expand_elif(char **word, char **ret, t_main *main)
{
	if (ft_is_env_word(*(*word + 1), 0) == 0)
		*ret = ft_strjoin_char(*ret, '$');
	else
		*ret = wft_strjoin(*ret, expand_env(word, main));
}

char	*expand(char *word, t_main *main)
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
		else if (*word == '$' && !s_quote)
			expand_elif(&word, &ret, main);
		else
			ret = ft_strjoin_char(ret, *word);
		if (*word)
			word++;
	}
	safe_free(tmp);
	return (ret);
}
