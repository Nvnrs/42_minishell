/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:52:28 by nveneros          #+#    #+#             */
/*   Updated: 2025/03/11 10:55:45 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// return nb_quotes : open/close -> 2 | only open 1 
int	skip_inside_quote(char quote, char *str, int *i)
{
	t_bool	quote_open;
	t_bool	quote_close;	

	*i += 1;
	quote_open = TRUE;
	quote_close = FALSE;
	while (str[*i] && str[*i] != quote)
	{
		*i += 1;
	}
	if (str[*i] == quote)
	{
		quote_close = TRUE;
		*i += 1;
	}
	if (quote_open && quote_close)
		return (2);
	return (1);
}

t_bool	nb_quotes_is_even(char quote, char other_quote, char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == other_quote)
			skip_inside_quote(other_quote, str, &i);
		else if (str[i] == quote)
		{
			count += skip_inside_quote(quote, str, &i);
		}
		else
			i++;
	}
	return (count % 2 == 0);
}

t_bool	quotes_are_valid(char *str)
{
	if (!nb_quotes_is_even(SINGLE_QUOTE, DOUBLE_QUOTE, str))
		return (FALSE);
	if (!nb_quotes_is_even(DOUBLE_QUOTE, SINGLE_QUOTE, str))
		return (FALSE);
	return (TRUE);
}
