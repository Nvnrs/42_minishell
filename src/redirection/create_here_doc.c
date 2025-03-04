/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_here_doc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 17:30:53 by nveneros          #+#    #+#             */
/*   Updated: 2025/03/04 17:40:14 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	create_and_assign_temp_file(t_key_val *operator_content, t_list **env)
{
	static int	id_here_doc;
	char		*name;
	char		*delimiter;

	name = create_name_here_doc(&id_here_doc);
	delimiter = ft_strdup(operator_content->value);
	write_to_here_doc(name, delimiter, env);
	free(delimiter);
	free(operator_content->value);
	operator_content->value = name;
}

void	create_all_here_doc(t_list **lst_cmd, t_list **env)
{
	t_list		*cmd;
	t_cmd		*cmd_content;
	t_list		**lst_operators;
	t_list		*operator;
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
}
