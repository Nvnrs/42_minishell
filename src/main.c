/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:10:56 by nveneros          #+#    #+#             */
/*   Updated: 2025/02/24 15:08:59 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_pipe(t_key_val *content, int *last)
{
	dup2(atoi(content->value), *last);
	*last = atoi(content->value);
	return (0);
}

int	redirect_in(t_key_val *content, int *last)
{
	int fd;

	fd = open(content->value, O_RDONLY);
	if (fd < 0)
	{
		perror(NULL);
		return (1);
	}
	dup2(fd, *last);
	*last = fd;
	return (0);
}

int	redirect_out(t_key_val *content, int *last)
{
	int fd;

	fd = open(content->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror(NULL);
		return (1);
	}
	dup2(fd, *last);
	*last = fd;
	return (0);
}

int	write_to_here_doc(char * filename, char	*delimiter)
{
	char	*line;
	int		here_docfd;

	here_docfd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (here_docfd == -1)
		return (1);
	line = get_next_line(STDIN_FILENO);
	//expansion variable env
	while (strcmp(line, delimiter) != 0)
	{
		if (write(here_docfd, line, ft_strlen(line)) == -1)
		{
			free(line);
			return (2);
		}
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	free(line);
	close(here_docfd);
	return (0);
}


char *create_name_here_doc(int *id)
{
	char *name;
	char *id_str;

	id_str = ft_itoa(*id);
	name = ft_strdup(HERE_DOC_FILENAME);
	name = cft_strcat_realloc(name, id_str);
	name = cft_strcat_realloc(name, ".txt");
	free(id_str);
	*id += 1;
	return (name);
}

int	handle_here_doc(t_key_val *content, int *last)
{
	t_key_val	*here_doc;
	char		*name;
	static int 	id_here_doc;
	char		*delimiter;
	int			status;
	
	status = 0;
	name = create_name_here_doc(&id_here_doc);
	delimiter = ft_strdup(content->value);
	delimiter = cft_strcat_realloc(delimiter, "\n");
	here_doc = init_key_val("<", name);
	status = write_to_here_doc(here_doc->value, delimiter);
	if (status == 1)
	{
		free_key_val(here_doc);
		free(name);
		free(delimiter);
		handle_here_doc(content, last);
	}
	else if (status == 0)
		status = redirect_in(here_doc, last);
	free_key_val(here_doc);
	free(name);
	free(delimiter);
	return (status);
}

int	redirect_out_append(t_key_val *content, int *last)
{
	int fd;

	fd = open(content->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror(NULL);
		return (1);
	}
	dup2(fd, *last);
	*last = fd;
	return (1);
}

int	redirect_case(t_key_val *content, int *last)
{
	int	status;

	status = 0;
	if (ft_strcmp(content->key, "base") == 0)
		status = redirect_pipe(content, last);
	else if (ft_strcmp(content->key, "<") == 0)
		status = redirect_in(content, last);
	else if (ft_strcmp(content->key, "<<") == 0)
		status = handle_here_doc(content, last);
	else if (ft_strcmp(content->key, ">") == 0)
		status = redirect_out(content, last);
	else if (ft_strcmp(content->key, ">>") == 0)
		status = redirect_out_append(content, last);
	return (status);
}

void	handle_redirection_in(t_list *operators_in, t_list **lst_cmd, t_list **env,  t_cmd *cmd)
{
	t_key_val	*content;
	int			last;
	int			status;

	last = STDIN_FILENO;
	while (operators_in)
	{
		content = operators_in->content;
		status = redirect_case(content, &last);
		if (status != 0)
		{
			close_and_free_pipes(cmd->pipes, 2);
			free_lst_cmd(lst_cmd);
			free_list_env(env);
			exit(status);
		}
		operators_in = operators_in->next;
	}
	if (last != STDIN_FILENO)
		close(last);
}

void	handle_redirection_out(t_list *operators_out, t_list **lst_cmd, t_list **env, t_cmd *cmd)
{
	t_key_val	*content;
	int			last;
	int			status;

	last = STDOUT_FILENO;
	while (operators_out)
	{
		content = operators_out->content;
		status = redirect_case(content, &last);
		if (status != 0)
		{
			close_and_free_pipes(cmd->pipes, 2);
			free_lst_cmd(lst_cmd);
			free_list_env(env);
			exit(status);
		}
		operators_out = operators_out->next;
	}
	if (last != STDOUT_FILENO)
		close(last);
}

void	handle_cmd(t_cmd *cmd, t_list **lst_cmd, t_list **env)
{
	/**
	 * Effectue les redirections in et out
	 * Close pipes
	 * Execute la  commande de la commande
	 */
	char *arg[3];
	arg[0] = "echo\0";
	arg[1] = "test";
	arg[2] = NULL;
	printf("START\n");
	handle_redirection_in(*cmd->operators_in, lst_cmd, env, cmd);
	handle_redirection_out(*cmd->operators_out, lst_cmd, env, cmd);
	close_and_free_pipes(cmd->pipes, 2);
	free_lst_cmd(lst_cmd);
	free_list_env(env);
	// free_all_pipes(cmd->pipes, 2);
	// free_cmd(cmd);
	execve("/bin/echo", arg, NULL);
	exit(0);
}

int	processing(t_list **lst_cmd, int nb_cmd, int **pipes, t_list **env)
{
	/**
	 * Separe les commandes en plusieurs process
	 */
	int	i;
	int	pid;
	t_list	*lst;

	i = 0;
	printf("HELLO HELLO\n");
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
		printf("HANDLE_CMD\n");
		handle_cmd(lst->content, lst_cmd, env);
	}
	(void)pipes;
	//close_and_free_pipes(pipes, 2);
	while (i > 0)
	{
		printf("WAIT\n");
		wait(NULL);//pas complet
		i--;
	}
	return (0);
}

int	handle_readline(char *rd, t_list **env)
{
	/**
	 * Gere l'input de l'utilisateur
	 */
	char	**input;
	t_list	**lst_cmd;
	int		**pipes;

	add_history(rd);
	if (!basics_checks(rd))
	{
		free(rd);
		return (1);
	}
	input = parse_input(rd);
	pipes = init_pipes(2);
	lst_cmd = init_lst_cmd(input, pipes);
	free_split(input);
	processing(lst_cmd, ft_lstsize(*lst_cmd), pipes, env);
	ft_lstiter(*lst_cmd, print_cmd);
	free_lst_cmd(lst_cmd);
	close_and_free_pipes(pipes, 2);
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*rd;
	int		flag;
	// char	**input;
	t_list	**env;
	// t_list	**lst_cmd;
	// int		**pipes;

	(void)argc;
	(void)argv;
	env = init_list_env(envp);
	flag = 1;
	while (flag)
	{
		rd = readline("> ");
		if (rd && *rd)
		{
			if (handle_readline(rd, env) == 1)
				continue ;
			// add_history(rd);
			// if (!basics_checks(rd))
			// {
			// 	free(rd);
			// 	continue;
			// }
			// input = parse_input(rd);
			// pipes = init_pipes(2);
			// printf("pipes[0][0] = %d\npipes[0][1] = %d\npipes[1][0] = %d\npipes[1][1] = %d\n", pipes[0][0], pipes[0][1], pipes[1][0], pipes[1][1]);
			// lst_cmd = init_lst_cmd(input, pipes);
			// ft_lstiter(*lst_cmd, print_cmd);
			// free_lst_cmd(lst_cmd);
			// free_split(input);
			// close_and_free_pipes(pipes, 2);
		}
		else if (rd == NULL)
			flag = 0;
		free(rd);
	}
	rl_clear_history();
	free_list_env(env);
	return (0);
}
