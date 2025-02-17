/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 17:11:16 by nveneros          #+#    #+#             */
/*   Updated: 2025/02/17 17:12:34 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	is_double_redirection(char *str, int index)
{
	if ((str[index] == '>' && str[index + 1] == '>')
		|| (str[index] == '<' && str[index + 1] == '<'))
		return (TRUE);
	return (FALSE);
}

t_bool	is_single_operator(char *str, int index)
{
	if (c_is_in_charset(str[index], "><|"))
		return (TRUE);
	return (FALSE);
}