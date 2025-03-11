/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_tmp_file_here_doc.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 17:43:11 by nveneros          #+#    #+#             */
/*   Updated: 2025/03/11 15:07:56 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_received_signal;

static void	free_data(t_data *data, char *line, char *delimiter)
{
	close_and_free_pipes(data->pipes, ft_lstsize(*data->lst_cmd) - 1);
	free_lst_cmd(data->lst_cmd);
	free_list_env(data->env);
	if (line)
		free(line);
	free(delimiter);
}

static void	handle_parent(int pid)
{
	int	wstatus;
	int	status_code;

	status_code = 0;
	waitpid(pid, &wstatus, 0);
	if (WIFEXITED(wstatus))
	{
		status_code = WEXITSTATUS(wstatus);
		exit_status(status_code, TRUE);
	}
	set_sigint_handle();
}

static void	handle_child(char *filename, char
	*delimiter, t_list **env, t_data *data)
{
	char	*line;
	char 	*expansion_line;
	int		here_docfd;

	set_sigint_handle_here_doc();
	here_docfd = open(filename, O_WRONLY | O_TRUNC);
	if (here_docfd == -1)
	{
		free_data(data, NULL, delimiter);
		exit(exit_status(1, TRUE));
	}
	line = readline("> ");
	while (line != NULL
		&& strcmp(line, delimiter) != 0 && g_received_signal == 0)
	{
		expansion_line = expansion_str(line, env);
		if (expansion_line == NULL)
		{
			free(line);
			line = ft_strdup("\n");
		}
		else
			line = cft_strcat_realloc(expansion_line, "\n");
		write(here_docfd, line, ft_strlen(line));
		free(line);
		if (g_received_signal == 0)
			line = readline("> ");
	}
	close(here_docfd);
	free_data(data, line, delimiter);
}

void	write_to_here_doc(char *filename, char
	*delimiter, t_list **env, t_data *data)
{
	int		pid;

	block_sigint();
	pid = fork();
	if (pid == 0)
	{
		handle_child(filename, delimiter, env, data);
		if (g_received_signal == 0)
			exit(exit_status(0, TRUE));
		else
			exit(exit_status(0, FALSE));
	}
	else
		handle_parent(pid);
}
