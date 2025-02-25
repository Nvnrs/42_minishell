#include "minishell.h"

static void	handle_sigint(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static void	set_sigint_handle(void)
{
	struct sigaction	sa;

	sa.sa_handler = &handle_sigint;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
}

static void	ignore_signal_but_sigint(void)
{
	struct sigaction	sa;
	int					i;

	sa.sa_handler = SIG_IGN;
	i = 1;
	while (i <= 31)
	{
		if (i != SIGINT)
			sigaction(i, &sa, NULL);
		i++;
	}
}

void	set_signals(void)
{
	ignore_signal_but_sigint();
	set_sigint_handle();
}