/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:10:56 by nveneros          #+#    #+#             */
/*   Updated: 2025/02/21 18:23:36 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	char	*rd;
	int		flag;
	char	**input;
	t_list	**env;
	t_list	**lst_cmd;
	int		**pipes;

	(void)argc;
	(void)argv;
	env = init_list_env(envp);
	flag = 1;
	while (flag)
	{
		rd = readline("> ");
		if (rd && *rd)
		{
			add_history(rd);
			if (!basics_checks(rd))
			{
				free(rd);
				continue;
			}
			input = parse_input(rd);
			pipes = init_pipes(2);
			// printf("pipes[0][0] = %d\npipes[0][1] = %d\npipes[1][0] = %d\npipes[1][1] = %d\n", pipes[0][0], pipes[0][1], pipes[1][0], pipes[1][1]);
			lst_cmd = init_lst_cmd(input, pipes);
			ft_lstiter(*lst_cmd, print_cmd);
			free_lst_cmd(lst_cmd);
			free_split(input);
			close_and_free_pipes(pipes, 2);
		}
		else if (rd == NULL)
			flag = 0;
		free(rd);
	}
	rl_clear_history();
	free_list_env(env);
	return (0);
}
