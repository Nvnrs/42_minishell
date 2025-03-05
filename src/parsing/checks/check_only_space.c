/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_only_space.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 11:57:04 by nveneros          #+#    #+#             */
/*   Updated: 2025/03/05 14:44:16 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	str_contan_only_space(char *str)
{
	int	i;
	int	space;
	int	others;

	i = 0;
	space = 0;
	others = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			space++;
		else
			others++;
		i++;
	}
	if (others == 0)
		return (TRUE);
	return (FALSE);
}
