/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:10:56 by nveneros          #+#    #+#             */
/*   Updated: 2025/02/18 11:27:02 by nveneros         ###   ########.fr       */
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
	print_list_env(env);
	free_list_env(env);
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
			print_split(split);
			free_split(split);
		}
		else if (rd == NULL)
			flag = 0;
		free(rd);
	}
	rl_clear_history();
	return (0);
}
