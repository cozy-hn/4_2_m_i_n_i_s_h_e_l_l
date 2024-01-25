/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiko <jiko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 17:53:03 by jiko              #+#    #+#             */
/*   Updated: 2024/01/26 03:37:32 by jiko             ###   ########.fr       */
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
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
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

t_env	*main_init(int argc, char **argv, char **env)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	set_signal(SHE, SHE);
	(void)argc;
	(void)argv;
	return (make_env_lst(env));
}

int	main(int argc, char **argv, char **env)
{
	char			*line;
	t_token			*token;
	t_cmd_tree		*cmd_tree;
	t_env			*env_lst;
	t_heredoc		*hed_lst;

	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	env_lst = main_init(argc, argv, env);
	while (1)
	{
		token = NULL;
		cmd_tree = NULL;
		hed_lst = NULL;
		line = readline("minishell$ ");
		if (!line)
		{
			ft_putstr_fd("\033[A", 1);
			ft_putstr_fd("minishell$ exit\n", STDERR_FILENO);
			exit(g_exit);
		}
		add_history(line);
		if (tokenizer(line, &token) || parser(&cmd_tree, &token, &hed_lst))
			continue ;
		// test_tr_print_tree(cmd_tree);
		start_exec(cmd_tree, env_lst, hed_lst);
		heredoc_free(hed_lst);
		free_cmd_tree(cmd_tree);
		free_token(token);
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	exit(g_exit);
	return (g_exit);
}
