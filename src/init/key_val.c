/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_val.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:47:32 by nveneros          #+#    #+#             */
/*   Updated: 2025/02/18 15:52:58 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_key_val	*init_key_val(char *key, char *value)
{
	t_key_val	*env_var;

	env_var = malloc(sizeof (t_key_val));
	env_var->key = ft_strdup(key);
	env_var->value = ft_strdup(value);
	return (env_var);
}

void	free_key_val(void *env_var_void)
{
	t_key_val	*env_var;

	env_var = env_var_void;
	free(env_var->key);
	free(env_var->value);
	free(env_var);
}
