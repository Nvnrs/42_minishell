/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 17:11:13 by nveneros          #+#    #+#             */
/*   Updated: 2025/03/05 14:43:30 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	count_case(int *count, int *i, char *str)
{
	if (str[*i] == SINGLE_QUOTE || str[*i] == DOUBLE_QUOTE)
	{
		*count += 1;
		*i += count_quote(str, *i);
	}
	else if (is_double_redirection(str, *i))
	{
		*count += 1;
		*i += 2;
	}
	else if (is_single_operator(str, *i))
	{
		*count += 1;
		*i += 1;
	}
	else if (str[*i] != ' ')
	{
		*count += 1;
		*i += count_no_quote(str, *i);
	}
	else
		*i += 1;
}

int	count_word_in_input(char *str)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (str[i])
		count_case(&count, &i, str);
	return (count);
}

static void	parse_case(char **split, int *i_split, char *str, int *i)
{
	if (str[*i] == SINGLE_QUOTE || str[*i] == DOUBLE_QUOTE)
	{
		*i += handle_quote(split, *i_split, str, *i);
		*i_split += 1;
	}
	else if (is_double_redirection(str, *i))// << >>
	{
		split[*i_split] = ft_substr(str, *i, 2);
		*i += 2;
		*i_split += 1;
	}
	else if (is_single_operator(str, *i))// < > 
	{
		split[*i_split] = ft_substr(str, *i, 1);
		*i += 1;
		*i_split += 1;
	}
	else if (str[*i] != ' ')
	{
		*i += handle_no_quote(split, *i_split, str, *i);
		*i_split += 1;
	}
	else
		*i += 1;
}

char	**parse_input(char *str)
{
	char	**split;
	int		i_split;
	int		i;

	i = 0;
	i_split = 0;
	split = malloc((count_word_in_input(str) + 1) * sizeof (char *));
	while (str[i])
		parse_case(split, &i_split, str, &i);
	split[count_word_in_input(str)] = NULL;
	return (split);
}
