/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_out.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:09:35 by nveneros          #+#    #+#             */
/*   Updated: 2025/02/26 16:41:33 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_out(t_key_val *content, t_bool is_last)
{
	int fd;

	fd = open(content->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		exit_status(1, TRUE);
		perror(content->value);
		return (1);
	}
	if (is_last)
		dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	redirect_out_append(t_key_val *content, t_bool is_last)
{
	int fd;

	fd = open(content->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		exit_status(1, TRUE);
		perror(content->value);
		return (1);
	}
	if (is_last)
		dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}
