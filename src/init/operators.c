/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:05:53 by nveneros          #+#    #+#             */
/*   Updated: 2025/02/26 13:30:56 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_list	**init_operators_in(char **split, int i_start, int i_end)
// {
// 	t_list	**operators_in;
// 	int		counter;

// 	counter = 0;
// 	operators_in = NULL;
// 	operators_in = malloc(sizeof (t_list *));
// 	if (operators_in == NULL)
// 		return (NULL);
// 	*operators_in = NULL;
// 	while (split[i_start] && split && i_start <= i_end)
// 	{
// 		if (ft_strcmp(split[i_start], "<<") == 0 || ft_strcmp(split[i_start], "<") == 0)
// 		{
// 			if (counter == 0)
// 				*operators_in = ft_lstnew(init_key_val(split[i_start], split[i_start + 1]));
// 			else
// 				ft_lstadd_back(operators_in, ft_lstnew(init_key_val(split[i_start], split[i_start + 1])));
// 			i_start += 2;
// 			counter++;
// 		}
// 		else
// 			i_start++;
// 	}
// 	return (operators_in);
// }

// t_list	**init_operators_out(char **split, int i_start, int i_end)
// {
// 	t_list	**operators_out;
// 	int		counter;

// 	counter = 0;
// 	operators_out = NULL;
// 	operators_out = malloc(sizeof (t_list *));
// 	if (operators_out == NULL)
// 		return (NULL);
// 	*operators_out = NULL;
// 	while (split[i_start] && split && i_start <= i_end)
// 	{
// 		if (ft_strcmp(split[i_start], ">>") == 0 ||ft_strcmp(split[i_start], ">") == 0)
// 		{
// 			if (counter == 0)
// 				*operators_out = ft_lstnew(init_key_val(split[i_start], split[i_start + 1]));
// 			else
// 				ft_lstadd_back(operators_out, ft_lstnew(init_key_val(split[i_start], split[i_start + 1])));
// 			i_start += 2;
// 			counter++;
// 		}
// 		else
// 			i_start++;
// 	}
// 	return (operators_out);
// }

t_list	**init_lst_operator(char **split, int i_start, int i_end)
{
	t_list	**lst_operator;

	lst_operator = NULL;
	lst_operator = malloc(sizeof (t_list *));
	if (lst_operator == NULL)
		return (NULL);
	*lst_operator = NULL;
	while (split[i_start] && split && i_start <= i_end)
	{
		if (ft_strcmp(split[i_start], ">>") == 0 ||ft_strcmp(split[i_start], ">") == 0
			|| ft_strcmp(split[i_start], "<<") == 0 ||ft_strcmp(split[i_start], "<") == 0)
		{
			if (*lst_operator == NULL)
				*lst_operator = ft_lstnew(init_key_val(split[i_start], split[i_start + 1]));
			else
				ft_lstadd_back(lst_operator, ft_lstnew(init_key_val(split[i_start], split[i_start + 1])));
			i_start += 2;
		}
		else
			i_start++;
	}
	return (lst_operator);
}
