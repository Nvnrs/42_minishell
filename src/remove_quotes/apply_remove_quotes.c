/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_remove_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 17:12:53 by nveneros          #+#    #+#             */
/*   Updated: 2025/03/04 17:13:26 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	apply_remove_quotes_args_exec(char **args_exec)
{
	int	i;

	i = 0;
	while (args_exec[i])
	{
		args_exec[i] = remove_quotes_in_str(args_exec[i]);
		i++;
	}
}

static void	apply_remove_quotes_operators(t_list **operators)
{
	t_list		*lst;
	t_key_val	*content;

	lst = *operators;
	while (lst)
	{
		content = lst->content;
		content->value = remove_quotes_in_str(content->value);
		lst = lst->next;
	}
}

void	apply_remove_quotes(t_list **lst_cmd)
{
	t_list	*lst;
	t_cmd	*cmd;

	lst = *lst_cmd;
	while (lst)
	{
		cmd = lst->content;
		if (cmd->name)
			cmd->name = remove_quotes_in_str(cmd->name);
		apply_remove_quotes_args_exec(cmd->args_exec);
		apply_remove_quotes_operators(cmd->lst_operator);
		lst = lst->next;
	}
}
