/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:50:45 by nveneros          #+#    #+#             */
/*   Updated: 2025/03/11 10:29:04 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_pair_of_quotes_in_str(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == SINGLE_QUOTE)
		{
			i++;
			while (str[i] && str[i] != SINGLE_QUOTE)
				i++;
			if (str[i] && str[i] == SINGLE_QUOTE)
			{
				count += 1;
				i++;
			}
		}
		else if (str[i] == DOUBLE_QUOTE)
		{
			i++;
			while (str[i] && str[i] != DOUBLE_QUOTE)
				i++;
			if (str[i] && str[i] == DOUBLE_QUOTE)
			{
				count += 1;
				i++;
			}
		}
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
		if (str[i_str])
			i_str++;
	}
	newstr[len_newstr - 1] = '\0';
	free(str);
	return (newstr);
}
