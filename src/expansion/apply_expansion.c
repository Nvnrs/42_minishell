/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:35:22 by nveneros          #+#    #+#             */
/*   Updated: 2025/03/10 14:19:41 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**rebuild_args_exec(int index_to_remove, char **args_exec)
{
	char	**new_args_exec;
	int		i_args_exec;
	int		i_new_args_exec;

	new_args_exec = NULL;
	new_args_exec = malloc((len_split(args_exec) - 1 + 1) * sizeof (char *));
	if (new_args_exec == NULL)
		return (NULL);
	i_args_exec = 0;
	i_new_args_exec = 0;
	while (args_exec[i_args_exec])
	{
		if (i_args_exec != index_to_remove)
		{
			new_args_exec[i_new_args_exec] = ft_strdup(args_exec[i_args_exec]);
			i_new_args_exec++;
		}
		i_args_exec++;
	}
	new_args_exec[i_new_args_exec] = NULL;
	free_split(args_exec);
	return (new_args_exec);	
}

static char	**apply_expansion_args_exec(char **args_exec, t_list **lst_env)
{
	int		i;
	char 	*arg_expansion;
	char	**new_args_exec;

	i = 0;
	new_args_exec = args_exec;
	while (new_args_exec[i])
	{
		arg_expansion = expansion_str(new_args_exec[i], lst_env);
		if (arg_expansion == NULL)
			new_args_exec = rebuild_args_exec(i, new_args_exec);
		else
		{
			new_args_exec[i] = arg_expansion;
			i++;
		}
	}
	return (new_args_exec);
}

static int	apply_expansion_operators(t_list **operators, t_list **lst_env)
{
	t_list		*lst;
	t_key_val	*content;
	char 		*expansion;

	lst = *operators;
	while (lst)
	{
		content = lst->content;
		if (ft_strcmp(content->key, "<<") != 0)
		{
			expansion = expansion_str(content->value, lst_env);
			if (expansion == NULL)
			{
				handle_error(1, content->value, ": ambigous redirect\n");
				free(content->value);
				content->value = NULL;
				return (get_exit_status());
			} 
			else
				content->value = expansion;
		}
		lst = lst->next;
	}
	return (0);
}

int	apply_expansion(t_list **lst_cmd, t_list **lst_env)
{
	t_list	*lst;
	t_cmd	*cmd;
	char	*expansion_name;

	lst = *lst_cmd;
	while (lst)
	{
		cmd = lst->content;
		if (cmd->name)
		{
			expansion_name = expansion_str(cmd->name, lst_env);
			if (expansion_name == NULL)
			{
				free(cmd->name);
				cmd->name = NULL;
			}
			else
				cmd->name = expansion_name;
			
		}
		cmd->args_exec = apply_expansion_args_exec(cmd->args_exec, lst_env);
		if (apply_expansion_operators(cmd->lst_operator, lst_env) != 0)
			return (get_exit_status());
		lst = lst->next;
	}
	return (0);
}
