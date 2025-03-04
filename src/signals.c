/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:50:29 by nveneros          #+#    #+#             */
/*   Updated: 2025/03/04 17:06:45 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_sigint(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		exit_status(130, TRUE);
	}
}

static void	set_sigint_handle(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof (struct sigaction));
	sa.sa_handler = &handle_sigint;
	sa.sa_flags = SA_RESTART;
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
