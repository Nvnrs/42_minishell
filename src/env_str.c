/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_str.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 10:31:57 by nveneros          #+#    #+#             */
/*   Updated: 2025/02/18 13:12:48 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*create_str_key_val(t_key_val *env_var)
{
	char *str;

	str = ft_strdup(env_var->key);
	str = cft_strcat_realloc(str, "=");
	str = cft_strcat_realloc(str, env_var->value);
	return (str);
}

char	**lst_env_to_tab_str(t_list **lst_env)
{
	char	**tab_str;
	t_list	*lst;
	int		i;

	i = 0;
	lst =  *lst_env;
	tab_str = malloc((ft_lstsize(lst) + 1) * sizeof(char*));
	if (tab_str == NULL)
		return (NULL);
	while (lst)
	{
		tab_str[i] = create_str_key_val(lst->content);
		lst = lst->next;
		i++;
	}
	tab_str[i] = NULL;
	return (tab_str);
}


int	main(int argc, char **argv, char **envp)
{
	t_list	**head;
	char	**tab_str;

	head = init_list_env(envp);
	
	tab_str = lst_env_to_tab_str(head);
	free_list_env(head);
	print_split(tab_str);
	free_split(tab_str);
	// print_list_env(head);
	return (0);
}