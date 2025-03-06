/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 17:19:35 by nveneros          #+#    #+#             */
/*   Updated: 2025/03/06 17:19:56 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_status(int new_status_code, t_bool update)
{
	static int	status_code;

	if (update)
		status_code = new_status_code;
	return (status_code);
}

char	*get_exit_status_str(void)
{
	char	*exit_status_str;

	exit_status_str = ft_itoa(exit_status(0, FALSE));
	return (exit_status_str);
}

int	get_exit_status(void)
{
	return (exit_status(0, FALSE));
}

int	handle_error(int status_code, char *context, char *message)
{
	force_print_stderr(context);
	force_print_stderr(message);
	return (exit_status(status_code, TRUE));
}
