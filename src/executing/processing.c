/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:41:38 by nveneros          #+#    #+#             */
/*   Updated: 2025/03/06 17:23:53 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_lst_and_pids(t_list **lst_cmd, t_list **env, int *tab_pid)
{
	if (lst_cmd)
		free_lst_cmd(lst_cmd);
	if (env)
		free_list_env(env);
	if (tab_pid)
		free(tab_pid);
}

static void	handle_cmd(t_cmd *cmd, t_list **lst_cmd, t_list **env, int *tab_pid)
{
	char	*path_cmd;
	char	**str_env;
	// printf("START\n");
	if (handle_redirection(*cmd->lst_operator, cmd) != 0)
	{
		free_lst_and_pids(lst_cmd, env, tab_pid);
		exit(exit_status(0, FALSE));
	}
	path_cmd = get_path_cmd(cmd, env);
	// printf("PATH :%s\n", path_cmd);
	// printf("OUTPUT CODE : %d\n", exit_status(0, FALSE));
	if (path_cmd == NULL)
	{
		free_lst_and_pids(lst_cmd, env, tab_pid);
		exit(exit_status(0, FALSE));
	}
	str_env = lst_env_to_tab_str(env);
	if (execve(path_cmd, cmd->args_exec, str_env) == -1)
		perror(path_cmd);
	free_lst_and_pids(lst_cmd, env, tab_pid);
	free_split(str_env);
	free(path_cmd);
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
	int		i;
	int		*pid;
	t_list	*lst;

	i = 0;
	lst = *lst_cmd;
	if (is_builtin(lst->content) && nb_cmd == 1)
	{
		printf("IS BUILTIN\n");
		handle_builtins_parent(lst_cmd, lst->content, env);
		return (0);
	}
	pid = NULL;
	pid = malloc(nb_cmd * sizeof(int));//attention proteger le malloc
	while (i < nb_cmd)
	{
		pid[i] = fork();
		if (pid[i] == -1)
			return (EXIT_FAILURE);
		else if (pid[i] == 0)
		{
			if (is_builtin(lst->content))
				handle_builtins_child(lst_cmd, lst->content, env, pid);
			else
				handle_cmd(lst->content, lst_cmd, env, pid);
			break ;
		}
		i++;
		lst = lst->next;
	}
	close_and_free_pipes(pipes, nb_cmd - 1);
	wait_childs_and_handle_signals(pid, nb_cmd);
	return (0);
}
