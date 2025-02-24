#include "minishell.h"

static int	redirect_case(t_key_val *content, t_bool is_last)
{
	int	status;

	status = 0;
	if (ft_strcmp(content->key, "base") == 0)
		status = redirect_pipe(content, NULL);
	else if (ft_strcmp(content->key, "<") == 0)
		status = redirect_in(content, is_last);
	else if (ft_strcmp(content->key, "<<") == 0)
		status = handle_here_doc(content, is_last);
	else if (ft_strcmp(content->key, ">") == 0)
		status = redirect_out(content, is_last);
	else if (ft_strcmp(content->key, ">>") == 0)
		status = redirect_out_append(content, is_last);
	return (status);
}

void	handle_redirection_in(t_list *operators_in, t_list **lst_cmd, int **pipes, t_list **env)
{
	t_key_val	*content;
	t_bool		is_last;
	int			status;

	is_last = FALSE;
	while (operators_in)
	{
		if (operators_in->next == NULL)
			is_last = TRUE;
		content = operators_in->content;
		status = redirect_case(content, is_last);
		printf("status value in handle_redirection_out: %d\n", status);
		// if (status != 0)
		// {
		// 	close_and_free_pipes(pipes, 2);
		// 	free_lst_cmd(lst_cmd);
		// 	free_list_env(env);
		// 	// exit(status);
		// }
		print_operator(operators_in->content);
		operators_in = operators_in->next;
	}
	// if (is_last != STDIN_FILENO)
	// 	close(is_last);
}

void	handle_redirection_out(t_list *operators_out, t_list **lst_cmd, int **pipes, t_list **env)
{
	t_key_val	*content;
	t_bool		is_last;
	int			status;

	is_last = STDOUT_FILENO;
	while (operators_out)
	{
		if (operators_out->next == NULL)
			is_last = TRUE;
		content = operators_out->content;
		status = redirect_case(content, is_last);
		printf("status value in handle_redirection_out: %d\n", status);
		// if (status != 0)
		// {
		// 	close_and_free_pipes(pipes, 2);
		// 	free_lst_cmd(lst_cmd);
		// 	free_list_env(env);
		// 	exit(status);
		// }
		operators_out = operators_out->next;
	}
	// if (is_last != STDOUT_FILENO)
	// 	close(is_last);
}