/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 17:13:32 by nveneros          #+#    #+#             */
/*   Updated: 2025/03/06 17:14:36 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_pwd(t_list **env)
{
	char		*pwd;
	t_key_val	*new_pwd;
	char		*oldpwd;
	t_key_val	*new_oldpwd;
	char		*current_directory;

	pwd = find_value_in_env("PWD", env);
	oldpwd = find_value_in_env("OLDPWD", env);
	if (pwd != NULL)
	{
		current_directory = getcwd(NULL, 0);
		new_pwd = init_key_val("PWD", current_directory);
		free(current_directory);
		save_new_var(new_pwd, env);
	}
	if (oldpwd != NULL && pwd != NULL)
	{
		new_oldpwd = init_key_val("OLDPWD", pwd);
		save_new_var(new_oldpwd, env);
	}
	else if (oldpwd != NULL && pwd == NULL)
		remove_var("OLDPWD", env);
	if (pwd != NULL)
		free(pwd);
	if (oldpwd != NULL)
		free(oldpwd);
}

static void	chdir_with_given_path(char *path, t_list **env)
{
	if (access(path, F_OK) != 0)
	{
		force_print_stderr("cd: ");
		handle_error(1, path, ": no such file or directory\n");
	}
	else if (access(path, X_OK) != 0)
	{
		force_print_stderr("cd: ");
		handle_error(1, path, ": permission denied\n");
	}
	else
	{
		exit_status(0, TRUE);
		chdir(path);//update in env ?
		update_pwd(env);
	}
}

void	builtin_cd(char **args, t_list **env)
{
	char	*home_value;

	if (args && args[0])
		chdir_with_given_path(args[0], env);
	else
	{
		home_value = find_value_in_env("HOME", env);
		if (home_value != NULL)
		{
			chdir_with_given_path(home_value, env);
			free(home_value);
		}
		else
			handle_error(1, "cd", ": HOME not set\n");
	}
}
