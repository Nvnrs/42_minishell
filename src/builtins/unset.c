/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:49:14 by nveneros          #+#    #+#             */
/*   Updated: 2025/03/03 14:00:41 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "minishell.h"

/*UNSET */
void	remove_var(char *var_key, t_list **env)
{
	t_list *curr;
	t_list *last;
	t_key_val *content_env;

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
			return;
		}
		last = curr;
		curr = curr->next;
	}
}


void	builtin_unset(char **args, t_list **env)
{
	int	i;

	i = 0;
	// exit_status(0, TRUE);
	while (args[i])
	{
		remove_var(args[i], env);
		i++;
	}
}

// cc -g  src/builtins/unset.c  src/init/key_val.c src/utils.c ./src/debug/env.c ./lib/MYLIB42/mylib42.a src/split_utils.c src/init/env/* lib/MYLIB42/mylib42.a -Isrc/
// int	main()
// {
// 	t_list **env;
// 	t_list *lst1;
// 	t_list *lst2;
// 	char	**args;

// 	args = malloc(2 * sizeof(char *));
// 	args[0] = ft_strdup("PATH");
// 	args[1] = NULL;
// 	lst1 = ft_lstnew(init_key_val("PATH", "salut"));
// 	lst2 = ft_lstnew(init_key_val("PATH", "salut"));
// 	lst1->next = lst2;
	
// 	env = &lst1;
// 	builtin_unset(args, env);

// 	// print lst
// 	print_list_env(env);
// 	free_split(args);
// 	t_list *lst = *env;
// 	t_list *temp = NULL;
	
// 	while (lst)
// 	{
// 		temp = lst;
// 		lst = lst->next;
// 		free_key_val(temp->content);
// 		free(temp);
// 	}
// 	return 0;
// }