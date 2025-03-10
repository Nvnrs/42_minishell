/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_consecutive_operators.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:53:56 by nveneros          #+#    #+#             */
/*   Updated: 2025/03/07 17:17:41 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_an_operator(char *str, int i)
{
	int	len_operator;

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
	int	skip;

	skip = 0;
	while (str[skip] && str[skip] == ' ')
		skip++;
	return (skip);
}

static int	skip_quotes(char *str, char quote)
{
	int	i;

	i = 0;
	if (str[i] == quote)
	{
		i++;
		while (str[i] && str[i] != quote)
		{
			i++;
		}
		if (str[i] == quote)
			i++;
	}
	return (i);
}

static t_bool	detect_consecutive_operators(char *str, int *i_main)
{
	int	i;

	i = *i_main;
	if (str[i] == '|')
	{
		i += 1;
		i += skip_spaces(&str[i]);
		if (str[i] == '|')
			return (TRUE);
	}
	else if (is_an_operator(str, i))
	{
		i += is_an_operator(str, i);
		i += skip_spaces(&str[i]);
		if (is_an_operator(str, i))
			return (TRUE);
	}
	else
		i++;
	*i_main = i;
	return (FALSE);
}

t_bool	consecutive_operators(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i += skip_quotes(&str[i], DOUBLE_QUOTE);
		i += skip_quotes(&str[i], SINGLE_QUOTE);
		if (detect_consecutive_operators(str, &i))
			return (TRUE);
	}
	return (FALSE);
}
