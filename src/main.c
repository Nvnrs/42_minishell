/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:10:56 by nveneros          #+#    #+#             */
/*   Updated: 2025/03/07 10:34:57 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Gere l'input de l'utilisateur
 */

extern int	g_received_signal;

void	assign_data_in_data(t_data *data, t_list **lst_cmd, t_list **env, int **pipes)
{
	data->lst_cmd = lst_cmd;
	data->env = env;
	data->pipes = pipes;
}

int	handle_readline(char *rd, t_list **env)
{
	char	**input;
	t_list	**lst_cmd;
	int		**pipes;
	t_data	data;

	add_history(rd);
	if (!basics_checks(rd))
	{
		free(rd);
		return (1);
	}
	input = parse_input(rd);
	print_split(input);
	lst_cmd = init_lst_cmd(input);
	pipes = init_pipes(ft_lstsize(*lst_cmd) - 1);
	assign_data_in_data(&data, lst_cmd, env, pipes);
	add_pipes_in_lst_cmd(lst_cmd, pipes);
	add_pipe_redirect(lst_cmd, ft_lstsize(*lst_cmd));
	free_split(input);
	apply_expansion(lst_cmd, env);
	apply_remove_quotes(lst_cmd);
	// ft_lstiter(*lst_cmd, print_cmd);
	if (create_all_here_doc(lst_cmd, env, &data) == 0)
		processing(lst_cmd, ft_lstsize(*lst_cmd), env, pipes);
	else
		close_and_free_pipes(pipes, ft_lstsize(*lst_cmd) - 1);
	free_lst_cmd(lst_cmd);
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*rd;
	int		flag;
	t_list	**env;

	(void)argc;
	(void)argv;
	env = init_list_env(envp);
	set_signals();
	flag = 1;
	while (flag)
	{
		g_received_signal = 0;
		rd = readline("minismash$ ");
		if (rd)
		{
			if (handle_readline(rd, env) == 1)
				continue ;
		}
		else if (rd == NULL)
			flag = 0;
		free(rd);
	}
	rl_clear_history();
	free_list_env(env);
	return (0);
}
