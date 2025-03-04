/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:09:38 by nveneros          #+#    #+#             */
/*   Updated: 2025/03/04 16:25:29 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_in(t_key_val *content, t_bool is_last)
{
	int fd;

	fd = open(content->value, O_RDONLY);
	if (fd < 0)
	{
		exit_status(1, TRUE);
		perror(content->value);
		return (1);
	}
	if (is_last)
		dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	write_to_here_doc(char *filename, char	*delimiter, t_list **env)
{
	char	*line;
	int		here_docfd;

	here_docfd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (here_docfd == -1)
		return (1);
	line = readline("< ");
	while (strcmp(line, delimiter) != 0)
	{
		line = expansion_str(line, env);
		if (write(here_docfd, line, ft_strlen(line)) == -1)
		{
			free(line);
			return (2);
		}
		free(line);
		line = readline("> ");
	}
	free(line);
	close(here_docfd);
	return (0);
}


t_bool	create_file(char *filename)
{
	int fd;

	fd = open(filename, O_CREAT, 0644);
	if (fd == -1)
		return (FALSE);
	return (TRUE);
}

static char *create_name_here_doc(int *id)
{
	char *name;
	char *id_str;
	t_bool	file_is_create;

	name = NULL;
	file_is_create = FALSE;
	while (file_is_create == FALSE)
	{
		id_str = ft_itoa(*id);
		name = ft_strdup(HERE_DOC_FILENAME);
		name = cft_strcat_realloc(name, id_str);
		name = cft_strcat_realloc(name, ".txt");
		free(id_str);
		*id += 1;
		if (create_file(name))
			file_is_create = TRUE;
	}
	printf("name file :%s\n", name);
	return (name);
}

void	create_and_assign_temp_file(t_key_val *operator_content, t_list **env)
{
	static int	id_here_doc;
	char		*name;
	char	*delimiter;

	name = create_name_here_doc(&id_here_doc);
	delimiter = ft_strdup(operator_content->value);
	// delimiter = cft_strcat_realloc(delimiter, "\n");
	write_to_here_doc(name, delimiter, env);
	free(delimiter);
	free(operator_content->value);
	operator_content->value = name;
}

void	create_all_here_doc(t_list **lst_cmd, t_list **env)
{
	t_list	*cmd;
	t_cmd	*cmd_content;
	t_list	**lst_operators;
	t_list	*operator;
	t_key_val	*operator_content;

	(void)env;
	cmd = *lst_cmd;
	while (cmd)
	{
		cmd_content = cmd->content;
		lst_operators = cmd_content->lst_operator;
		operator = *lst_operators;
		while (operator)
		{
			operator_content = operator->content;
			if (strcmp(operator_content->key, "<<") == 0)
			{
				create_and_assign_temp_file(operator_content, env);
			}
			operator = operator->next;
		}
		cmd = cmd->next;
	}
	// ft_lstiter(*lst_cmd, print_cmd);
}

int	handle_here_doc(t_key_val *content, t_bool is_last)
{
	int			status;

	status = redirect_in(content, is_last);
	unlink(content->value);
	return (status);
}
