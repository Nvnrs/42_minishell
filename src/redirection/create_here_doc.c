/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_here_doc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 17:30:53 by nveneros          #+#    #+#             */
/*   Updated: 2025/03/06 14:45:30 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	received_signal;

static void	free_data(t_data *data, char *line, char *delimiter)
{
	close_and_free_pipes(data->pipes, ft_lstsize(*data->lst_cmd) - 1);
	free_lst_cmd(data->lst_cmd);
	free_list_env(data->env);
	if (line)
		free(line);
	free(delimiter);
}

void	write_to_here_doc(char *filename, char	*delimiter, t_list **env, t_data *data)
{
	char	*line;
	int		here_docfd;
	int		pid;

	block_sigint();
	pid = fork();
	if (pid == 0)
	{
		set_sigint_handle_here_doc();
		here_docfd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (here_docfd == -1)
		{
			free_data(data, NULL, delimiter);
			exit(exit_status(1, TRUE));
		}
		line = readline("> ");
		while (line != NULL && strcmp(line, delimiter) != 0 && received_signal == 0)
		{
			line = expansion_str(line, env);
			line = cft_strcat_realloc(line, "\n");
			if (write(here_docfd, line, ft_strlen(line)) == -1)
			{
				close(here_docfd);
				free_data(data, line, delimiter);
				exit(exit_status(1, TRUE));// return (2);
			}
			free(line);
			if (received_signal == 0)
				line = readline("> ");
		}
		close(here_docfd);
		free_data(data, line, delimiter);
		if (received_signal == 0)
			exit(exit_status(0, TRUE));
		else
			exit(exit_status(0, FALSE));
	}
	else
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
}

void	create_and_assign_temp_file(t_key_val *operator_content, t_list **env, t_data *data)
{
	static int	id_here_doc;
	char		*name;
	char		*delimiter;

	name = create_name_here_doc(&id_here_doc);
	delimiter = ft_strdup(operator_content->value);
	free(operator_content->value);
	operator_content->value = name;
	write_to_here_doc(name, delimiter, env, data);
	free(delimiter);
}


void	del_here_doc(char *filename)
{
	int fd;

	fd = open(filename, O_RDONLY);
	if (fd != -1)
	{
		close(fd);
		unlink(filename);
	}
}

void	del_all_here_doc(t_list **lst_cmd)
{
	t_list		*cmd;
	t_cmd		*cmd_content;
	t_list		**lst_operators;
	t_list		*operator;
	t_key_val	*operator_content;

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
				del_here_doc(operator_content->value);
			operator = operator->next;
		}
		cmd = cmd->next;
	}
}
int	create_all_here_doc(t_list **lst_cmd, t_list **env, t_data *data)
{
	t_list		*cmd;
	t_cmd		*cmd_content;
	t_list		**lst_operators;
	t_list		*operator;
	t_key_val	*operator_content;

	// (void)env;
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
				create_and_assign_temp_file(operator_content, env, data);
				if (exit_status(0, FALSE) != 0)
				{
					del_all_here_doc(lst_cmd);
					return (exit_status(0, FALSE));
				}
			}
			operator = operator->next;
		}
		cmd = cmd->next;
	}
	return (0);
}
