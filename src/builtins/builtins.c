#include  "minishell.h"

t_bool	is_n_option_echo(char *str)
{
	int	i;

	i = 0;
	if (str[i] && str[i] == '-')
		i++;
	else
		return (FALSE);
	if (str[i] && str[i] == 'n')
	{
		while (str[i] && str[i] == 'n')
			i++;
		if (str[i] == '\0')
			return (TRUE);
	}
	return (FALSE);
}

/**
 * Creer une chaine de char a partir du tableau de chaine de char
 */
void	builtin_echo(t_cmd *cmd)
{
	int	i_split;
	char	*output_str;

	i_split = 1;
	output_str = "\0";
	if (cmd->args_exec[1] && is_n_option_echo(cmd->args_exec[1]))
		i_split++;
	if (cmd->args_exec[i_split])
		output_str = cmd->args_exec[i_split];
	while (cmd->args_exec[i_split] && cmd->args_exec[i_split + 1])
	{
		output_str = ft_strjoin(output_str, " ");
		output_str = ft_strjoin(output_str, cmd->args_exec[i_split + 1]);
		i_split++;
	}
	if ((cmd->args_exec[1] && !is_n_option_echo(cmd->args_exec[1])) || len_split(cmd->args_exec) == 1)
		printf("%s\n", output_str);
	else
		printf("%s", output_str);
	if ((len_split(cmd->args_exec) > 2 && !is_n_option_echo(cmd->args_exec[1]))
		|| (len_split(cmd->args_exec) > 3 && is_n_option_echo(cmd->args_exec[1])))
		free(output_str);
	exit_status(1, TRUE);
	
}

void	builtin_pwd(void)
{
	char	*current_directory;

	current_directory = getcwd(NULL, 0);
	if (current_directory)
	{
		printf("%s\n", current_directory);
		free(current_directory);
	}
	exit_status(0, TRUE);
}

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
		i++;
		while (str[i] && str[i] != '=')
		{
			if (!ft_isalnum(str[i]) && str[i] != '_')
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
	t_key_val *var;

	i = 0;
	var = malloc(sizeof(t_key_val));
	if ((ft_isalpha(str[i]) || str[i] == '_'))
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '\0' || str[i] != '=')
	{
		free(var);
		return (NULL);
	}
	var->key = ft_substr(str, 0, i);
	i++; //skip = 
	var->value = ft_substr(str, i, (ft_strlen(str) - 1));
	printf("KEY = %s\n", var->key);
	printf("VAL = %s\n", var->value);
	return (var);
}


void	save_new_var(t_key_val *new_var, t_list **env)
{
	t_list *lst;
	t_key_val *content_env;

	lst = *env;
	while (lst)
	{
		content_env = lst->content;
		if (ft_strcmp(content_env->key, new_var->key) == 0)
		{
			free_key_val(lst->content);
			lst->content = new_var;
			return;
		}
		lst = lst->next;
	}
	ft_lstadd_back(env, ft_lstnew(new_var));
}

void	builtin_export(char **args, /*t_cmd *cmd,*/ int nb_cmd, t_list **env)
{
	int			i;
	t_key_val	*var;

	i = 0;
	// printf("HELLOOERIEOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO\n");
	exit_status(0, TRUE);
	if (args == NULL)
		return;
	while (args[i])
	{
		if (!is_valid_key(args[i]))
		{
			ft_putstr_fd("export: '", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			exit_status(1, TRUE);
		}
		else if (nb_cmd == 1)
		{
			var = create_new_var(args[i]);
			if (var)
				save_new_var(var, env);
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
		builtin_echo(cmd);
	else if (strcmp(cmd->name, "env") == 0)
		builtin_env(env);
	else if (strcmp(cmd->name, "pwd") == 0)
		builtin_pwd();
	else if (strcmp(cmd->name, "cd") == 0 && nb_cmd == 1)
		return;
	else if (strcmp(cmd->name, "export") == 0)
		builtin_export(args, /*cmd,*/ nb_cmd, env); 
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