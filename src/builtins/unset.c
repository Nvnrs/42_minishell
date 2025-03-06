/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:49:14 by nveneros          #+#    #+#             */
/*   Updated: 2025/03/06 17:18:12 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			if (last != NULL)
			{
				last->next = curr->next;
				ft_lstdelone(curr, free_key_val);
				curr = last->next;
			}
			else
			{
				*env = curr->next;
				ft_lstdelone(curr, free_key_val);
			}
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
