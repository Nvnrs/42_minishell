#include "minishell.h"

static void	redirect_first(t_cmd *cmd)
{
	ft_lstadd_front(cmd->operators_out, ft_lstnew(init_key_val("base", ft_itoa(cmd->pipes[0][1]))));
}

static void	redirect_last(t_cmd *cmd, int index_cmd)
{
	if (index_cmd % 2 == 1)
		ft_lstadd_front(cmd->operators_in, ft_lstnew(init_key_val("base", ft_itoa(cmd->pipes[0][0]))));
	else if (index_cmd % 2 == 0)
		ft_lstadd_front(cmd->operators_in, ft_lstnew(init_key_val("base", ft_itoa(cmd->pipes[1][0]))));
}

static void	redirect_middle(t_cmd *cmd, int index_cmd)
{
	if (index_cmd % 2 == 1)
	{
		ft_lstadd_front(cmd->operators_in, ft_lstnew(init_key_val("base", ft_itoa(cmd->pipes[0][0]))));
		ft_lstadd_front(cmd->operators_out, ft_lstnew(init_key_val("base", ft_itoa(cmd->pipes[1][1]))));
	}
	else if (index_cmd % 2 == 0)
	{
		ft_lstadd_front(cmd->operators_in, ft_lstnew(init_key_val("base", ft_itoa(cmd->pipes[1][0]))));
		ft_lstadd_front(cmd->operators_out, ft_lstnew(init_key_val("base", ft_itoa(cmd->pipes[0][1]))));
	}
}

static void	apply_basic_redirect_on_node(t_cmd *cmd, int nb_cmd, int index_cmd)
{
	if (nb_cmd > 1 && index_cmd == 0)
		redirect_first(cmd);
	else if (nb_cmd > 1 && index_cmd > 0 && index_cmd < nb_cmd - 1)
		redirect_middle(cmd, index_cmd);
	else if (nb_cmd > 1 && index_cmd == nb_cmd - 1)
		redirect_last(cmd, index_cmd);
}

void	apply_basic_redirect(t_list **lst_cmd, int nb_cmd)
{
	t_list	*head;
	int		i;

	if (!lst_cmd || !*lst_cmd)
		return ;
	i = 0;
	head = *lst_cmd;
	while(head != NULL)
	{
		apply_basic_redirect_on_node(head->content, nb_cmd, i);
		i++;
		head = head->next;
	}
}
