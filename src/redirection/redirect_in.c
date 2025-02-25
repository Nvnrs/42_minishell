#include "minishell.h"

int	redirect_in(t_key_val *content, t_bool is_last)
{
	int fd;

	fd = open(content->value, O_RDONLY);
	if (fd < 0)
	{
		dprintf(2, "HYYYYYYYYY");
		perror(NULL);
		return (1);
	}
	if (is_last)
		dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

static int	write_to_here_doc(char * filename, char	*delimiter, t_list **env)
{
	char	*line;
	int		here_docfd;

	here_docfd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (here_docfd == -1)
		return (1);
	line = get_next_line(STDIN_FILENO);
	while (strcmp(line, delimiter) != 0)
	{
		line = expansion_str(line, env);
		if (write(here_docfd, line, ft_strlen(line)) == -1)
		{
			free(line);
			return (2);
		}
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	free(line);
	close(here_docfd);
	return (0);
}


static char *create_name_here_doc(int *id)
{
	char *name;
	char *id_str;

	id_str = ft_itoa(*id);
	name = ft_strdup(HERE_DOC_FILENAME);
	name = cft_strcat_realloc(name, id_str);
	name = cft_strcat_realloc(name, ".txt");
	free(id_str);
	if (access(name, R_OK | F_OK) != 0)
		*id += 1;
	return (name);
}

int	handle_here_doc(t_key_val *content, t_bool is_last, t_list **env)
{
	t_key_val	*here_doc;
	char		*name;
	static int 	id_here_doc;
	char		*delimiter;
	int			status;
	
	status = 0;
	name = create_name_here_doc(&id_here_doc);
	delimiter = ft_strdup(content->value);
	delimiter = cft_strcat_realloc(delimiter, "\n");
	here_doc = init_key_val("<", name);
	printf("here_doc name: %s\n", name);
	status = write_to_here_doc(here_doc->value, delimiter, env);
	if (status == 1)
		handle_here_doc(content, is_last, env);
	else if (status == 0 && is_last)
		status = redirect_in(here_doc, is_last);
	free_key_val(here_doc);
	free(name);
	free(delimiter);
	return (status);
}
