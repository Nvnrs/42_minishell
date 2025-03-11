/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_arguments.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:53:07 by nveneros          #+#    #+#             */
/*   Updated: 2025/03/11 10:55:33 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_cmd_arguments(char **input, int i_start, int i_end)
{
	int	counter;

	counter = 0;
	while (input[i_start] && i_start <= i_end)
	{
		if (is_start_of_operator("<", input[i_start], 0)
			|| is_start_of_operator(">", input[i_start], 0))
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
	while (input[i_start] && i_start <= i_end)
	{
		if (is_start_of_operator("<", input[i_start], 0)
			|| is_start_of_operator(">", input[i_start], 0))
			i_start += 2;
		else
		{
			cmd_arguments[i_arguments] = ft_strdup(input[i_start]);
			i_start++;
			i_arguments++;
		}
	}
	cmd_arguments[number_of_arguments] = NULL;
	return (cmd_arguments);
}
