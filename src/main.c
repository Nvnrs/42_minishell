/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchateau <pchateau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:10:56 by nveneros          #+#    #+#             */
/*   Updated: 2025/02/28 14:26:28 by pchateau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	add_pipes_in_cmd(t_cmd *cmd, int pipes, int nb_pipes)
// {
// 	cmd->pipes = pipes;
// 	cmd->nb_pipes = nb_pipes;
// }


void	add_pipes_in_lst_cmd(t_list **lst_cmd, int **pipes)
{
	t_list *lst;
	t_cmd *cmd;
	int nb_pipes;

	lst = *lst_cmd;
	nb_pipes = ft_lstsize(lst) - 1;
	while (lst)
	{
		cmd = lst->content;
		cmd->pipes = pipes;
		cmd->nb_pipes = nb_pipes;
		lst = lst->next;
	}
}

/**
 * Gere l'input de l'utilisateur
 */
int	handle_readline(char *rd, t_list **env)
{
	char	**input;
	t_list	**lst_cmd;
	int		**pipes;

	add_history(rd);
	if (!basics_checks(rd))
	{
		free(rd);
		return (1);
	}
	input = parse_input(rd);
	lst_cmd = init_lst_cmd(input);
	pipes = init_pipes(ft_lstsize(*lst_cmd) - 1);//nb_pipe = nb_cmd - 1
	//ajouter les pipes au commandes
	add_pipes_in_lst_cmd(lst_cmd, pipes);
	add_pipe_redirect(lst_cmd, ft_lstsize(*lst_cmd));
	free_split(input);
	apply_expansion(lst_cmd, env);
	apply_remove_quotes(lst_cmd);
	ft_lstiter(*lst_cmd, print_cmd);
	processing(lst_cmd, ft_lstsize(*lst_cmd), env, pipes);
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
		rd = readline("> ");
		if (rd && *rd)
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
