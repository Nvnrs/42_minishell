/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:48:56 by nveneros          #+#    #+#             */
/*   Updated: 2025/03/11 15:14:59 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_received_signal = 0;

void	set_sigint_handle(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof (struct sigaction));
	sa.sa_handler = &handle_sigint;
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
}

static void	ignore_signal_but_sigint(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof (struct sigaction));
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGTSTP, &sa, NULL);
}

void	set_signals(void)
{
	ignore_signal_but_sigint();
	set_sigint_handle();
}
