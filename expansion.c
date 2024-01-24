/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiko <jiko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 22:04:35 by jiko              #+#    #+#             */
/*   Updated: 2024/01/24 21:40:05 by jiko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_env(char **word, t_env *env_lst)
{
	char	*ret;
	char	*env;
	int		i;

	i = 0;
	(*word)++;
	ret = wft_calloc(1, sizeof(char));
	while (*(*word + i) && ft_is_env_word(*(*word + i), i))
		i++;
	env = ft_substr(*word, 0, i);
	ret = wft_strjoin(ret, get_env_value(env_lst, env));
	if (i > 0)
		(*word) += i - 1;
	safe_free(env);
	return (ret);
}

char	*expand(char *word, t_env *env_lst)
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
		{
			if (ft_is_env_word(*(word + 1), 0) == 0)
				ret = ft_strjoin_char(ret, '$');
			else
				ret = wft_strjoin(ret, expand_env(&word, env_lst));
		}
		else
			ret = ft_strjoin_char(ret, *word);
		if (*word)
			word++;
	}
	safe_free(tmp);
	return (ret);
}
