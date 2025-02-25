#include "minishell.h"

int	len_split(char **split)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
		i++;
	return (i);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	print_split(char **split)
{
	int	i;
	int	len;

	i = 0;
	len = len_split(split);
	while (i < len)
	{
		ft_printf("split[%d]: %s\n", i, split[i]);
		i++;
	}
}
