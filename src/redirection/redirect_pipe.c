/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchateau <pchateau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:57:08 by nveneros          #+#    #+#             */
/*   Updated: 2025/02/25 09:21:55 by pchateau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_pipe_in(t_key_val *content, t_bool is_last)
{
	if (is_last)
		dup2(atoi(content->value), STDIN_FILENO);
	return (0);
}

int	redirect_pipe_out(t_key_val *content, t_bool is_last)
{
	if (is_last)
		dup2(atoi(content->value), STDOUT_FILENO);
	return (0);
}