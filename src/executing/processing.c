/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:41:38 by nveneros          #+#    #+#             */
/*   Updated: 2025/03/11 15:07:41 by nveneros         ###   ########.fr       */
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

	if (handle_redirection(*cmd->lst_operator, cmd) != 0)
	{
		free_lst_and_pids(lst_cmd, env, tab_pid);
		exit(exit_status(0, FALSE));
	}
	path_cmd = get_path_cmd(cmd, env);
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

	i = 0;
	while (i < nb_cmd)
	{
		waitpid(pid[i], &wstatus, 0);
		if (WIFSIGNALED(wstatus))
		{
			status_code = 128 + WTERMSIG(wstatus);
			printf("\n");
			exit_status(status_code, TRUE);
		}
		else if (WIFEXITED(wstatus))
		{
			status_code = WEXITSTATUS(wstatus);
			exit_status(status_code, TRUE);
		}
		i++;
	}
	free(pid);
}

int	*handle_process(t_list **lst_cmd, t_list **env, int nb_cmd)
{
	int		*pid;
	int		i;
	t_list	*cmd;

	i = 0;
	pid = NULL;
	pid = malloc(nb_cmd * sizeof(int));
	cmd = *lst_cmd;
	while (i < nb_cmd)
	{
		pid[i] = fork();
		if (pid[i] == -1)
			return (free(pid), NULL);
		else if (pid[i] == 0)
		{
			reset_sigint();
			if (is_builtin(cmd->content))
				handle_builtins_child(lst_cmd, cmd->content, env, pid);
			else
				handle_cmd(cmd->content, lst_cmd, env, pid);
		}
		i++;
		cmd = cmd->next;
	}
	return (pid);
}

/**
 * Separe les commandes en plusieurs process
 */
int	processing(t_list **lst_cmd, int nb_cmd, t_list **env, int **pipes)
{
	int		*pid;
	t_list	*cmd;

	cmd = *lst_cmd;
	if (is_builtin(cmd->content) && nb_cmd == 1)
	{
		handle_builtins_parent(lst_cmd, cmd->content, env);
		return (0);
	}
	block_sigint();
	pid = handle_process(lst_cmd, env, nb_cmd);
	close_and_free_pipes(pipes, nb_cmd - 1);
	wait_childs_and_handle_signals(pid, nb_cmd);
	set_sigint_handle();
	return (0);
}
