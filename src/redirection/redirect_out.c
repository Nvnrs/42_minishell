#include "minishell.h"

int	redirect_out(t_key_val *content, t_bool is_last)
{
	int fd;

	fd = open(content->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror(NULL);
		return (1);
	}
	if (is_last)
		dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	redirect_out_append(t_key_val *content, t_bool is_last)
{
	int fd;

	fd = open(content->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror(NULL);
		return (1);
	}
	if (is_last)
		dup2(fd, STDOUT_FILENO);
	close(fd);
	return (1);
}