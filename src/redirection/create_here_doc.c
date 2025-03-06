/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_here_doc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 17:30:53 by nveneros          #+#    #+#             */
/*   Updated: 2025/03/06 17:43:08 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_and_assign_temp_file(t_key_val *operator_content,
	t_list **env, t_data *data)
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
	int	fd;

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

int	create_here_doc_for_one_cmd(t_list **lst_operators,
	t_list **env, t_data *data)
{
	t_list		*operator;
	t_key_val	*operator_content;

	operator = *lst_operators;
	while (operator)
	{
		operator_content = operator->content;
		if (strcmp(operator_content->key, "<<") == 0)
		{
			create_and_assign_temp_file(operator_content, env, data);
			if (exit_status(0, FALSE) != 0)
			{
				del_all_here_doc(data->lst_cmd);
				return (exit_status(0, FALSE));
			}
		}
		operator = operator->next;
	}
	return (exit_status(0, TRUE));
}

int	create_all_here_doc(t_list **lst_cmd, t_list **env, t_data *data)
{
	t_list		*cmd;
	t_cmd		*cmd_content;

	cmd = *lst_cmd;
	while (cmd)
	{
		cmd_content = cmd->content;
		if (create_here_doc_for_one_cmd(cmd_content->lst_operator,
				env, data) != 0)
			return (exit_status(0, FALSE));
		cmd = cmd->next;
	}
	return (0);
}
