
#include "execute.h"
#include "../minishell.h"

int	init_arg(t_arg *arg, char **env)
{
	get_path(arg);
	return (0);
}

t_lst *mock_lst(char *str)
{
	t_lst *lst = (t_lst *)malloc(sizeof(t_lst));
	t_lst *tmp = lst;
	char **line = ft_split(str, '|');

	int i = 0;
	while (line[i])
	{
		char **cmd = ft_split(line[i], ' ');
		tmp->cmd = cmd;
		tmp->fd_in = -1;
		tmp->fd_out = -1;
		tmp->prev_pipe = -1;
		if (line[i + 1] == NULL)
		{
			tmp->next = NULL;
			break ;
		}
		tmp->next = (t_lst *)malloc(sizeof(t_lst));
		tmp = tmp->next;
		i++;
	}
	return (lst);
}
