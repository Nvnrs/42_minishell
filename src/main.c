/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:10:56 by nveneros          #+#    #+#             */
/*   Updated: 2025/02/24 17:56:31 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
* Effectue les redirections in et out
* Close pipes
* Execute la  commande de la commande
*/
void	handle_cmd(t_cmd *cmd, t_list **lst_cmd, t_list **env)
{
	char *arg[3];
	arg[0] = "echo\0";
	arg[1] = "test";
	arg[2] = NULL;
	// printf("START\n");
	handle_redirection_in(*cmd->operators_in, lst_cmd, cmd->pipes, env);
	handle_redirection_out(*cmd->operators_out, lst_cmd, cmd->pipes, env);
	close_and_free_pipes(cmd->pipes, 2);
	free_lst_cmd(lst_cmd);
	free_list_env(env);
	execve("/bin/echo", arg, NULL);
	exit(0);
}

/**
 * Separe les commandes en plusieurs process
 */
int	processing(t_list **lst_cmd, int nb_cmd, t_list **env)
{
	int	i;
	int	pid;
	t_list	*lst;

	i = 0;
	lst = *lst_cmd;
	while (i < nb_cmd)
	{
		pid = fork();
		if (pid == -1)
			return (1);
		else if (pid == 0)
			break ;
		i++;
		lst = lst->next;
	}
	if (pid == 0)
	{
		printf("___________HANDLE_CMD\n");
		handle_cmd(lst->content, lst_cmd, env);
	}
	while (i > 0)
	{
		// printf("WAIT\n");
		wait(NULL);//pas complet
		i--;
	}
	return (0);
}

// APPLY EXPANSION 

void	apply_expansion_args_exec(char **args_exec, t_list **lst_env)
{
	int i;

	i = 0;
	while (args_exec[i])
	{
		args_exec[i] = expansion_str(args_exec[i], lst_env);
		i++;
	}
}


void	apply_expansion_operators(t_list **operators, t_list **lst_env)
{
	t_list	*lst;
	t_key_val *content;

	lst = *operators;
	while (lst)
	{
		content = lst->content;
		if (ft_strcmp(content->key, "<<") != 0)
		{
			content->value = expansion_str(content->value, lst_env);
		}
		lst = lst->next;
	}
		
}
	/**
	 * apply to
	 * cmd
	 * 	-> name
	 * 	-> args_exec
	 *  -> operators_in / out
	 * 		-> value
	 */

void	apply_expansion(t_list **lst_cmd, t_list **lst_env)
{
	t_list	*lst;
	t_cmd	*cmd;

	lst = *lst_cmd;

	while (lst)
	{
		cmd = lst->content;
		cmd->name = expansion_str(cmd->name, lst_env);
		apply_expansion_args_exec(cmd->args_exec, lst_env);
		apply_expansion_operators(cmd->operators_in, lst_env);
		apply_expansion_operators(cmd->operators_out, lst_env);	
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
	pipes = init_pipes(2);
	lst_cmd = init_lst_cmd(input, pipes);
	free_split(input);
	apply_expansion(lst_cmd, env);
	processing(lst_cmd, ft_lstsize(*lst_cmd), env);
	ft_lstiter(*lst_cmd, print_cmd);
	free_lst_cmd(lst_cmd);
	close_and_free_pipes(pipes, 2);
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*rd;
	int		flag;
	// char	**input;
	t_list	**env;
	// t_list	**lst_cmd;
	// int		**pipes;

	(void)argc;
	(void)argv;
	env = init_list_env(envp);
	flag = 1;
	while (flag)
	{
		rd = readline("> ");
		if (rd && *rd)
		{
			if (handle_readline(rd, env) == 1)
				continue ;
			// add_history(rd);
			// if (!basics_checks(rd))
			// {
			// 	free(rd);
			// 	continue;
			// }
			// input = parse_input(rd);
			// pipes = init_pipes(2);
			// printf("pipes[0][0] = %d\npipes[0][1] = %d\npipes[1][0] = %d\npipes[1][1] = %d\n", pipes[0][0], pipes[0][1], pipes[1][0], pipes[1][1]);
			// lst_cmd = init_lst_cmd(input, pipes);
			// ft_lstiter(*lst_cmd, print_cmd);
			// free_lst_cmd(lst_cmd);
			// free_split(input);
			// close_and_free_pipes(pipes, 2);
		}
		else if (rd == NULL)
			flag = 0;
		free(rd);
	}
	rl_clear_history();
	free_list_env(env);
	return (0);
}
