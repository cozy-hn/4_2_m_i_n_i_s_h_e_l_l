/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiko <jiko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 22:27:20 by jiko              #+#    #+#             */
/*   Updated: 2024/01/07 02:27:04 by jiko             ###   ########.fr       */
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


int	is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

int	is_meta(char *line)
{
	if (line[0] && (line[0] == '|' || line[0] == '<' || line[0] == '>'
			|| (line[0] == '&' && line[1] == '&') || line[0] == '('
			|| line[0] == ')'))
		return (1);
	return (0);
}

int	is_pipe(char *line, int *i)
{
	if (line[*i] && line[*i] == '|')
	{
		(*i)++;
		return (1);
	}
	return (0);
}

int	is_or(char *line, int *i)
{
	if (line[*i] && line[*i] == '|' && line[*i + 1] && line[*i + 1] == '|')
	{
		(*i) += 2;
		return (1);
	}
	return (0);
}

int	is_and(char *line, int *i)
{
	if (line[*i] && line[*i] == '&' && line[*i + 1] == '&')
	{
		(*i) += 2;
		return (1);
	}
	return (0);
}

int	is_l_redir(char *line, int *i)
{
	if (line[*i] && line[*i] == '<')
	{
		(*i)++;
		return (1);
	}
	return (0);
}

int	is_r_redir(char *line, int *i)
{
	if (line[*i] && line[*i] == '>')
	{
		(*i)++;
		return (1);
	}
	return (0);
}
int	is_l_d_redir(char *line, int *i)
{
	if (line[*i] && line[*i] == '<' && line[*i + 1] == '<')
	{
		(*i) += 2;
		return (1);
	}
	return (0);
}

int	is_r_d_redir(char *line, int *i)
{
	if (line[*i] && line[*i] == '>' && line[*i + 1] == '>')
	{
		(*i) += 2;
		return (1);
	}
	return (0);
}

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

int is_quote(char c)
{
	if (c == '\'')
		return (1);
	return (0);
}
int is_d_quote(char c)
{
	if (c == '\"')
		return (1);
	return (0);
}

void free_token(t_token *token)
{
	t_token *tmp;

	while (token)
	{
		tmp = token->next;
		if (token->word)
			free(token->word);
		free(token);
		token = tmp;
	}
}



