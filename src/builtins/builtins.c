#include  "minishell.h"

void	handle_builtins(t_cmd *cmd, int nb_cmd)
{
	if (strcmp(cmd->name, "echo") == 0)
	else if (strcmp(cmd->name, "pwd") == 0)
	else if (strcmp(cmd->name, "env") == 0)
	else if (strcmp(cmd->name, "cd") == 0 && nb_cmd == 1)
	else if (strcmp(cmd->name, "export") == 0 && nb_cmd == 1)
	else if (strcmp(cmd->name, "unset") == 0 && nb_cmd == 1)
	else if (strcmp(cmd->name, "exit") == 0 && nb_cmd == 1)
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