/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_consecutive_operators.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:53:56 by nveneros          #+#    #+#             */
/*   Updated: 2025/02/25 11:47:41 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* CONSECUTIVES OPERATORS */

static int	is_an_operator(char *str, int i)
{	
	int len_operator;

	len_operator = 0;
	if (is_start_of_operator("<<", str, i)
		|| is_start_of_operator(">>", str, i))
	{
		len_operator = 2;
	}
	else if (is_start_of_operator(">", str, i)
		|| is_start_of_operator("<", str, i)
		|| is_start_of_operator("|", str, i))
	{
		len_operator = 1;
	}
	return (len_operator);
}
static int	skip_spaces(char *str)
{
	int skip;

	skip = 0;
	while (str[skip] && str[skip] == ' ')
		skip++;
	return (skip);
}

t_bool	consecutives_operators(char *str)
{
	int	i;
	int	len_operator;

	i = 0;
	while (str[i])
	{
		len_operator = is_an_operator(str, i);
		if (len_operator)
		{
			i += len_operator;
			i += skip_spaces(&str[i]);
			if (is_an_operator(str, i))
			{
				return (TRUE);
			}
		}
		i++;
	}
	return (FALSE);
}
