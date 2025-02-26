/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_only_point.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 09:45:47 by nveneros          #+#    #+#             */
/*   Updated: 2025/02/26 10:08:10 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	str_contain_only_point(char *str)
{
	int	i;
	int	point;
	int	character;

	i = 0;
	character = 0;
	point = 0;
	while (str[i])
	{
		if (str[i] != ' ')
		{
			if (str[i] == '.')
				point++;
			else
				character++;
		}
		i++;
	}
	if (point == 1 && character == 0)
		return (TRUE);
	return (FALSE);
}

// int	main(void)
// {
// 	printf("%d", check_if_only_point("  .  ."));
// 	return (0); 
// }