#include  "minishell.h"


void	builtin_env(t_list **env)
{
	print_list_env(env);
	exit_status(0, TRUE);
}

void	builtin_export(t_cmd *cmd, t_list **env)
{
	char **args;

	args = cmd->args;
	if (cmd->args_exec == NULL)
		return (exit_status(0, TRUE));

}

char **get_only_args(char **args_exec)
{
	char **args;

	if (cmd->args_exec == NULL)
		args = NULL;
	else
		args = args_exec[1];
}

void	handle_builtins(t_cmd *cmd, int nb_cmd, t_list **env)
{
	char **args;

	args = get_only_args(cmd->args_exec);
	// print_split(args);
	// return;
	// if (strcmp(cmd->name, "echo") == 0)
	// 	return;
	// else if (strcmp(cmd->name, "env") == 0)
	// 	builtin_env(env);
	// // else if (strcmp(cmd->name, "pwd") == 0)
	// // else if (strcmp(cmd->name, "cd") == 0 && nb_cmd == 1)
	// // else if (strcmp(cmd->name, "export") == 0 && nb_cmd == 1)
	// else if (strcmp(cmd->name, "unset") == 0 && nb_cmd == 1)
	// 	builtin_export(cmd, env);
	// else if (strcmp(cmd->name, "exit") == 0 && nb_cmd == 1)
}

// * CD
// * export
// * unset
// * exit

// Execution classique :

// * echo option -n
// * pwd
// * env NO OPTIONS ET NO ARG

t_bool	is_builtin(char *cmd_name)
{
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