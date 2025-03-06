/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 17:36:27 by nveneros          #+#    #+#             */
/*   Updated: 2025/03/06 17:36:31 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all_pipes(int **pipes, int nb_pipe)
{
	int	i;

	i = 0;
	while (i < nb_pipe)
	{
		free(pipes[i]);
		i++;
	}
	free(pipes);
}

void	free_npipe(int **pipes, int nb_pipe, int n)
{
	int	i;

	i = 0;
	while (i < nb_pipe && i <= n)
	{
		free(pipes[i]);
		i++;
	}
	free(pipes);
}
