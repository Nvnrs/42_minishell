/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 17:18:12 by nveneros          #+#    #+#             */
/*   Updated: 2025/03/11 10:51:13 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redirect_case(t_key_val *content, t_bool is_last)
{
	int	status;

	status = 0;
	if (ft_strcmp(content->key, "<") == 0)
		status = redirect_in(content, is_last);
	else if (ft_strcmp(content->key, "<<") == 0)
		status = handle_here_doc(content, is_last);
	else if (ft_strcmp(content->key, ">") == 0)
		status = redirect_out(content, is_last);
	else if (ft_strcmp(content->key, ">>") == 0)
		status = redirect_out_append(content, is_last);
	return (status);
}

int	handle_redirection(t_list *lst_operator, t_cmd *cmd)
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
	while (lst_operator)
	{
		content = lst_operator->content;
		if (i == index_last_in || i == index_last_out)
			status = redirect_case(content, TRUE);
		else
			status = redirect_case(content, FALSE);
		if (status != 0)
			return (1);
		i++;
		lst_operator = lst_operator->next;
	}
	return (0);
}
