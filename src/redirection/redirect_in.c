/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:09:38 by nveneros          #+#    #+#             */
/*   Updated: 2025/03/04 17:41:10 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_in(t_key_val *content, t_bool is_last)
{
	int	fd;

	fd = open(content->value, O_RDONLY);
	if (fd < 0)
	{
		exit_status(1, TRUE);
		perror(content->value);
		return (1);
	}
	if (is_last)
		dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	handle_here_doc(t_key_val *content, t_bool is_last)
{
	int			status;

	status = redirect_in(content, is_last);
	unlink(content->value);
	return (status);
}
