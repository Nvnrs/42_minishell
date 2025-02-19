/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:51:16 by nveneros          #+#    #+#             */
/*   Updated: 2025/02/19 16:51:27 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_operator(t_key_val *operator)
{
	printf("%s %s\n", operator->key, operator->value);
}

void	print_list_operators(t_list **operators)
{
	t_list	*lst;
	int		i;

	lst = *operators;
	i = 0;
	while (lst)
	{
		printf("~~~[%d] :", i);
		print_operator(lst->content);
		lst = lst->next;
		i++;
	}
}