/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 07:45:41 by sumjo             #+#    #+#             */
/*   Updated: 2024/02/01 14:37:02 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "../minishell.h"
# include "../builtin/builtin.h"

void	close_in_out_fds(t_arg *arg);
char	**return_commands(t_arg *arg, char **cmd);
void	get_path(t_arg *arg);
char	*return_path(t_env *env);
int		throw_error(char *cmd, char *str, char *msg);
char	**parse_commands(t_arg *arg, char **cmd);
int		is_builtin(t_lst *lst);
int		run_builtin(t_lst *lst, t_main *main);
int		executor_helper(t_lst *lst, t_main *main);
t_lst	*mock_lst(void);
int		execute(t_lst *lst, t_main *main);
void	connect_original_fd(t_lst *lst, int *fd);
int		handle_redirection(t_lst *lst);
void	connect_redir(t_lst *lst);
void	duplicate_original_fd(int *fd);
int		run_builtin_helper(t_main *main);
void	ft_wait(int pid, t_main *main);
void	turn_to_shell_mode(void);
void	turn_off_default(void);

#endif
