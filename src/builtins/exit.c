/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 17:15:48 by nveneros          #+#    #+#             */
/*   Updated: 2025/03/10 14:46:49 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	numeric_arg_required(char *first_arg)
{
	force_print_stderr("exit: ");
	handle_error(1, first_arg, ": numeric argument required\n");
}

static t_bool	str_is_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] && str[i] == '-')
		i++;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			i++;
		else
			return (FALSE);
	}
	return (TRUE);
}

void	builtin_exit(char **args, t_list **lst_cmd, t_list **env, int *pid)
{
	int	exit_number;

	if (ft_lstsize(*lst_cmd) == 1)
		printf("exit\n");
	if (args && args[0])
	{
		if (str_is_number(args[0]))
		{
			if (len_split(args) > 1)
			{
				handle_error(1, "exit", ": too many arguments\n");
				return ;
			}
			exit_number = atoi(args[0]);
			if (exit_number >= 0 && exit_number <= 255)
			{
				free_lst_and_pids(lst_cmd, env, pid);
				exit(exit_status(exit_number, TRUE));
			}
		}
		else
			numeric_arg_required(args[0]);
	}
	free_lst_and_pids(lst_cmd, env, pid);
	exit(exit_status(0, FALSE));
}
