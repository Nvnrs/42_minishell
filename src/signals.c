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

static void	block_sigint(void)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa, NULL);
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
	int					i;

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