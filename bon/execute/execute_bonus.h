/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 07:45:41 by sumjo             #+#    #+#             */
/*   Updated: 2024/01/26 12:22:09 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_BONUS_H
# define EXECUTE_BONUS_H

# include "../minishell_bonus.h"
# include "../builtin/builtin_bonus.h"

void	close_in_out_fds(t_arg *arg);
char	**return_commands(t_arg *arg, char **cmd);
void	get_path(t_arg *arg);
char	*return_path(t_env *env);
int		throw_error(char *cmd, char *str, char *msg);
char	**parse_commands(t_arg *arg, char **cmd);
int		is_builtin(t_lst *lst);
int		run_builtin(t_lst *lst, t_arg *arg);
int		executor_helper(t_lst *lst, t_arg *arg);
t_lst	*mock_lst(void);
int		execute(t_lst *lst, t_arg *arg);
void	connect_original_fd(t_lst *lst, int *fd);
int		handle_redirection(t_lst *lst);
void	connect_redir(t_lst *lst);
void	duplicate_original_fd(int *fd);
int		run_builtin_helper(t_lst *lst, t_arg *arg);
void	ft_wait(int pid);

#endif
