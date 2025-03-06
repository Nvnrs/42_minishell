/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 13:18:56 by nveneros          #+#    #+#             */
/*   Updated: 2025/03/06 17:33:54 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**split_on_first_equal(char *str)
{
	char	**split;
	int		i;
	int		equal_index;

	split = malloc(sizeof (char *) * 3);
	if (split == NULL)
		return (NULL);
	i = 0;
	while (str[i] != '=' && str[i])
		i++;
	split[0] = ft_substr(str, 0, i);
	equal_index = i;
	i++;
	while (str[i])
		i++;
	split[1] = ft_substr(str, equal_index + 1, i - equal_index + 1);
	split[2] = NULL;
	return (split);
}

t_list	**init_list_env(char *envp[])
{
	t_list	**env;
	int		i;
	char	**split;

	i = 0;
	env = malloc(sizeof (t_list *));
	if (env == NULL)
		return (NULL);
	while (envp[i] && envp)
	{
		split = split_on_first_equal(envp[i]);
		if (i == 0)
			*env = ft_lstnew(init_key_val(split[0], split[1]));
		else
			ft_lstadd_back(env, ft_lstnew(init_key_val(split[0], split[1])));
		free_split(split);
		i++;
	}
	return (env);
}

void	free_list_env(t_list **env)
{
	ft_lstclear(env, free_key_val);
	free(env);
	env = NULL;
}
