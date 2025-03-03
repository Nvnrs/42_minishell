/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 11:43:56 by nveneros          #+#    #+#             */
/*   Updated: 2025/03/03 14:01:25 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "minishell.h"

char **get_only_args(char **args_exec)
{
	char **args;

	if (args_exec == NULL)
		args = NULL;
	else
		args = &args_exec[1];
	return (args);
}

void	save_in_and_out(t_cmd *cmd)
{
	if (operator_in_in_lst_operator(*cmd->lst_operator))
		cmd->saved_in = dup(0);
	if (operator_out_in_lst_operator(*cmd->lst_operator))
		cmd->saved_out = dup(1);
}


void	restore_in_and_out(t_cmd *cmd)
{
	if (cmd->saved_in != -1)
	{
		dup2(cmd->saved_in, 0);
		close(cmd->saved_in);
	}
	if (cmd->saved_out != -1)
	{
		dup2(cmd->saved_out, 1);
		close(cmd->saved_out);
	}
}




void	builtin_case(t_list **lst_cmd, t_cmd *cmd, t_list **env, int *pid)
{
	char **args;
	
	args = get_only_args(cmd->args_exec);
	if (strcmp(cmd->name, "echo") == 0)
		builtin_echo(cmd);
	else if (strcmp(cmd->name, "env") == 0)
		builtin_env(env);
	else if (strcmp(cmd->name, "pwd") == 0)
		builtin_pwd();
	else if (strcmp(cmd->name, "cd") == 0)
		return ;
	else if (strcmp(cmd->name, "export") == 0)
		builtin_export(args, env); 
	else if (strcmp(cmd->name, "unset") == 0)
		builtin_unset(args, env);
	else if (strcmp(cmd->name, "exit") == 0)
		builtin_exit(args, lst_cmd, env, pid);
}

void	handle_builtins_parent(t_list **lst_cmd, t_cmd *cmd, t_list **env)
{
	save_in_and_out(cmd);
	if (handle_redirection(*cmd->lst_operator, env, cmd))
	{
		restore_in_and_out(cmd);
		return;
	}
	builtin_case(lst_cmd, cmd, env, NULL);
	restore_in_and_out(cmd);
}

void	handle_builtins_child(t_list **lst_cmd, t_cmd *cmd, t_list **env, int *pid)
{
	if (handle_redirection(*cmd->lst_operator, env, cmd) != 0)
	{
		free_lst_and_pids(lst_cmd, env, pid);
		exit(exit_status(0, FALSE));
	}
	builtin_case(lst_cmd, cmd, env, pid);
	free_lst_and_pids(lst_cmd, env, pid);
	exit(exit_status(0, FALSE));
}


t_bool	is_builtin(t_cmd *cmd)
{
	char *cmd_name;

	cmd_name = cmd->name;
	if(strcmp(cmd_name, "echo") == 0
		|| strcmp(cmd_name, "cd") == 0
		|| strcmp(cmd_name, "export") == 0
		|| strcmp(cmd_name, "unset") == 0
		|| strcmp(cmd_name, "exit") == 0
		|| strcmp(cmd_name, "echo") == 0
		|| strcmp(cmd_name, "pwd") == 0
		|| strcmp(cmd_name, "env") == 0)
			return (TRUE);
	return (FALSE);
}