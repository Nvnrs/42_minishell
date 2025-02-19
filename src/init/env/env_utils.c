/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 13:19:38 by nveneros          #+#    #+#             */
/*   Updated: 2025/02/19 10:46:48 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env_var(t_key_val *env_var)
{
	printf("%s=%s\n", env_var->key, env_var->value);
}

void	print_list_env(t_list **env)
{
	t_list	*lst;

	lst = *env;
	while (lst)
	{
		print_env_var(lst->content);
		lst = lst->next;
	}
}
