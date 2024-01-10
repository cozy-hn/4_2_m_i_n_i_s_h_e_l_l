/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiko <jiko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:33:57 by jiko              #+#    #+#             */
/*   Updated: 2024/01/09 16:36:56 by jiko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_type(char *line, int *i)
{
	if (is_or(line, i))
		return (T_OR);
	if (is_pipe(line, i))
		return (T_PIPE);
	if (is_and(line, i))
		return (T_AND);
	if (is_l_d_redir(line, i))
		return (T_L_D_REDIR);
	if (is_r_d_redir(line, i))
		return (T_R_D_REDIR);
	if (is_l_redir(line, i))
		return (T_L_REDIR);
	if (is_r_redir(line, i))
		return (T_R_REDIR);
	if (is_l_par(line, i))
		return (T_L_PAR);
	if (is_r_par(line, i))
		return (T_R_PAR);
	return (0);
}

int	word_checker(char *line, int dquote, int squote)
{
	if (dquote || squote)
		return (1);
	if (is_space(line[0]))
		return (0);
	if (is_meta(line))
		return (0);
	return (1);
}

char	*set_word(char *line, int *i)
{
	int		dquote;
	int		squote;
	char	*word;

	dquote = 0;
	squote = 0;
	word = wft_calloc(1, sizeof(char));
	while (line[*i] && word_checker(&line[*i], dquote, squote))
	{
		if (line[*i] == '"' && !squote)
			dquote = !dquote;
		else if (line[*i] == '\'' && !dquote)
			squote = !squote;
		word = ft_strjoin_char(word, line[*i]);
		(*i)++;
	}
	if (dquote || squote)
	{
		printf("minishell: syntax error(quote)\n");
		return (NULL);
	}
	return (word);
}


void	tokenizer(char *line, t_token **token)
{
	int		i;
	t_token	*new;

	i = 0;
	remove_space(line, &i);
	while (line[i])
	{	
		if (remove_space(line, &i))
			continue ;
		new = wft_calloc(1, sizeof(t_token));
		if (is_meta(&line[i]))
			new->type = set_type(line, &i);
		else
		{
			new->type = T_WORD;
			new->word = set_word(line, &i);
		}
		wft_lstadd_back(token, new);
	}
}
