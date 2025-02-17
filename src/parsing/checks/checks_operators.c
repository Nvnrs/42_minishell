/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_operators.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:54:01 by nveneros          #+#    #+#             */
/*   Updated: 2025/02/17 17:28:54 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// list operators
// <
// >
// >>
// <<
// |

// ERROR : parse error near '<'


t_bool	is_start_of_operator(char *operator, char *str, int i_str)
{
	int	j;
	int	i;

	j = 0;
	i = i_str;
	while (str[i] && str[i] == operator[j])
	{
		i++;
		j++;
	}
	if ((int)ft_strlen(operator) == j)
		return (TRUE);
	return (FALSE);
}


t_bool	operators_are_valid(char *str)
{
	if (consecutives_operators(str))
		return (FALSE);
	else if (after_operators_is_empty(str))
		return (FALSE);
	return (TRUE);
}
