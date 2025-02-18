/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:05:53 by nveneros          #+#    #+#             */
/*   Updated: 2025/02/18 16:40:37 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

t_list	**init_operators(char **split, int i_start, int i_end)
{
	t_list	**operators;
	int	counter;

	counter = 0;
	operators = malloc(sizeof (t_list *));
	if (operators == NULL)
		return (NULL);
	while (split[i_start] && split && i_start < i_end)
	{
		if (ft_strcmp(split[i_start], ">>") == 0 || ft_strcmp(split[i_start], "<<") == 0 
			||ft_strcmp(split[i_start], ">") == 0 || ft_strcmp(split[i_start], "<") == 0)
		{
			if (counter == 0)
				*operators = ft_lstnew(init_key_val(split[i_start], split[i_start + 1]));
			else
				ft_lstadd_back(operators, ft_lstnew(init_key_val(split[i_start], split[i_start + 1])));
			i_start += 2;
			counter++;
		}
		else
			i_start++;
	}
	return (operators);
}
