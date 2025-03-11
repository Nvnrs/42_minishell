/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:03:25 by nveneros          #+#    #+#             */
/*   Updated: 2025/03/11 11:03:41 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Cherche la valeur associe a une cle en se basant sur la liste ENV
 * 
 * @param key cle pour laquelle on doit trouver la valeur
 * @param lst_env Liste des variables d'environnement
 * @return valeur de la variable ou NULl si inexistante
 */
char	*find_value_in_env(char *key, t_list **lst_env)
{
	t_list		*lst;
	t_key_val	*content;

	lst = *lst_env;
	while (lst)
	{
		content = lst->content;
		if (ft_strcmp(key, content->key) == 0)
		{
			return (ft_strdup(content->value));
		}
		lst = lst->next;
	}
	return (NULL);
}
