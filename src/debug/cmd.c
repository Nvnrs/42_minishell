/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:48:41 by nveneros          #+#    #+#             */
/*   Updated: 2025/03/06 17:19:01 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_start_end(char **tab, int start, int end)
{
	printf("start :%d\n", start);
	printf("end :%d\n", end);
	while (start <= end)
	{
		printf("%s", tab[start]);
		start++;
	}
	printf("\n");
}

void	print_args_of_cmd(char **args)
{
	int	i;

	i = 0;
	printf("args_exec :\n");
	while (args[i])
	{
		printf("~~~[%d] :%s\n", i, args[i]);
		i++;
	}
}

void	print_pid_tab(int *pid, int nb_cmd)
{
	int	i;

	i = 0;
	while (i < nb_cmd)
	{
		printf("pid[%d]:%d\n", i, pid[i]);
		i++;
	}
}

void	print_cmd(void *cmd_content)
{
	t_cmd		*cmd;
	static int	i;

	cmd = cmd_content;
	printf("\033[0;35m%d ------------------------------ %d\n\033[0;30m", i, i);
	printf("name :%s\n", cmd->name);
	print_args_of_cmd(cmd->args_exec);
	printf("operators_in && operator_out :\n");
	print_list_operators(cmd->lst_operator);
	printf("pipe_in :%d\n", cmd->pipefd_in);
	printf("pipe_out :%d\n", cmd->pipefd_out);
	printf("nb_pipes :%d\n", cmd->nb_pipes);
	if (cmd->pipes == NULL)
		printf("pipes :(NULL)\n");
	else
		printf("pipes :OK\n");
	printf("\033[0;37m");
	i++;
}
