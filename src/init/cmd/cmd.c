/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:53:02 by nveneros          #+#    #+#             */
/*   Updated: 2025/03/03 10:03:44 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//   * char *name
//   * char **parameters_execve
//   * t_list operators_in
//   * t_list operators_out
//   * int pipes[2][2]



t_cmd	*init_cmd(char **input, int start, int end)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof (t_cmd));
	cmd->name = get_cmd_name(input, start, end);
	cmd->args_exec = get_cmd_arguments(input, start, end);
	cmd->lst_operator = init_lst_operator(input, start, end);
	cmd->pipefd_in = -1;
	cmd->pipefd_out = -1;
	cmd->pipes = NULL;
	cmd->nb_pipes = 0;
	cmd->saved_in = -1;
	cmd->saved_out = -1;
	return (cmd);
}

t_list	**init_lst_cmd(char **input)
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
				*lst_cmd =  ft_lstnew(init_cmd(input, start, end));
			else
				ft_lstadd_back(lst_cmd, ft_lstnew(init_cmd(input, start, end)));
			start = i + 1;
		}
		i++;
	}
	return (lst_cmd);
}

void	free_cmd(void *cmd_void)
{
	t_cmd	*cmd;

	cmd = cmd_void;
	free(cmd->name);
	free_split(cmd->args_exec);	
	if (cmd->lst_operator!= NULL)
	{
		if (*cmd->lst_operator != NULL)
	 		ft_lstclear(cmd->lst_operator, free_key_val);
	 	free(cmd->lst_operator);
	}
	free(cmd);
}

void	free_lst_cmd(t_list **lst_cmd)
{
	ft_lstclear(lst_cmd, free_cmd);
	free(lst_cmd);
	lst_cmd = NULL;
}
