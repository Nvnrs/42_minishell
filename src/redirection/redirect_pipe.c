/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:57:08 by nveneros          #+#    #+#             */
/*   Updated: 2025/02/24 17:59:18 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_pipe(t_key_val *content, int *last)
{
	(void)last;
	// dup2(atoi(content->value), *last);
	// *last = atoi(content->value);
	return (0);
}