/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:57:08 by nveneros          #+#    #+#             */
/*   Updated: 2025/02/25 15:08:35 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_pipe_in(t_key_val *content, t_bool is_last)
{
	int	fd;

	if (is_last)
	{
		fd = atoi(content->value);
		dup2(fd, STDIN_FILENO);
	}
	return (0);
}

int	redirect_pipe_out(t_key_val *content, t_bool is_last)
{
	int	fd;

	if (is_last)
	{	
		fd = atoi(content->value);
		dup2(fd, STDOUT_FILENO);
	}
	return (0);
}