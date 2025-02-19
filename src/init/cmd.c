/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:53:02 by nveneros          #+#    #+#             */
/*   Updated: 2025/02/19 11:41:07 by nveneros         ###   ########.fr       */
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
	(void)input;
	(void)start;
	(void)end;
	// cmd->name = ;
	// cmd->n = ft_strdup(input[start]);
	return (cmd);
}

char	*get_cmd_name(char	**input, int i_start, int i_end)
{
	while (input[i_start] && i_start < i_end)
	{
		if (is_start_of_operator("<", input[i_start], 0) || is_start_of_operator(">", input[i_start], 0))
			i_start += 2;
		else
			break ;
	}
	return (ft_strdup(input[i_start]));
}

int		count_cmd_arguments(char **input, int i_start, int i_end)
{
	int	counter;

	counter = 0;
	while (input[i_start] && i_start < i_end)
	{
		if (is_start_of_operator("<", input[i_start], 0) || is_start_of_operator(">", input[i_start], 0))
			i_start += 2;
		else
		{
			counter++;
			i_start++;
		}
	}
	return (counter);
}

char	**get_cmd_arguments(char **input, int i_start, int i_end)
{
	char	**cmd_arguments;
	int		i_arguments;
	int		number_of_arguments;

	number_of_arguments = count_cmd_arguments(input, i_start, i_end);
	cmd_arguments = malloc(sizeof (char *) * (number_of_arguments + 1));
	if (cmd_arguments == NULL)
		return (NULL);
	i_arguments = 0;
	while (input[i_start] && i_start < i_end)
	{
		if (is_start_of_operator("<", input[i_start], 0) || is_start_of_operator(">", input[i_start], 0))
			i_start += 2;
		else
		{
			cmd_arguments[i_arguments] = input[i_start];
			i_start++;
			i_arguments++;
		}
	}
	printf("number of args: %d", number_of_arguments);
	cmd_arguments[number_of_arguments] = NULL;
	return (cmd_arguments);
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
