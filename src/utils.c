/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:44:18 by nveneros          #+#    #+#             */
/*   Updated: 2025/03/04 11:48:37 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_int_zero(int *first, int *second, int *third, int *fourth)
{
	if (first != NULL)
		*first = 0;
	if (second != NULL)
		*second = 0;
	if (third != NULL)
		*third = 0;
	if (fourth != NULL)
		*fourth = 0;
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

void	force_print_stderr(char *message)
{
	write(2, message, ft_strlen(message));
}
