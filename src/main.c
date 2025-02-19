/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:10:56 by nveneros          #+#    #+#             */
/*   Updated: 2025/02/19 15:39:31 by nveneros         ###   ########.fr       */
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
			lst_cmd = init_lst_cmd(input);
			//print_cmd((*lst_cmd)->content);
			
			//ft_lstiter(*lst_cmd, print_cmd);
			// char *test = get_cmd_name(split, 0, len_split(split) - 1);
			// printf("%s", test);
			// free(test);
			// print_split(get_cmd_arguments(split, 0, len_split(split) - 1));
			// print_split(split);
			//init_lst_cmd(split);
			free_lst_cmd(lst_cmd);
			free_split(input);
		}
		else if (rd == NULL)
			flag = 0;
		free(rd);
	}
	rl_clear_history();
	free_list_env(env);
	return (0);
}
