/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_no_quote.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:46:01 by nveneros          #+#    #+#             */
/*   Updated: 2025/03/05 14:34:40 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_no_quote(char **split, int split_index, char *str, int i_start)
{
	int	i_end;

	i_end = i_start;
	while (str[i_end] != ' '
		&& str[i_end] != '\0' && !is_single_operator(str, i_end))
		i_end++;
	split[split_index] = ft_substr(str, i_start, i_end - i_start);
	return (i_end - i_start);
}

int	count_no_quote(char *str, int i_start)
{
	int	i_end;

	i_end = i_start;
	while (str[i_end] != ' '
		&& str[i_end] != '\0' && !is_single_operator(str, i_end))
		i_end++;
	return (i_end - i_start);
}
