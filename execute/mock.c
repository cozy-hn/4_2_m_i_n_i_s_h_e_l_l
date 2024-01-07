
#include "execute.h"

int	init_arg(t_arg *arg, char **env)
{
	get_path(arg, env);
	arg->env = env;
	return (0);
}

t_lst *mock_lst()
{
	t_lst  *lst;
	t_lst  *tmp;

	lst = malloc(sizeof(t_lst));
	lst->fd_in = -1;
	lst->fd_out = -1;
	lst->cmd = malloc(sizeof(char *) * 3);
	lst->cmd[0] = strdup("ls");
	lst->cmd[1] = strdup("-aRl");
	lst->cmd[2] = NULL;
	lst->prev_pipe = -1;
	lst->next = malloc(sizeof(t_lst));
	tmp = lst->next;
	tmp->fd_in = -1;
	tmp->fd_out = -1;
	tmp->cmd = malloc(sizeof(char *) * 3);
	tmp->cmd[0] = strdup("grep");
	tmp->cmd[1] = strdup("a");
	tmp->cmd[2] = NULL;
	tmp->prev_pipe = -1;
	tmp->next = malloc(sizeof(t_lst));
	// tmp = tmp->next;
	// tmp->fd_in = -1;
	// tmp->fd_out = -1;
	// tmp->cmd = malloc(sizeof(char *) * 3);
	// tmp->cmd[0] = strdup("wc");
	// tmp->cmd[1] = strdup("-l");
	// tmp->cmd[2] = NULL;
	// tmp->prev_pipe = -1;
	tmp->next = NULL;
	return (lst);
}
