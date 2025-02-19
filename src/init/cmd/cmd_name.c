/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_name.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:53:54 by nveneros          #+#    #+#             */
/*   Updated: 2025/02/19 16:54:12 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_cmd_name(char	**input, int i_start, int i_end)
{
	while (input[i_start] && i_start <= i_end)
	{
		if (is_start_of_operator("<", input[i_start], 0) || is_start_of_operator(">", input[i_start], 0))
			i_start += 2;
		else
		{
			if (input[i_start])
				return(ft_strdup(input[i_start]));
			else
				return (NULL);
		}
	}
	return (NULL);
}
