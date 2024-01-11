/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiko <jiko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 17:53:03 by jiko              #+#    #+#             */
/*   Updated: 2024/01/11 22:53:03 by jiko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_leak(void)
{
	system("leaks --list -- minishell");
}

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
}

void	main_init(int argc, char **argv)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	set_signal(SHE, SHE);
	(void)argc;
	(void)argv;
}

// void	wait_child(void)
// {
// 	int		status;
// 	int		signo;
// 	int		i;

// 	i = 0;
// 	while (wait(&status) != -1)
// 	{
// 		if (WIFSIGNALED(status))
// 		{
// 			signo = WTERMSIG(status);
// 			if (signo == SIGINT && i++ == 0)
// 				ft_putstr_fd("^C\n", STDERR_FILENO);
// 			else if (signo == SIGQUIT && i++ == 0)
// 				ft_putstr_fd("^\\Quit: 3\n", STDERR_FILENO);
// 			g_exit_code = 128 + signo;
// 		}
// 		else
// 			g_exit_code = WEXITSTATUS(status);
// 	}
// }

int	main(int argc, char **argv, char **env)
{
	char			*line;
	t_token			*token;
	t_cmd_tree		*cmd_tree;
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	main_init(argc, argv);
	while (1)
	{
		token = NULL;
		cmd_tree = NULL;
		(void)env;
		line = readline("minishell$ ");
		if (!line)
			break ;
		add_history(line);
		if (tokenizer(line, &token))
			continue ;
		// print_token(token); //test
		if (parser(&cmd_tree, &token))
		{
			// test_tr_print_tree(cmd_tree); //test
			safe_free(line);
			free_cmd_tree(cmd_tree);
			free_token(token);
			continue ;
		}
		// test_tr_print_tree(cmd_tree); //test
		safe_free(line);
		free_cmd_tree(cmd_tree);
		free_token(token);
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	atexit(check_leak);
	return (0);
}
