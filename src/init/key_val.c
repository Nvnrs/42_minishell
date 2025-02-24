/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_val.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchateau <pchateau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:47:32 by nveneros          #+#    #+#             */
/*   Updated: 2025/02/24 11:47:22 by pchateau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_key_val	*init_key_val(char *key, char *value)
{
	t_key_val	*key_val;

	key_val = malloc(sizeof (t_key_val));
	key_val->key = ft_strdup(key);
	key_val->value = ft_strdup(value);
	return (key_val);
}

void	free_key_val(void *key_val_void)
{
	t_key_val	*key_val;

	key_val = key_val_void;
	free(key_val->key);
	free(key_val->value);
	free(key_val);
}
