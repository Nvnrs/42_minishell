/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:10:56 by nveneros          #+#    #+#             */
/*   Updated: 2025/02/18 16:51:22 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	char	*rd;
	int		flag;
	char	**split;
	t_list	**env;

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
			split = parse_input(rd);
			// print_split(split);
			init_lst_cmd(split);
			free_split(split);
		}
		else if (rd == NULL)
			flag = 0;
		free(rd);
	}
	rl_clear_history();
	free_list_env(env);
	return (0);
}
