/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiko <jiko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 17:53:26 by jiko              #+#    #+#             */
/*   Updated: 2024/01/03 22:34:40 by jiko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h> // for tmp
// # include <signal.h>
// # include <unistd.h>
// # include <sys/types.h>
// # include <sys/wait.h>
// # include <sys/stat.h>
// # include <fcntl.h>
// # include <dirent.h>
// # include <errno.h>	

int	remove_space(char *line);
int	is_space(char c);
int	is_meta(char c);
int	is_quote(char c);

typedef enum type
{
	T_NULL,
	T_COMMAND,
	T_DOUBLE_QUOTE,
	T_SINGLE_QUOTE,
	T_INPUT_REDIR,
	T_HERE_DOC,
	T_LIMITER,
	T_OUTPUT_REDIR,
	T_APPEND_REDIR,
	T_PIPE
}	t_type;

typedef struct s_token
{
	t_type			type;
	char			*word;
	struct s_token	*next;
}	t_token;

void	*ft_calloc(size_t count, size_t size);
int		remove_space(char *line);
int		is_space(char c);
int		is_meta(char c);
int		is_quote(char c);
int		is_double_quote(char c);
int		is_single_quote(char c);

#endif
