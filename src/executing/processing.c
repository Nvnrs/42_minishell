/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:41:38 by nveneros          #+#    #+#             */
/*   Updated: 2025/02/25 18:38:51 by nveneros         ###   ########.fr       */
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
	return (status_code);
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
		if (access(path_cmd, F_OK | X_OK) == 0)
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

/**
	Check if the given path is valid
	Return error code
 */
t_bool	path_is_valid(char *path)
{
	struct stat	buffer;
	
	stat(path, &buffer);
	if (access(path, F_OK) != 0)
	{
		exit_status(1, TRUE);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (FALSE);
	}
	else if (access(path, X_OK) != 0)
	{
		exit_status(126, TRUE);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		return (FALSE);
	}
	else if (S_ISDIR(buffer.st_mode) == TRUE)
	{
		exit_status(126, TRUE);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": Is a directory\n", 2);
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
			if (path_is_valid(cmd->name))
				return (ft_strdup(cmd->name));
			return (NULL);
		}
		path = find_path_with_env(cmd, env);
		if (path == NULL)
		{
			ft_putstr_fd(cmd->name, 2);
			ft_putstr_fd(": Command not found\n", 2);
			return (NULL);
		}
		return (path);
	}
	if (path_is_valid(cmd->name))
		return (ft_strdup(cmd->name));
	return (NULL);
}

static void	handle_cmd(t_cmd *cmd, t_list **lst_cmd, t_list **env)
{
	char *path_cmd;
	// printf("START\n");
	//path = get_path_cmd(cmd, env);
	handle_redirection_in(*cmd->operators_in, env);
	handle_redirection_out(*cmd->operators_out, env);
	path_cmd = get_path_cmd(cmd, env);//tester avec NULL
	printf("PATH : %s\n", path_cmd);
	if (path_cmd == NULL)
	{
		// printf("command not found\n");
		close_and_free_pipes(cmd->pipes, 2);
		free_lst_cmd(lst_cmd);
		free_list_env(env);
		exit(EXIT_FAILURE);
	}
	close_and_free_pipes(cmd->pipes, 2);
	// free_lst_cmd(lst_cmd);
	free_list_env(env);
	if (execve(path_cmd, cmd->args_exec, NULL) == -1)
		perror(NULL);
	exit(0);
}

/**
 * Separe les commandes en plusieurs process
 */
int	processing(t_list **lst_cmd, int nb_cmd, t_list **env, int **pipes)
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
		//printf("___________HANDLE_CMD\n");
		handle_cmd(lst->content, lst_cmd, env);
	}
	close_and_free_pipes(pipes, 2);
	while (i > 0)
	{
		//printf("WAIT START\n");
		wait(NULL);//pas complet
		//printf("WAIT END\n");
		i--;
	}
	return (0);
}