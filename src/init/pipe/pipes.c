/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 17:36:30 by nveneros          #+#    #+#             */
/*   Updated: 2025/03/06 17:36:52 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_pipes_in_lst_cmd(t_list **lst_cmd, int **pipes)
{
	t_list	*lst;
	t_cmd	*cmd;
	int		nb_pipes;

	lst = *lst_cmd;
	nb_pipes = ft_lstsize(lst) - 1;
	while (lst)
	{
		cmd = lst->content;
		cmd->pipes = pipes;
		cmd->nb_pipes = nb_pipes;
		lst = lst->next;
	}
}

int	**init_pipes(int nb_pipe)
{
	int	**pipes;
	int	i;

	if (nb_pipe < 1)
		return (NULL);
	pipes = malloc(sizeof (int *) * nb_pipe);
	if (pipes == NULL)
		return (NULL);
	i = 0;
	while (i < nb_pipe)
	{
		pipes[i] = malloc(sizeof (int) * 2);
		if (pipes[i] == NULL)
			free_npipe(pipes, nb_pipe, i - 1);
		if (pipe(pipes[i]) == -1)
			close_and_free_npipe(pipes, nb_pipe, i);
		i++;
	}
	return (pipes);
}
