/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiko <jiko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 22:04:35 by jiko              #+#    #+#             */
/*   Updated: 2024/01/12 23:44:39 by jiko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_env(char **word, t_arg *arg)
{
	char	*ret;
	char	*env;
	int		i;

	i = 0;
	ret = wft_calloc(1, sizeof(char));
	if (**word == '?')
	{
		env = ft_itoa(g_exit_status);
		ret = wft_strjoin(ret, env);
		(*word)++;
	}
	else
	{
		printf("falut test\n");
		printf("word: %s\n", *word);
		while (*(*word + i) && ft_is_env_word(*(*word + i), i))
			i++;
		printf("word: %s\n", *word);
		env = ft_substr(*word, 1, i);
		ret = wft_strjoin(ret, get_env_value(arg->env, env));
		(*word) += i;
	}
	safe_free(env);
	return (ret);
}

char	*expand(char *word, t_arg *arg)
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
		if (*word == '\'')
			s_quote = !s_quote;
		else if (*word == '\"')
			d_quote = !d_quote;
		else if (*word == '$' && !s_quote)
		{
			word++;
			ret = wft_strjoin(ret, expand_env(&word, arg));
		}
		else
			ret = ft_strjoin_char(ret, *word);
		if (*word)
			word++;
	}
	safe_free(tmp);
	return (ret);
}

int	expander(t_cmd_tree **cmd_tree, t_arg *arg)
{
	if (!*cmd_tree)
		return (0);
	if ((*cmd_tree)->bnf_type == BNF_COMMAND_PART)
		(*cmd_tree)->token->word = expand((*cmd_tree)->token->word, arg);
	expander(&(*cmd_tree)->left, arg);
	expander(&(*cmd_tree)->right, arg);
	return (0);
}
