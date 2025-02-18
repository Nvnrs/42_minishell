/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:53:02 by nveneros          #+#    #+#             */
/*   Updated: 2025/02/18 17:19:51 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//   * char *name
//   * char **parameters_execve
//   * t_list operators_in
//   * t_list operators_out
//   * int pipes[2][2]


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

t_cmd	*init_cmd(char **input, int start, int end)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	// cmd->name = ;
	// cmd->n = ft_strdup(input[start]);
	return (cmd);
}

t_list	**init_lst_cmd(char **input)
{
	t_list	**lst_cmd;
	int		i;
	int		start;
	int		end;

	i = 0;
	start = 0;
	end = 0;
	lst_cmd = malloc(sizeof(t_list *));
	while (input[i])
	{
		if (ft_strcmp(input[i], "|") == 0 ||  i == (len_split(input) - 1))
		{
			if (i == (len_split(input) - 1))
				end = i;
			else
				end = i - 1;
			// get cmd
			// get operators
			print_start_end(input, start, end);
			start = i + 1;
		}
		i++;
	}
	return (lst_cmd);
}
