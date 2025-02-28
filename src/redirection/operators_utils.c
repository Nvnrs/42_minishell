#include "minishell.h"

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