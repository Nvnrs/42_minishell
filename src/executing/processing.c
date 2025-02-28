/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchateau <pchateau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:41:38 by nveneros          #+#    #+#             */
/*   Updated: 2025/02/28 14:26:47 by pchateau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
* Effectue les redirections in et out
* Close pipes
* Execute la  commande de la commande
*/

int	exit_status(int new_status_code, t_bool update)
{
	static int status_code;

	if (update)
		status_code = new_status_code;
	// printf("inside exit_status(): %d\n", status_code);
	// if (update)
		// printf("new exit_status(): %d\n", new_status_code);
	return (status_code);
}

char	*get_exit_status_str(void)
{
	char	*exit_status_str;

	exit_status_str = ft_itoa(exit_status(0, FALSE));
	return (exit_status_str);
}

char	*tests_path_for_find_cmd(t_cmd *cmd, char **tests_path)
{
	int		i;
	char	*path_cmd;
	char	*path_with_slash;

	i = 0;
	while (tests_path[i])
	{
		path_with_slash = ft_strjoin(tests_path[i], "/");
		path_cmd = ft_strjoin(path_with_slash, cmd->name);
		if (access(path_cmd, F_OK) == 0)
		{
			free(path_with_slash);
			return (path_cmd);
		}
		free(path_with_slash);
		free(path_cmd);
		i++;
	}
	return (NULL);
}

int	handle_error(int status_code, char *context, char *message)
{
	ft_putstr_fd(context, 2);
	ft_putstr_fd(message, 2);
	return (exit_status(status_code, TRUE));
}

/**
	Check if the given path is valid
	Return error code
 */

t_bool	cmd_path_is_valid(char *path)
{
	struct stat	buffer;
	
	stat(path, &buffer);
	if (access(path, F_OK) != 0)
	{
		handle_error(1, path, ": No such file or directory\n");
		return (FALSE);
	}
	if (access(path, X_OK) != 0)
	{
		handle_error(126, path, ": Permission denied\n");
		return (FALSE);
	}
	if (S_ISDIR(buffer.st_mode) == TRUE)
	{
		handle_error(126, path, ": Is a directory\n");
		return (FALSE);
	}
	return (TRUE);
}


t_bool	path_var_env_exist(t_list **env)
{
	char	*path_cmd;
	char	*path_env;
	char	**paths_in_path_env;

	if (env == NULL || *env == NULL)
		return (FALSE);
	path_env = find_value_in_env("PATH", env);
	if (path_env == NULL)
		return (FALSE);
	free(path_env);
	return (TRUE);
}

char *find_path_with_env(t_cmd *cmd, t_list **env)
{
	char	*path_cmd;
	char	*path_env;
	char	**paths_in_path_env;

	if (!path_var_env_exist(env))
			return (NULL);
	path_env = find_value_in_env("PATH", env);
	paths_in_path_env = ft_split(path_env, ':');
	path_cmd = tests_path_for_find_cmd(cmd, paths_in_path_env);
	free(path_env);
	free_split(paths_in_path_env);
	return (path_cmd);
}

char *get_path_cmd(t_cmd *cmd, t_list **env)
{
	char	*path;
	
	if (path_var_env_exist(env))
	{
		if (str_contain_c(cmd->name,'/'))
		{
			printf("HERE : %s", cmd->name);
			if (cmd_path_is_valid(cmd->name))
				return (ft_strdup(cmd->name));
			return (NULL);
		}
		path = find_path_with_env(cmd, env);
		printf("PATH :%s\n", path);
		if (path == NULL)
		{
			handle_error(127, cmd->name, ": Command not found\n");
			return (NULL);
		}
		if (!cmd_path_is_valid(path))
			return (free(path), (NULL));
		return (path);
	}
	if (cmd_path_is_valid(cmd->name))
		return (ft_strdup(cmd->name));
	return (NULL);
}

static void	handle_cmd(t_cmd *cmd, t_list **lst_cmd, t_list **env, int *tab_pid)
{
	char	*path_cmd;
	char	**str_env;
	// printf("START\n");
	//path = get_path_cmd(cmd, env);
	if(handle_redirection(*cmd->lst_operator, env, cmd) != 0)
	{
		//close_and_free_pipes(cmd->pipes, 2);
		free_lst_cmd(lst_cmd);
		free_list_env(env);
		free(tab_pid);
		exit(exit_status(0, FALSE));
	}
	//close_and_free_pipes(cmd->pipes, 2);
	path_cmd = get_path_cmd(cmd, env);//tester avec NULL
	// printf("PATH :%s\n", path_cmd);
	// printf("OUTPUT CODE : %d\n", exit_status(0, FALSE));
	if (path_cmd == NULL)
	{
		// printf("command not found\n");
		//close_and_free_pipes(cmd->pipes, 2);
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

void	print_pid_tab(int *pid, int nb_cmd)
{
	int	i;

	i = 0;
	while (i < nb_cmd)
	{
		printf("pid[%d]:%d\n", i, pid[i]);
		i++;
	}
}

void	wait_childs_and_handle_signals(int *pid, int nb_cmd)
{
	int	i;
	int	wstatus;
	int	status_code;
	
	print_pid_tab(pid, nb_cmd);
	i = 0;
	while (i < nb_cmd)
	{
		printf("START wait number %d\n", i);
		waitpid(pid[i], &wstatus, 0);
		printf("END wait number %d\n", i);
		if (WIFSIGNALED(wstatus))
		{
			status_code = 128 + WTERMSIG(wstatus);
			printf("exit status code of child with signal:%d\n", status_code);
			exit_status(status_code, TRUE);
		}
		else if (WIFEXITED(wstatus))
		{
			status_code = WEXITSTATUS(wstatus);
			printf("exit status code of child:%d\n", status_code);
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
		// if (is_builtin())
		// {
		// 	handle_builtins(lst->content, nb_cmd);
		// }
		// else
		// {
			// nb_fork++;
			pid[i] = fork();
			if (pid[i] == -1)
				return (EXIT_FAILURE);
			else if (pid[i] == 0)
			{
				handle_cmd(lst->content, lst_cmd, env, pid);
				break;
			}
		// }
		//sleep(2*i);
		i++;
		lst = lst->next;
	}
	// close_and_free_pipes(pipes, 2);
	if (nb_cmd > 1)
		close_and_free_pipes(pipes, nb_cmd - 1);
	wait_childs_and_handle_signals(pid, nb_cmd/*, nb_fork*/);
	return (0);
}
