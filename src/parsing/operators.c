/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:51:11 by nveneros          #+#    #+#             */
/*   Updated: 2025/02/17 14:09:51 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/MYLIB42/mylib42.h"

// list operators
// <
// >
// >>
// <<
// |

// ERROR : parse error near '<'


// operator 

// detect operator
// 

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
	if (ft_strlen(operator) == j)
		return (TRUE);
	return (FALSE);
}

#include <stdio.h>

t_bool	is_only_space(char *str)
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

t_bool	has_empty_after_operator(char *operator, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (is_start_of_operator(operator, str, i))
		{
			// skip operator
			i+= ft_strlen(operator);
			printf("SKIP : %s\n", &str[i]);
			if (is_only_space(&str[i]))
			{
				printf("EMPTY AFTER");
				return (TRUE);
			}
			continue;
		}
		i++;
	}
	return (FALSE);
}

// Don't check for pipe because if empty after PIPE we need read STDIN
t_bool	after_operator_is_valid(char *str)
{
	if (has_empty_after_operator("<<", str))
		return (FALSE);
	if (has_empty_after_operator(">>", str))
		return (FALSE);
	if (has_empty_after_operator("<", str))
		return (FALSE);
	if (has_empty_after_operator(">", str))
		return (FALSE);
	return (TRUE);
}
// t_bool	operator_after_operator(char *operator)
// {
	
// }

// t_bool	consecutives_operators(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (is_start_of_operator("<<"))
// 		{
			
// 		}
// 		i++;
// 	}
	
// }

int main()
{
	after_operator_is_valid("< salut < salut je test >                 ");
	return (0);
}