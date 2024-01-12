/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiko <jiko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 17:53:03 by jiko              #+#    #+#             */
/*   Updated: 2024/01/12 22:06:15 by jiko             ###   ########.fr       */
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
int	throw_error(char *cmd, char *str, char *msg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("':", 2);
	ft_putendl_fd(msg, 2);
	return (1);
}

char	*ft_strndup(char *s, char *end)
{
	int		i;
	char	*ret;

	if (!end)
	{
		ret = ft_strdup(s);
		return (ret);
	}
	i = -1;
	ret = (char *)malloc(sizeof(char) * (end - s + 1));
	while (++i < end - s)
		ret[i] = s[i];
	ret[i] = 0;
	return (ret);
}

int	make_env_lst(t_arg *arg, char **env)
{
	t_env	*tmp;
	int		i;

	arg->env = (t_env *)malloc(sizeof(t_env));
	tmp = arg->env;
	i = -1;
	while (env[++i])
	{
		tmp->key = ft_strndup(env[i], ft_strchr(env[i], '='));
		tmp->value = ft_strdup(ft_strchr(env[i], '=') + 1);
		if (env[i + 1])
		{
			tmp->next = (t_env *)malloc(sizeof(t_env));
			tmp = tmp->next;
		}
		else
			tmp->next = NULL;
	}
	return (0);
}

char	*return_path(char **env)
{
	char	*arr;
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp("PATH=", env[i], 5) == 0)
		{
			arr = ft_strdup(env[i] + 5);
			return (arr);
		}
		i++;
	}
	throw_error("PATH not found", "", "");
	return (NULL);
}

void	get_path(t_arg *arg, char **env)
{
	char	*arr;
	int		i;

	i = 0;
	arr = return_path(env);
	arg->path = ft_split(arr, ':');
	while (arg->path[i])
	{
		arg->path[i] = ft_strjoin(arg->path[i], "/");
		i++;
	}
	free(arr);
}

int	init_arg(t_arg **arg, char **env)
{
	*arg = wft_calloc(sizeof(t_arg), 1);
	get_path(*arg, env);
	make_env_lst(*arg, env);
	return (0);
}

char	*get_env_value(t_env *env, char *key)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, ft_strlen(key)) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

int	main(int argc, char **argv, char **env)
{
	char			*line;
	t_token			*token;
	t_cmd_tree		*cmd_tree;
	t_arg			*arg;
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	main_init(argc, argv);
	init_arg(&arg, env);
	// print_env(arg->env);
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
			test_tr_print_tree(cmd_tree); //test
			safe_free(line);
			continue ;
		}
		if (expander(&cmd_tree, arg))
		{
			test_tr_print_tree(cmd_tree); //test
			continue ;
		}
		test_tr_print_tree(cmd_tree); //test
		safe_free(line);
		free_cmd_tree(cmd_tree);
		free_token(token);
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	atexit(check_leak);
	return (0);
}
