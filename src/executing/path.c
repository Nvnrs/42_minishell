#include "minishell.h"

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
	// char	*path_cmd;
	char	*path_env;
	// char	**paths_in_path_env;

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
	
	if (cmd->name == NULL)
		return (NULL);
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
		// printf("PATH :%s\n", path);
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
