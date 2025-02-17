/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:38:34 by nveneros          #+#    #+#             */
/*   Updated: 2025/02/17 17:31:12 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_quote(char **split, int split_index, char *str, int i_start)
{
	int		i_end;

	i_end = i_start;
	if (ft_strlen(str) - i_start >= 2)
	{
		while (str[i_end] == SINGLE_QUOTE || str[i_end] == DOUBLE_QUOTE || (str[i_end] != ' ' && !is_single_operator(str, i_end) && str[i_end]))
		{
			if (str[i_end] == SINGLE_QUOTE)
			{
				i_end++;
				while (str[i_end] != SINGLE_QUOTE)
					i_end++;
			}
			else if (str[i_end] == DOUBLE_QUOTE)
			{
				i_end++;
				while (str[i_end] != DOUBLE_QUOTE)
					i_end++;
			}
			i_end++;
		}
		split[split_index] = ft_substr(str, i_start, i_end - i_start);
		return (i_end - i_start);
	}
	return (0);
}

int	count_quote(char *str, int i_start)
{
	int		i_end;

	i_end = i_start;
	if (ft_strlen(str) - i_start >= 2)
	{
		while (str[i_end] == SINGLE_QUOTE || str[i_end] == DOUBLE_QUOTE || (str[i_end] != ' ' && !is_single_operator(str, i_end) && str[i_end]))
		{
			if (str[i_end] == SINGLE_QUOTE)
			{
				i_end++;
				while (str[i_end] != SINGLE_QUOTE)
					i_end++;
			}
			else if (str[i_end] == DOUBLE_QUOTE)
			{
				i_end++;
				while (str[i_end] != DOUBLE_QUOTE)
					i_end++;
			}
			i_end++;
		}
		return (i_end - i_start);
	}
	return (0);
}
