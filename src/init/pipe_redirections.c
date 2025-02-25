#include "minishell.h"

static void	redirect_first(t_cmd *cmd)
{
	char	*first_pipe_write;

	first_pipe_write = ft_itoa(cmd->pipes[0][1]);
	ft_lstadd_front(cmd->operators_out, ft_lstnew(init_key_val("pipe", first_pipe_write)));
	free(first_pipe_write);
}

static void	redirect_last(t_cmd *cmd, int index_cmd)
{
	char	*first_pipe_read;
	char	*second_pipe_read;

	if (index_cmd % 2 == 1)
	{
		first_pipe_read = ft_itoa(cmd->pipes[0][0]);
		ft_lstadd_front(cmd->operators_in, ft_lstnew(init_key_val("pipe", first_pipe_read)));
		free(first_pipe_read);
	}
	else if (index_cmd % 2 == 0)
	{
		second_pipe_read = ft_itoa(cmd->pipes[1][0]);
		ft_lstadd_front(cmd->operators_in, ft_lstnew(init_key_val("pipe", second_pipe_read)));
		free(second_pipe_read);
	}
}

static void	redirect_middle(t_cmd *cmd, int index_cmd)
{
	char	*first_pipe_read;
	char	*first_pipe_write;
	char	*second_pipe_read;
	char	*second_pipe_write;

	if (index_cmd % 2 == 1)
	{
		first_pipe_read = ft_itoa(cmd->pipes[0][0]);
		second_pipe_write = ft_itoa(cmd->pipes[1][1]);
		ft_lstadd_front(cmd->operators_in, ft_lstnew(init_key_val("pipe", first_pipe_read)));
		ft_lstadd_front(cmd->operators_out, ft_lstnew(init_key_val("pipe", second_pipe_write)));
		free(first_pipe_read);
		free(second_pipe_write);
	}
	else if (index_cmd % 2 == 0)
	{
		second_pipe_read = ft_itoa(cmd->pipes[1][0]);
		first_pipe_write = ft_itoa(cmd->pipes[0][1]);
		ft_lstadd_front(cmd->operators_in, ft_lstnew(init_key_val("pipe", second_pipe_read)));
		ft_lstadd_front(cmd->operators_out, ft_lstnew(init_key_val("pipe", first_pipe_write)));
		free(second_pipe_read);
		free(first_pipe_write);
	}
}

static void	add_pipe_redirect_on_node(t_cmd *cmd, int nb_cmd, int index_cmd)
{
	if (nb_cmd > 1 && index_cmd == 0)
		redirect_first(cmd);
	else if (nb_cmd > 1 && index_cmd > 0 && index_cmd < nb_cmd - 1)
		redirect_middle(cmd, index_cmd);
	else if (nb_cmd > 1 && index_cmd == nb_cmd - 1)
		redirect_last(cmd, index_cmd);
}

void	add_pipe_redirect(t_list **lst_cmd, int nb_cmd)
{
	t_list	*head;
	int		i;

	if (!lst_cmd || !*lst_cmd)
		return ;
	i = 0;
	head = *lst_cmd;
	while(head != NULL)
	{
		add_pipe_redirect_on_node(head->content, nb_cmd, i);
		i++;
		head = head->next;
	}
}
