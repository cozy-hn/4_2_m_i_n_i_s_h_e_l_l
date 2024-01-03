/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiko <jiko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 17:53:03 by jiko              #+#    #+#             */
/*   Updated: 2024/01/03 22:34:57 by jiko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_leak(void)
{
	system("leaks --list -- minishell");
}

void	tokenizer(char *line, t_token **token)
{
	int		i;
	char	*tmp;

	i = remove_space(line);
	while (line[i])
	{	
		i = remove_space(line);
		if (!is_meta(line[i]))
		{
		}

	}
}

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_token	*token;

	token = NULL;
	while (1)
	{
		(void)argc;
		(void)argv;
		(void)env;
		line = readline("minishell$ ");
		tokenizer(line, &token);
		if (strcmp(line, "exit") == 0)
			break ;
		free(line);
	}
	free(line);
	atexit(check_leak);
	return (0);
}
