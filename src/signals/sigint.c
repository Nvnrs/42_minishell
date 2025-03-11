/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigint.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:47:54 by nveneros          #+#    #+#             */
/*   Updated: 2025/03/11 14:49:32 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_received_signal;

void	reset_sigint(void)
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
		g_received_signal = 2;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		close(0);
		exit_status(130, TRUE);
	}
}

void	set_sigint_handle_here_doc(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof (struct sigaction));
	sa.sa_handler = &handle_sigint_here_doc;
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
}

void	block_sigint(void)
{
	struct sigaction	sa;

	// reset_sigint();
	ft_bzero(&sa, sizeof (struct sigaction));
	sa.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa, NULL);
}

void	handle_sigint(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		exit_status(130, TRUE);
	}
}
