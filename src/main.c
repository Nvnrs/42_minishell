/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:10:56 by nveneros          #+#    #+#             */
/*   Updated: 2025/02/17 17:18:32 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*rd;
	int		flag;
	char	**split;

	flag = 1;
	while (flag)
	{
		rd = readline("> ");
		if (rd && *rd)
		{
			add_history(rd);
			if (!basics_checks(rd))
			{
				free(rd);
				continue;
			}
			split = parse_input(rd);
			print_split(split);
			free_split(split);
		}
		else if (rd == NULL)
			flag = 0;
		free(rd);
	}
	rl_clear_history();
	return (0);
}
