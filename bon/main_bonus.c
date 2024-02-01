/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 17:53:03 by jiko              #+#    #+#             */
/*   Updated: 2024/02/01 14:57:16 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

void	main_signal_exit(t_main *main)
{
	ft_putstr_fd("\033[A", 1);
	ft_putstr_fd("minishell$ exit\n", STDERR_FILENO);
	if (g_exit)
		exit(1);
	exit(main->exit_code);
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

void	main_second(t_main *main)
{
	start_exec(main->cmd_tree, main);
	heredoc_free(main->hed_lst);
	free_cmd_tree(main->cmd_tree);
	free_token(main->token);
}

void	main_init_second(t_main *main)
{
	main->token = NULL;
	main->cmd_tree = NULL;
	main->hed_lst = NULL;
}

int	main(int argc, char **argv, char **env)
{
	t_main			main;
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	main.env_lst = main_init(argc, argv, env);
	main.exit_code = 0;
	while (1)
	{
		main_init_second(&main);
		main.line = readline("minishell$ ");
		if (!main.line)
		{
			tcsetattr(STDIN_FILENO, TCSANOW, &term);
			main_signal_exit(&main);
		}
		add_history(main.line);
		if (tokenizer(main.line, &main.token, &main)
			|| parser(&main.cmd_tree, &main.token, &main))
			continue ;
		main_second(&main);
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	exit(main.exit_code);
	return (main.exit_code);
}
