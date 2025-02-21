#include "minishell.h"

int	**init_pipes(int nb_pipe)
{
	int	**pipes;
	int	i;

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