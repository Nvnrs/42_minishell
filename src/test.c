/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:11:00 by nveneros          #+#    #+#             */
/*   Updated: 2025/02/17 12:57:52 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

#include <unistd.h>

#include <stdlib.h>

#include <sys/stat.h>

#include <sys/types.h>
#include <dirent.h>

#include <signal.h>


void	handle_sigint(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	set_sigint_handle(void)
{
	struct sigaction	sa;

	sa.sa_handler = &handle_sigint;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
}

void	ignore_signal_but_sigint(void)
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

void	print_split(char **split)
{
	int	i;
	int	len;

	i = 0;
	len = len_split(split);
	while (i < len)
	{
		ft_printf("split[%d]: %s\n", i, split[i]);
		i++;
	}
}
int	main(void)
{
	char	*rd;
	int		flag;
	char	**split;

	printf("hello hello\n");
	set_signals();
	flag = 1;
	while (flag)
	{
		rd = readline("> ");
		if (rd && *rd)
			add_history(rd);
		if (rd == NULL)
			flag = 0;
		else
		{
			split = ft_split(rd, ' ');
			printf("rd contains %d words\n", len_split(split));
			print_split(split);
			free_split(split);
		}
		free(rd);
	}
	rl_clear_history();
	printf("bye bye\n");
	return(0);
}

c_is_in_charset()