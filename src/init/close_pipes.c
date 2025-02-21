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
	close_all_pipes(pipes, nb_pipe);
	free_all_pipes(pipes, nb_pipe);
}

void	close_and_free_npipe(int **pipes, int nb_pipe, int n)
{
	close_npipe(pipes, nb_pipe, n);
	free_npipe(pipes, nb_pipe, n);
}
