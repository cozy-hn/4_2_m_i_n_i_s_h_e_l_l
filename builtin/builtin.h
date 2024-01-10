#ifndef BUILTIN_H
# define BUILTIN_H

#define OPTION  1
#define NO_OPTION  0

#include "../libft/libft.h"
#include "../minishell.h"

char	**ft_dup_env(char **env);
int		ft_free_arr(char **arr);
int		ft_print_env(char **env);
char	**ft_sort_env(char **env);
int		has_char(char *str, char c);
int		env_len(char *env);

int ft_cd(t_arg *arg, char **cmd);
int	ft_echo(char **cmd);
int	ft_export(t_arg *arg, char **cmd);
int	ft_unset(t_arg *arg, char **cmd);
int	ft_env(t_env *env);
int	ft_pwd(void);
int	ft_exit(t_arg *arg, char **cmd);
int free_env_lst(t_env *env);
char *ft_strndup(char *s, char *end);
int	make_env_lst(t_arg *arg, char **env);
char *get_env_value(t_env *env, char *key);




// char	**set_env(char **env, char *str);
// int		ft_export(char ***env, char **str);
int		ft_export(t_arg *arg, char **cmd);
int		same_env(char *env, char *str);
int		throw_error(char *cmd, char *str, char *msg);
int		modify_env(char **str);
char	*ft_strndup(char *s, char *end);
int		make_env_lst(t_arg *arg, char **env);
char	**env_lst_to_arr(t_env *env);
int ft_free_env_lst(t_env *env);

#endif
