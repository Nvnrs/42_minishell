/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:50:29 by nveneros          #+#    #+#             */
/*   Updated: 2025/03/06 14:22:33 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	received_signal = 0;

static void	reset_sigint(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof (struct sigaction));
	sa.sa_handler = SIG_DFL;
	sigaction(SIGINT, &sa, NULL);
}

static void	handle_sigint_here_doc(int signum)
{
	if (signum == SIGINT)
	{
		received_signal = 2;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		// rl_redisplay();
		close(0);
		exit_status(130, TRUE);
	}
}

void	set_sigint_handle_here_doc(void)
{
	struct sigaction	sa;

	reset_sigint();
	ft_bzero(&sa, sizeof (struct sigaction));
	sa.sa_handler = &handle_sigint_here_doc;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
}

void	block_sigint(void)
{
	struct sigaction	sa;

	reset_sigint();
	ft_bzero(&sa, sizeof (struct sigaction));
	sa.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa, NULL);
}

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

void	set_sigint_handle(void)
{
	struct sigaction	sa;

	reset_sigint();
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
