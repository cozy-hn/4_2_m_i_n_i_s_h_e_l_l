/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiko <jiko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 07:40:22 by sumjo             #+#    #+#             */
/*   Updated: 2024/01/31 20:32:24 by jiko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_BONUS_H
# define BUILTIN_BONUS_H

# include "../minishell_bonus.h"

char	**ft_dup_env(char **env);
int		ft_free_arr(char **arr);
int		ft_print_env(char **env);
char	**ft_sort_env(char **env_arr);
int		has_char(char *str, char c);
int		env_len(char *env);
int		throw_error(char *cmd, char *str, char *msg);

int		ft_cd(t_main *main, char **cmd);
int		ft_echo(char **cmd);
int		ft_export(t_env **env, char **cmd);
int		ft_unset(t_env **env, char **cmd);
int		ft_env(t_env **env);
int		ft_pwd(t_main *main);
int		ft_exit(t_main *main, char **cmd);
void	free_env_lst(t_env *env);
char	*ft_strndup(char *s, char *end);
char	*get_env_value(t_main *main, char *key);
int		add_env(t_env **env, char *str);
void	throw_export_error(char *cmd, char *str, char *msg);
int		same_env(char *env, char *str);
int		modify_env(char **str);
t_env	*make_env_lst(char **env);
char	**env_lst_to_arr(t_env *env);
int		ft_free_env_lst(t_env *env);

#endif
