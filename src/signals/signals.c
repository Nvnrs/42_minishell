/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:48:56 by nveneros          #+#    #+#             */
/*   Updated: 2025/03/11 14:48:15 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_received_signal = 0;

void	handle_sigint_child(int signum)
{
	printf("%d\n", signum);
	if (signum == SIGINT)
	{
		printf("child sigint\n");
		printf("\n");
		exit_status(130, TRUE);
	}
}

void	set_sigint_child(void)
{
	struct sigaction	sa;
	
	// reset_sigint();
	printf("HELLO SET_SIGINT\n");
	ft_bzero(&sa, sizeof (struct sigaction));
	sa.sa_handler = &handle_sigint_child;
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
}

void	set_sigint_handle(void)
{
	struct sigaction	sa;

	// reset_sigint();
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
