/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:50:45 by nveneros          #+#    #+#             */
/*   Updated: 2025/03/11 11:27:52 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	count_in_quotes(char *str, char quote, int *i, int *count)
{
	*i += 1;
	while (str[*i] && str[*i] != quote)
		i++;
	if (str[*i] && str[*i] == quote)
	{
		*count += 1;
		*i += 1;
	}
}

int	count_pair_of_quotes_in_str(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == SINGLE_QUOTE)
			count_in_quotes(str, SINGLE_QUOTE, &i, &count);
		else if (str[i] == DOUBLE_QUOTE)
			count_in_quotes(str, DOUBLE_QUOTE, &i, &count);
		else
			i++;
	}
	return (count);
}

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

static void	move_if_not_end_of_str(char *str, int *i)
{
	if (str[*i])
		*i += 1;
}

char	*remove_quotes_in_str(char *str)
{
	char	*newstr;
	int		i_str;
	int		i_newstr;
	int		len_newstr;

	if (count_pair_of_quotes_in_str(str) == 0)
		return (str);
	len_newstr = ft_strlen(str) - count_pair_of_quotes_in_str(str) * 2 + 1;
	newstr = NULL;
	newstr = malloc(sizeof (char) * len_newstr);
	if (newstr == NULL)
		return (NULL);
	init_int_zero(&i_str, &i_newstr, NULL, NULL);
	while (str[i_str])
	{
		if (str[i_str] == SINGLE_QUOTE)
			single_quote_case(str, newstr, &i_str, &i_newstr);
		else if (str[i_str] == DOUBLE_QUOTE)
			double_quote_case(str, newstr, &i_str, &i_newstr);
		else if (str[i_str] != SINGLE_QUOTE && str[i_str] != DOUBLE_QUOTE)
			others_case(str, newstr, &i_str, &i_newstr);
		move_if_not_end_of_str(str, &i_str);
	}
	newstr[len_newstr - 1] = '\0';
	return (free(str), newstr);
}
