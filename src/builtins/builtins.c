#include  "minishell.h"


void	builtin_env(t_list **env)
{
	print_list_env(env);
	exit_status(0, TRUE);
}

t_bool	is_valid_key(char *str)
{
	int	i;

	i = 0;
	if (ft_isalpha(str[i]) || str[i] == '_')
	{
		while (str[i])
		{
			if (!(ft_isalnum(str[i]) || str[i] == '_'))
				return (FALSE);
			i++;
		}
		return (TRUE);
	}
	return (FALSE);
}

t_key_val	*create_new_var(char *str)
{
	int	i;
	int j;
	char *key;
	char *val;

	i = 0;
	if ((ft_isalpha(str[i]) || str[i] == '_'))
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '\0' || str[i] != '=')
		return (NULL);
	key = ft_substr(str, 0, i);
	i++; //skip = 
	val = ft_substr(str, i, (ft_strlen(str) - 1));
	printf("KEY = %s\n", key);
	printf("VAL = %s\n", val);
	return (NULL);
}

void	builtin_export(char **args, t_cmd *cmd, t_list **env)
{
	int			i;
	t_key_val	var;

	i = 0;
	// printf("HELLOOERIEOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO\n");
	if (args == NULL)
	{
		exit_status(0, TRUE);
		return;
	}
	while (args[i])
	{
		if (!is_valid_key(args[i]))
		{
			ft_putstr_fd("export: '", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			exit_status(1, TRUE);
		}
		else
		{
			create_new_var(args[i]);
		}
		
		i++;
	}
	
}

char **get_only_args(char **args_exec)
{
	char **args;

	if (args_exec == NULL)
		args = NULL;
	else
		args = &args_exec[1];
	return (args);
}

void	handle_builtins(t_cmd *cmd, int nb_cmd, t_list **env)
{
	char **args;

	args = get_only_args(cmd->args_exec);
	print_split(args);
	if (strcmp(cmd->name, "echo") == 0)
		return;
	else if (strcmp(cmd->name, "env") == 0)
		builtin_env(env);
	else if (strcmp(cmd->name, "pwd") == 0)
		return;
	else if (strcmp(cmd->name, "cd") == 0 && nb_cmd == 1)
		return;
	else if (strcmp(cmd->name, "export") == 0 && nb_cmd == 1)
		builtin_export(args, cmd, env); 
	// else if (strcmp(cmd->name, "unset") == 0 && nb_cmd == 1)
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