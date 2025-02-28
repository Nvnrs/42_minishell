/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchateau <pchateau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:41:38 by nveneros          #+#    #+#             */
/*   Updated: 2025/02/28 15:39:26 by pchateau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_cmd(t_cmd *cmd, t_list **lst_cmd, t_list **env, int *tab_pid)
{
	char	*path_cmd;
	char	**str_env;
	// printf("START\n");
	if(handle_redirection(*cmd->lst_operator, env, cmd) != 0)
	{
		free_lst_cmd(lst_cmd);
		free_list_env(env);
		free(tab_pid);
		exit(exit_status(0, FALSE));
	}
	path_cmd = get_path_cmd(cmd, env);//tester avec NULL
	// printf("PATH :%s\n", path_cmd);
	// printf("OUTPUT CODE : %d\n", exit_status(0, FALSE));
	if (path_cmd == NULL)
	{
		free_lst_cmd(lst_cmd);
		free_list_env(env);
		free(tab_pid);
		exit(exit_status(0, FALSE));
	}
	str_env = lst_env_to_tab_str(env);
	if (execve(path_cmd, cmd->args_exec, str_env) == -1)//passer env en str
		perror(path_cmd);
	free_lst_cmd(lst_cmd);
	free_split(str_env);
	free_list_env(env);
	free(path_cmd);
	free(tab_pid);
	exit(exit_status(1, TRUE));
}

void	wait_childs_and_handle_signals(int *pid, int nb_cmd)
{
	int	i;
	int	wstatus;
	int	status_code;
	
	// print_pid_tab(pid, nb_cmd);
	i = 0;
	while (i < nb_cmd)
	{
		// printf("START wait number %d\n", i);
		waitpid(pid[i], &wstatus, 0);
		// printf("END wait number %d\n", i);
		if (WIFSIGNALED(wstatus))
		{
			status_code = 128 + WTERMSIG(wstatus);
			// printf("exit status code of child with signal:%d\n", status_code);
			exit_status(status_code, TRUE);
		}
		else if (WIFEXITED(wstatus))
		{
			status_code = WEXITSTATUS(wstatus);
			// printf("exit status code of child:%d\n", status_code);
			exit_status(status_code, TRUE);
		}
		i++;
	}
	free(pid);
}

/**
 * Separe les commandes en plusieurs process
 */
int	processing(t_list **lst_cmd, int nb_cmd, t_list **env, int **pipes)
{
	int	i;
	// int	nb_fork;
	int	*pid;
	t_list	*lst;

	i = 0;
	// nb_fork = 0;
	lst = *lst_cmd;
	pid = malloc(nb_cmd * sizeof(int));
	while (i < nb_cmd)
	{
		if (is_builtin(lst->content))
		{
			printf("IS BUILTIN\n");
			handle_builtins(lst->content, nb_cmd, env);
		}
		else
		{
			// nb_fork++;
			pid[i] = fork();
			if (pid[i] == -1)
				return (EXIT_FAILURE);
			else if (pid[i] == 0)
			{
				handle_cmd(lst->content, lst_cmd, env, pid);
				break;
			}
		}
		//sleep(2*i);
		i++;
		lst = lst->next;
	}
	if (nb_cmd > 1)
		close_and_free_pipes(pipes, nb_cmd - 1);
	wait_childs_and_handle_signals(pid, nb_cmd/*, nb_fork*/);
	return (0);
}
