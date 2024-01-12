/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_for_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiko <jiko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:33:32 by jiko              #+#    #+#             */
/*   Updated: 2024/01/12 19:44:52 by jiko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token(t_token *token)
{
	while (token)
	{
		printf("type: %d\n", token->type);
		printf("word: %s\n", token->word);
		printf("==========\n");
		token = token->next;
	}
}

void	print_env(t_env *env)
{
	while (env)
	{
		printf("key: %s\n", env->key);
		printf("value: %s\n", env->value);
		printf("==========\n");
		env = env->next;
	}
}
