/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:49:14 by nveneros          #+#    #+#             */
/*   Updated: 2025/03/11 11:16:38 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	key_is_in_env(t_list **curr, t_list *last, t_list **env)
{
	
	if (last != NULL)
	{
		last->next = (*curr)->next;
		ft_lstdelone(*curr, free_key_val);
		*curr = last->next;
	}
	else
	{
		*env = (*curr)->next;
		ft_lstdelone(*curr, free_key_val);
	}
}

/*UNSET */
void	remove_var(char *var_key, t_list **env)
{
	t_list		*curr;
	t_list		*last;
	t_key_val	*content_env;

	curr = *env;
	last = NULL;
	while (curr)
	{
		content_env = curr->content;
		if (ft_strcmp(content_env->key, var_key) == 0)
		{
			key_is_in_env(&curr, last, env);
			return ;
		}
		last = curr;
		curr = curr->next;
	}
}

void	builtin_unset(char **args, t_list **env)
{
	int	i;

	i = 0;
	while (args[i])
	{
		remove_var(args[i], env);
		i++;
	}
}
