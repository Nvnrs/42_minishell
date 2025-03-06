/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 17:36:24 by nveneros          #+#    #+#             */
/*   Updated: 2025/03/06 17:37:16 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipe(int pipes[2])
{
	close(pipes[0]);
	close(pipes[1]);
}

void	close_all_pipes(int **pipes, int nb_pipe)
{
	int	i;

	i = 0;
	while (i < nb_pipe)
	{
		close_pipe(pipes[i]);
		i++;
	}
}

void	close_npipe(int **pipes, int nb_pipe, int n)
{
	int	i;

	i = 0;
	while (i < nb_pipe && i <= n)
	{
		close_pipe(pipes[i]);
		i++;
	}
}

void	close_and_free_pipes(int **pipes, int nb_pipe)
{
	if (nb_pipe == 0)
		return ;
	close_all_pipes(pipes, nb_pipe);
	free_all_pipes(pipes, nb_pipe);
}

void	close_and_free_npipe(int **pipes, int nb_pipe, int n)
{
	close_npipe(pipes, nb_pipe, n);
	free_npipe(pipes, nb_pipe, n);
}
