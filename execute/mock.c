
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
	t_env *env = make_env_lst(env1);

	t_arg	*arg;
	t_arg	*tmp;

	t_lst	*lst;
	t_lst	*tmp2;

	int j;
	int	i;

	i = 0;
	arg = (t_arg *)malloc(sizeof(t_arg));
	tmp = arg;

	lst = (t_lst *)malloc(sizeof(t_lst));
	tmp2 = lst;

	char **token = ft_split(str, ' ');
	
	char **cmd = (char **)malloc(sizeof(char *) * 100);

	int arg_count = 0;
	while (token[i])
	{
		if (ft_strncmp(token[i], "&&", 2) == 0)
		{
			tmp->lst = lst;
			tmp->env = env;
			tmp->condition = T_AND;
			tmp->next = (t_arg *)malloc(sizeof(t_arg));
			tmp = tmp->next;
			lst = (t_lst *)malloc(sizeof(t_lst));
			tmp2 = lst;
			i++;
		}
		else if (ft_strncmp(token[i], "||", 2) == 0)
		{
			tmp->lst = lst;
			tmp->env = env;
			tmp->condition = T_OR;
			tmp->next = (t_arg *)malloc(sizeof(t_arg));
			tmp = tmp->next;
			lst = (t_lst *)malloc(sizeof(t_lst));
			tmp2 = lst;
			i++;
		}
		else 
		{
			j = 0;
			while (token[i])
			{
				if (ft_strncmp(token[i], "||", 2) == 0 || ft_strncmp(token[i], "&&", 2) == 0)
					break ;
				else if (ft_strncmp(token[i], "|", 1))
				{
					cmd[j] = NULL;
					tmp2->cmd = cmd;
					tmp2->next = (t_lst *)malloc(sizeof(t_lst));
					tmp2 = tmp2->next;
					char **cmd = (char **)malloc(sizeof(char *) * 100);
					i++;
					break ;
				}
				else
				{
					cmd[j] = ft_strdup(token[i]);
					j++;
					i++;
				}
			}
		}

	}
	cmd[j] = NULL;
	tmp2->cmd = cmd;
	tmp2->next = NULL;
	tmp->lst = lst;
	tmp->env = env;
	tmp->condition = 0;
	tmp->next = NULL;

	return (arg);
}
