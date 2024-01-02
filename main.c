/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiko <jiko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 17:53:03 by jiko              #+#    #+#             */
/*   Updated: 2024/01/02 19:53:14 by jiko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_leak(void)
{
	system("leaks --list -- minishell");
}

int	main(int argc, char **argv, char **env)
{
	char	*line;

	while (1)
	{
		(void)argc;
		(void)argv;
		(void)env;
		line = readline("minishell$ ");
		if (strcmp(line, "exit") == 0)
		{
			free(line);	
			break ;
		}
		free(line);	
	}
	atexit(check_leak);
	return (0);
}
