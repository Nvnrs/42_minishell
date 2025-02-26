/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:35:22 by nveneros          #+#    #+#             */
/*   Updated: 2025/02/26 14:11:49 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	apply_expansion_args_exec(char **args_exec, t_list **lst_env)
{
	int i;

	i = 0;
	while (args_exec[i])
	{
		args_exec[i] = expansion_str(args_exec[i], lst_env);
		i++;
	}
}

static void	apply_expansion_operators(t_list **operators, t_list **lst_env)
{
	t_list	*lst;
	t_key_val *content;

	lst = *operators;
	while (lst)
	{
		content = lst->content;
		if (ft_strcmp(content->key, "<<") != 0)
		{
			content->value = expansion_str(content->value, lst_env);
		}
		lst = lst->next;
	}
		
}

/**
 * apply to
 * cmd
 * 	-> name
 * 	-> args_exec
 *  -> operators_in / out
 * 		-> value
 */
void	apply_expansion(t_list **lst_cmd, t_list **lst_env)
{
	t_list	*lst;
	t_cmd	*cmd;

	lst = *lst_cmd;

	while (lst)
	{
		cmd = lst->content;
		if (cmd->name)
			cmd->name = expansion_str(cmd->name, lst_env);
		apply_expansion_args_exec(cmd->args_exec, lst_env);
		apply_expansion_operators(cmd->lst_operator, lst_env);
		lst = lst->next;
	}
}

