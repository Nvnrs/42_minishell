/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:10:56 by nveneros          #+#    #+#             */
/*   Updated: 2025/02/27 13:48:20 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Gere l'input de l'utilisateur
 */
int	handle_readline(char *rd, t_list **env)
{
	char	**input;
	t_list	**lst_cmd;
	int		**pipes;

	add_history(rd);
	if (!basics_checks(rd))
	{
		free(rd);
		return (1);
	}
	input = parse_input(rd);
	pipes = init_pipes(2);
	lst_cmd = init_lst_cmd(input, pipes);
	free_split(input);
	apply_expansion(lst_cmd, env);
	ft_lstiter(*lst_cmd, print_cmd);
	//printf("pipes[0][0] = %d\npipes[0][1] = %d\npipes[1][0] = %d\npipes[1][1] = %d\n", pipes[0][0], pipes[0][1], pipes[1][0], pipes[1][1]);
	processing(lst_cmd, ft_lstsize(*lst_cmd), env, pipes);
	free_lst_cmd(lst_cmd);
	return (0);
}


int	main(int argc, char *argv[], char *envp[])
{
	char	*rd;
	int		flag;
	t_list	**env;

	(void)argc;
	(void)argv;
	env = init_list_env(envp);
	set_signals();
	flag = 1;
	while (flag)
	{
		rd = readline("> ");
		if (rd && *rd)
		{
			if (handle_readline(rd, env) == 1)
				continue ;
		}
		else if (rd == NULL)
			flag = 0;
		free(rd);
	}
	rl_clear_history();
	free_list_env(env);
	return (0);
}
