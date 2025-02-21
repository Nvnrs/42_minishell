/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:53:02 by nveneros          #+#    #+#             */
/*   Updated: 2025/02/21 18:24:37 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//   * char *name
//   * char **parameters_execve
//   * t_list operators_in
//   * t_list operators_out
//   * int pipes[2][2]

t_cmd	*init_cmd(char **input, int start, int end, int **pipes)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof (t_cmd));
	cmd->name = get_cmd_name(input, start, end);
	cmd->args_exec = get_cmd_arguments(input, start, end);
	cmd->operators_in = init_operators_in(input, start, end);
	cmd->operators_out = init_operators_out(input, start, end);
	cmd->pipes = pipes;
	return (cmd);
}

t_list	**init_lst_cmd(char **input, int **pipes)
{
	t_list	**lst_cmd;
	int		i;
	int		start;
	int		end;

	init_int_zero(&i, &start, &end, NULL);
	lst_cmd = malloc(sizeof(t_list *));
	*lst_cmd = NULL;
	while (input[i] && input)
	{
		if (ft_strcmp(input[i], "|") == 0 ||  i == (len_split(input) - 1))
		{
			end = i - 1;
			if (i == (len_split(input) - 1))
				end = i;
			if (*lst_cmd == NULL)
				*lst_cmd =  ft_lstnew(init_cmd(input, start, end, pipes));
			else
				ft_lstadd_back(lst_cmd, ft_lstnew(init_cmd(input, start, end, pipes)));
			start = i + 1;
		}
		i++;
	}
	add_basic_redirect(lst_cmd, ft_lstsize(*lst_cmd));
	return (lst_cmd);
}

void	free_cmd(void *cmd_void)
{
	t_cmd	*cmd;

	cmd = cmd_void;
	free(cmd->name);
	free_split(cmd->args_exec);	
	if (cmd->operators_in != NULL)
	{
		if (*cmd->operators_in != NULL)
			ft_lstclear(cmd->operators_in, free_key_val);
		free(cmd->operators_in);
	}
	if (cmd->operators_out != NULL)
	{
		if (*cmd->operators_out != NULL)
			ft_lstclear(cmd->operators_out, free_key_val);
		free(cmd->operators_out);
	}
	free(cmd);
}

void	free_lst_cmd(t_list **lst_cmd)
{
	ft_lstclear(lst_cmd, free_cmd);
	free(lst_cmd);
	lst_cmd = NULL;
}
