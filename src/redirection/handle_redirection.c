#include "minishell.h"

static int	redirect_case(t_key_val *content, t_bool is_last, t_bool is_in, t_list **env)
{
	int	status;

	status = 0;
	if (ft_strcmp(content->key, "pipe") == 0 && is_in == TRUE)
		status = redirect_pipe_in(content, is_last);
	else if (ft_strcmp(content->key, "pipe") == 0 && is_in == FALSE)
		status = redirect_pipe_out(content, is_last);
	else if (ft_strcmp(content->key, "<") == 0)
		status = redirect_in(content, is_last);
	else if (ft_strcmp(content->key, "<<") == 0)
		status = handle_here_doc(content, is_last, env);
	else if (ft_strcmp(content->key, ">") == 0)
		status = redirect_out(content, is_last);
	else if (ft_strcmp(content->key, ">>") == 0)
		status = redirect_out_append(content, is_last);
	return (status);
}

void	handle_redirection_in(t_list *operators_in, t_list **env)
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
		status = redirect_case(content, is_last, TRUE, env);
		//printf("status value in handle_redirection_in: %d\n", status);
		//print_operator(operators_in->content);
		operators_in = operators_in->next;
	}
}

void	handle_redirection_out(t_list *operators_out, t_list **env)
{
	t_key_val	*content;
	t_bool		is_last;
	int			status;

	is_last = FALSE;
	while (operators_out)
	{
		if (operators_out->next == NULL)
			is_last = TRUE;
		content = operators_out->content;
		status = redirect_case(content, is_last, FALSE, env);
		//printf("status value in handle_redirection_out: %d\n", status);
		//print_operator(operators_out->content);
		operators_out = operators_out->next;
	}
}