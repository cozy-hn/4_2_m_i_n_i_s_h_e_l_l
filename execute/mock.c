
#include <string.h>
#include "execute.h"
#include "../minishell.h"


int	init_arg(t_arg *arg)
{
	get_path(arg);
	return (0);
}


t_arg *mock_lst(char *str, char **env1)
{
	str = 0;
	t_env *env = make_env_lst(env1);

	t_arg	*arg;
	t_arg	*tmp;

	t_lst	*lst;
	t_lst	*tmp2;

	arg = wft_calloc(sizeof(t_arg), 1);
	tmp = arg;
	tmp->env = env;


	lst = wft_calloc(sizeof(t_lst), 1);
	tmp2 = lst;
	tmp2->cmd = wft_calloc(sizeof(char *), 100);
	tmp2->cmd[0] = ft_strdup("export");
	tmp2->cmd[1] = ft_strdup("test=hello world");
	tmp2->cmd[2] = NULL;
	tmp2->fd_in = -1;
	tmp2->fd_out = -1;
	tmp2->prev_pipe = -1;
	tmp->lst = lst;
	tmp->condition = T_AND;

	tmp->next = wft_calloc(sizeof(t_arg), 1);
	tmp = tmp->next;
	tmp->env = env;


	lst = wft_calloc(sizeof(t_lst), 1);
	tmp2 = lst;
	tmp2->cmd = wft_calloc(sizeof(char *), 100);
	tmp2->cmd[0] = ft_strdup("env");
	tmp2->cmd[1] = NULL;
	tmp2->fd_in = -1;
	tmp2->fd_out = -1;
	tmp2->prev_pipe = -1;

	tmp2->next = wft_calloc(sizeof(t_lst), 1);
	tmp2 = tmp2->next;
	tmp2->cmd = wft_calloc(sizeof(char *), 100);
	tmp2->cmd[0] = ft_strdup("grep");
	tmp2->cmd[1] = ft_strdup("test");
	tmp2->cmd[2] = NULL;
	tmp2->fd_in = -1;
	tmp2->fd_out = -1;
	tmp2->prev_pipe = -1;

	tmp->lst = lst;
	tmp->condition = 0;
	tmp->next = NULL;

	// printf("arg->lst->cmd[0] = %s\n", arg->lst->cmd[0]);
	// printf("arg->lst->cmd[1] = %s\n", arg->lst->cmd[1]);

	// tmp = arg->next;
	// tmp2 = tmp->lst;
	// printf("arg->next->lst->cmd[0] = %s\n", tmp2->cmd[0]);
	// printf("arg->next->lst->cmd[1] = %s\n", tmp2->cmd[1]);
	// tmp2 = tmp2->next;
	// printf("arg->next->lst->next->cmd[0] = %s\n", tmp2->cmd[0]);
	// printf("arg->next->lst->next->cmd[1] = %s\n", tmp2->cmd[1]);


	return (arg);

}

// t_arg *mock_lst(char *str, char **env1)
// {
// 	t_env *env = make_env_lst(env1);

// 	t_arg	*arg;
// 	t_arg	*tmp;

// 	t_lst	*lst;
// 	t_lst	*tmp2;

// 	int j;
// 	int	i;

// 	i = 0;
// 	arg = (t_arg *)malloc(sizeof(t_arg));
// 	tmp = arg;

// 	lst = (t_lst *)malloc(sizeof(t_lst));
// 	tmp2 = lst;

// 	char **token = ft_split(str, ' ');
	
// 	char **cmd = (char **)malloc(sizeof(char *) * 100);

// 	while (token[i])
// 	{
// 		if (ft_strncmp(token[i], "&&", 2) == 0)
// 		{
// 			tmp2->cmd = cmd;
// 			tmp2->next = (t_lst *)malloc(sizeof(t_lst));
// 			tmp2 = tmp2->next;
// 			cmd = (char **)malloc(sizeof(char *) * 100);

// 			tmp->lst = lst;
// 			tmp->env = env;
// 			tmp->condition = T_AND;
// 			tmp->next = (t_arg *)malloc(sizeof(t_arg));
// 			tmp = tmp->next;
// 			lst = (t_lst *)malloc(sizeof(t_lst));
// 			tmp2 = lst;
// 			i++;
// 		}
// 		else if (ft_strncmp(token[i], "||", 2) == 0)
// 		{
// 			tmp2->cmd = cmd;
// 			tmp2->next = (t_lst *)malloc(sizeof(t_lst));
// 			tmp2 = tmp2->next;
// 			cmd = (char **)malloc(sizeof(char *) * 100);
// 			tmp->lst = lst;
// 			tmp->env = env;
// 			tmp->condition = T_OR;
// 			tmp->next = (t_arg *)malloc(sizeof(t_arg));
// 			tmp = tmp->next;
// 			lst = (t_lst *)malloc(sizeof(t_lst));
// 			tmp2 = lst;
// 			i++;
// 		}
// 		else 
// 		{
// 			j = 0;
// 			while (token[i])
// 			{
// 				if (ft_strncmp(token[i], "||", 2) == 0 || ft_strncmp(token[i], "&&", 2) == 0)
// 					break ;
// 				else if (ft_strncmp(token[i], "|", 1) == 0)
// 				{
// 					cmd[j] = NULL;
// 					tmp2->cmd = cmd;
// 					tmp2->next = (t_lst *)malloc(sizeof(t_lst));
// 					tmp2 = tmp2->next;
// 					cmd = (char **)malloc(sizeof(char *) * 100);
// 					j = 0;
// 					i++;
// 					break ;
// 				}
// 				else
// 				{
// 					cmd[j] = ft_strdup(token[i]);
// 					j++;
// 					i++;
// 				}
// 			}
// 		}
// 	}
// 	cmd[j] = NULL;
// 	tmp2->cmd = cmd;
// 	tmp2->next = NULL;
// 	tmp->lst = lst;
// 	tmp->env = env;
// 	tmp->condition = 0;
// 	tmp->next = NULL;

// 	return (arg);
// }
