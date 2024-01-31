/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiko <jiko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 05:07:10 by sumjo             #+#    #+#             */
/*   Updated: 2024/01/26 08:00:47 by jiko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (signo == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	heredoc_free(t_heredoc *hed_lst)
{
	t_heredoc	*tmp;
	t_heredoc	*tmp2;

	tmp = hed_lst;
	while (tmp)
	{
		tmp2 = tmp;
		if (access(tmp->name, F_OK) == 0)
			unlink(tmp->name);
		safe_free(tmp->name);
		tmp = tmp->next;
		safe_free(tmp2);
	}
}

int	heredoc_handler(t_heredoc *hed_lst)
{
	write(1, "\n", 1);
	heredoc_free(hed_lst);
	return (1);
}

void	set_signal(int sig_int, int sig_quit)
{
	if (sig_int == IGN)
		signal(SIGINT, SIG_IGN);
	if (sig_int == DFL)
		signal(SIGINT, SIG_DFL);
	if (sig_int == SHE)
		signal(SIGINT, signal_handler);
	if (sig_quit == IGN)
		signal(SIGQUIT, SIG_IGN);
	if (sig_quit == DFL)
		signal(SIGQUIT, SIG_DFL);
	if (sig_quit == SHE)
		signal(SIGQUIT, signal_handler);
	if (sig_int == HED)
		signal(SIGINT, SIG_DFL);
	if (sig_quit == HED)
		signal(SIGQUIT, SIG_IGN);
}
