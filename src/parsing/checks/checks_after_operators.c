/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_after_operators.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:55:21 by nveneros          #+#    #+#             */
/*   Updated: 2025/03/05 14:44:42 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	is_only_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

static t_bool	has_empty_after_operator(char *operator, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (is_start_of_operator(operator, str, i))
		{
			i += ft_strlen(operator);
			if (is_only_space(&str[i]))
			{
				return (TRUE);
			}
			continue ;
		}
		i++;
	}
	return (FALSE);
}

/* AFTER OPERATORS */

// Don't check for pipe because if empty after PIPE we need read STDIN
t_bool	after_operators_is_empty(char *str)
{
	if (has_empty_after_operator("<<", str))
		return (TRUE);
	if (has_empty_after_operator(">>", str))
		return (TRUE);
	if (has_empty_after_operator("<", str))
		return (TRUE);
	if (has_empty_after_operator(">", str))
		return (TRUE);
	if (has_empty_after_operator("|", str))
		return (TRUE);
	return (FALSE);
}
