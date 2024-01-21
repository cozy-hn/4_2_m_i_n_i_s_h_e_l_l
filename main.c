/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiko <jiko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 17:53:03 by jiko              #+#    #+#             */
/*   Updated: 2024/01/21 20:22:39 by jiko             ###   ########.fr       */
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

// int	make_env_lst(t_env *tmp, char **env)
// {
// 	int		i;

// 	i = -1;
// 	while (env[++i])
// 	{
// 		tmp->key = ft_strndup(env[i], ft_strchr(env[i], '='));
// 		tmp->value = ft_strdup(ft_strchr(env[i], '=') + 1);
// 		if (env[i + 1])
// 		{
// 			tmp->next = (t_env *)malloc(sizeof(t_env));
// 			tmp = tmp->next;
// 		}
// 		else
// 			tmp->next = NULL;
// 	}
// 	return (0);
// }

int	init_arg(t_env **env_lst, char **env)
{
	*env_lst = wft_calloc(sizeof(t_env), 1);
	*env_lst = make_env_lst(env);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	char			*line;
	t_token			*token;
	t_cmd_tree		*cmd_tree;
	t_env			*env_lst;
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	main_init(argc, argv);
	init_arg(&env_lst, env);
	while (1)
	{
		token = NULL;
		cmd_tree = NULL;
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
			continue ;
		}
		// test_tr_print_tree(cmd_tree); //test
		printf("expander\n\n");
		expander(&cmd_tree, env_lst);
		// {
		// 	safe_free(line);
		// 	free_cmd_tree(cmd_tree);
		// 	free_token(token);
		// 	free_env_lst(env_lst);
		// 	tcsetattr(STDIN_FILENO, TCSANOW, &term);
		// 	atexit(check_leak);
		// 	return (0);
		// }
		// test_tr_print_tree(cmd_tree); //test
		start_exec(cmd_tree, env_lst);
		// printf("falut test out\n");
		safe_free(line);
		free_cmd_tree(cmd_tree);
		free_token(token);
	}
	free_env_lst(env_lst);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	atexit(check_leak);
	return (0);
}
