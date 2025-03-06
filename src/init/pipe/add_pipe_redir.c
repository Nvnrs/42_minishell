/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_pipe_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 17:34:31 by nveneros          #+#    #+#             */
/*   Updated: 2025/03/06 17:37:07 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	redirect_first(t_cmd *cmd)
{
	int	first_pipe_write;

	first_pipe_write = cmd->pipes[0][1];
	cmd->pipefd_in = -1;
	cmd->pipefd_out = first_pipe_write;
}

static void	redirect_last(t_cmd *cmd, int nb_cmd)
{
	int	last_pipe_read;

	last_pipe_read = cmd->pipes[nb_cmd - 1][0];
	cmd->pipefd_in = last_pipe_read;
	cmd->pipefd_out = -1;
}

static void	redirect_middle(t_cmd *cmd, int index_cmd)
{
	int	previous_pipe_read;
	int	current_pipe_write;

	previous_pipe_read = cmd->pipes[index_cmd - 1][0];
	current_pipe_write = cmd->pipes[index_cmd][1];
	cmd->pipefd_in = previous_pipe_read;
	cmd->pipefd_out = current_pipe_write;
}

static void	add_pipe_redirect_on_node(t_cmd *cmd, int nb_cmd, int index_cmd)
{
	if (nb_cmd > 1 && index_cmd == 0)
		redirect_first(cmd);
	else if (nb_cmd > 1 && index_cmd > 0 && index_cmd < nb_cmd - 1)
		redirect_middle(cmd, index_cmd);
	else if (nb_cmd > 1 && index_cmd == nb_cmd - 1)
		redirect_last(cmd, index_cmd);
	else
	{
		cmd->pipefd_in = -1;
		cmd->pipefd_out = -1;
	}
}

void	add_pipe_redirect(t_list **lst_cmd, int nb_cmd)
{
	t_list	*head;
	int		i;

	if (!lst_cmd || !*lst_cmd)
		return ;
	i = 0;
	head = *lst_cmd;
	while (head != NULL)
	{
		add_pipe_redirect_on_node(head->content, nb_cmd, i);
		i++;
		head = head->next;
	}
}
