/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cases_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:27:20 by nveneros          #+#    #+#             */
/*   Updated: 2025/03/11 11:37:06 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	is_last_quote(char *str, int i, char quote)
{
	i++;
	while (str[i])
	{
		if (str[i] == quote)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

void	single_quote_case(char *str, char *newstr, int *i_str, int *i_newstr)
{
	if (is_last_quote(str, *i_str, SINGLE_QUOTE))
	{
		newstr[*i_newstr] = str[*i_str];
		*i_newstr += 1;
	}
	*i_str += 1;
	while (str[*i_str] && str[*i_str] != SINGLE_QUOTE)
	{
		newstr[*i_newstr] = str[*i_str];
		*i_str += 1;
		*i_newstr += 1;
	}
}

void	double_quote_case(char *str, char *newstr, int *i_str, int *i_newstr)
{
	if (is_last_quote(str, *i_str, DOUBLE_QUOTE))
	{
		newstr[*i_newstr] = str[*i_str];
		*i_newstr += 1;
	}
	*i_str += 1;
	while (str[*i_str] && str[*i_str] != DOUBLE_QUOTE)
	{
		newstr[*i_newstr] = str[*i_str];
		*i_str += 1;
		*i_newstr += 1;
	}
}

void	others_case(char *str, char *newstr, int *i_str, int *i_newstr)
{
	newstr[*i_newstr] = str[*i_str];
	*i_newstr += 1;
}
