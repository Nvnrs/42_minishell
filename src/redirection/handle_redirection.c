#include "minishell.h"

static int	redirect_case(t_key_val *content, t_bool is_last, t_list **env)
{
	int	status;

	status = 0;
	// if (ft_strcmp(content->key, "pipe") == 0 && is_in == TRUE)
	// 	status = redirect_pipe_in(content, is_last);
	// else if (ft_strcmp(content->key, "pipe") == 0 && is_in == FALSE)
	// 	status = redirect_pipe_out(content, is_last);
	if (ft_strcmp(content->key, "<") == 0)
		status = redirect_in(content, is_last);
	else if (ft_strcmp(content->key, "<<") == 0)
		status = handle_here_doc(content, is_last, env);
	else if (ft_strcmp(content->key, ">") == 0)
		status = redirect_out(content, is_last);
	else if (ft_strcmp(content->key, ">>") == 0)
		status = redirect_out_append(content, is_last);
	return (status);
}

// void	handle_redirection_in(t_list *operators_in, t_list **env)
// {
// 	t_key_val	*content;
// 	t_bool		is_last;
// 	int			status;

// 	is_last = FALSE;
// 	while (operators_in)
// 	{
// 		if (operators_in->next == NULL)
// 			is_last = TRUE;
// 		content = operators_in->content;
// 		status = redirect_case(content, is_last, TRUE, env);
// 		//printf("status value in handle_redirection_in: %d\n", status);
// 		//print_operator(operators_in->content);
// 		operators_in = operators_in->next;
// 	}
// }

// void	handle_redirection_out(t_list *operators_out, t_list **env)
// {
// 	t_key_val	*content;
// 	t_bool		is_last;
// 	int			status;

// 	is_last = FALSE;
// 	while (operators_out)
// 	{
// 		if (operators_out->next == NULL)
// 			is_last = TRUE;
// 		content = operators_out->content;
// 		status = redirect_case(content, is_last, FALSE, env);
// 		//printf("status value in handle_redirection_out: %d\n", status);
// 		//print_operator(operators_out->content);
// 		operators_out = operators_out->next;
// 	}
// }

t_bool	operator_in_in_lst_operator(t_list *lst_operator)
{
	t_key_val	*content;

	while (lst_operator)
	{
		content = lst_operator->content;
		if (strcmp(content->key, "<<") == 0 || strcmp(content->key, "<") == 0)
			return (TRUE);
		lst_operator = lst_operator->next;
	}
	return (FALSE);
}

t_bool	operator_out_in_lst_operator(t_list *lst_operator)
{
	t_key_val	*content;

	while (lst_operator)
	{
		content = lst_operator->content;
		if (strcmp(content->key, ">>") == 0 || strcmp(content->key, ">") == 0)
			return (TRUE);
		lst_operator = lst_operator->next;
	}
	return (FALSE);
}

int	index_last_in_operator(t_list *lst_operator)
{
	t_key_val	*content;
	int	i;
	int	index_last;

	i = 0;
	index_last = -1;
	while (lst_operator)
	{
		content = lst_operator->content;
		if (strcmp(content->key, "<<") == 0 || strcmp(content->key, "<") == 0)
			index_last = i;
		i++;
		lst_operator = lst_operator->next;
	}
	return (index_last);
}

int	index_last_out_operator(t_list *lst_operator)
{
	t_key_val	*content;
	int	i;
	int	index_last;

	i = 0;
	index_last = -1;
	while (lst_operator)
	{
		content = lst_operator->content;
		if (strcmp(content->key, ">>") == 0 || strcmp(content->key, ">") == 0)
			index_last = i;
		i++;
		lst_operator = lst_operator->next;
	}
	return (index_last);
}

int	handle_redirection(t_list *lst_operator, t_list **env, t_cmd *cmd)
{
	t_key_val	*content;
	int			i;
	t_bool		status;
	int			index_last_in;
	int			index_last_out;

	redirect_pipe(lst_operator, cmd);
	i = 0;
	index_last_in = index_last_in_operator(lst_operator);
	index_last_out = index_last_out_operator(lst_operator);
	printf("Index last in : %d\n", index_last_in);
	printf("Index last out : %d\n", index_last_out);
	while (lst_operator)
	{
		printf("Index : %d\n", i);
		content = lst_operator->content;
		if (i == index_last_in || i == index_last_out)
			status = redirect_case(content, TRUE, env);
		else
			status = redirect_case(content, FALSE, env);
		//printf("status value in handle_redirection_out: %d\n", status);
		//print_operator(operators_out->content);
		if (status != 0)
			return (1);
		i++;
		lst_operator = lst_operator->next;
	}
	return (0);
}
